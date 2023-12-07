/**
    Main: Contains main function for AES SPI communication with FPGA.
    Sends the plaintext and key over SPI to the FPGA and then receives back
    the cyphertext. The cyphertext is then compared against the solution
    listed in Appendix A of the AES FIPS 197 standard.
    @file lab7.c
    @author Josh Brake
    @version 1.0 7/13/2021
*/
#include <stdio.h>
#include <stm32l432xx.h>
#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_TIM.h"
#include "STM32L432KC_FLASH.h"
#include "STM32L432KC_USART.h"
#include "STM32L432KC_SPI.h"

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

#define MCK_FREQ 100000

// Test Case from Appendix A.1, B
char matrix[1] = {0x14};

/* 
// Another test case from Appendix C.1

char key[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

char plaintext[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                      0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

char ct[16] = {0x69, 0xC4, 0xE0, 0xD8, 0x6A, 0x7B, 0x04, 0x30,
               0xD8, 0xCD, 0xB7, 0x80, 0x70, 0xB4, 0xC5, 0x5A};
*/

////////////////////////////////////////////////
// Function Prototypes
////////////////////////////////////////////////

void SPISendHelper(char);
char ScrollingSignal(int hours);
char StaticSignal(int hours, int minutes);


////////////////////////////////////////////////
// Main
////////////////////////////////////////////////

int main(void) {
  char cyphertext[16];

  // Configure flash latency and set clock to run at 84 MHz

  // Enable GPIOA clock
  RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN);

  // "clock divide" = master clock frequency / desired baud rate
  // the phase for the SPI clock is 1 and the polarity is 0
  initSPI(1, 0, 0);


  // Load and done pins
  pinMode(PA5, GPIO_OUTPUT);  // LOAD
  pinMode(PA6, GPIO_INPUT);   // DONE
  
  // debugging LEDs
  pinMode(PA9, GPIO_OUTPUT);
  pinMode(PA10, GPIO_OUTPUT);
  digitalWrite(PA9, 0);
  digitalWrite(PA10, 0);

  // hardware accelerated encryption
  int hr = 0;
  int min = 12;
  char mat = StaticSignal(hr, min);
  SPISendHelper(mat);
}

////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////


void SPISendHelper(char plaintext) {
  int i;

  // Write LOAD high
  digitalWrite(PA5, 1);

  // Send plaintext
    spiSendReceive(plaintext);

  while(SPI1->SR & SPI_SR_BSY); // Confirm all SPI transactions are completed
  digitalWrite(PA5, 0); // Write LOAD low
}

char ScrollingSignal(int hours) {
  if ( hours < 6  || hours >= 18) {
    return 0x20;
  } 
   else {
    return 0x21;
  }
}

char StaticSignal(int hour, int minutes) {
 if (hour == 8 && (30 <= minutes && minutes <= 59)) {
    return 0x00;
 }
 else if (hour == 9 && (0 <= minutes && minutes < 15)) {
    return 0x00;
 }

 else if (hour == 9 && (15 <= minutes && minutes <= 59)) {
    return 0x01;
 }

 else if (hour == 10 && (0 <= minutes && minutes < 45)) {
    return 0x02;
 }

 else if (hour == 10 && (45 <= minutes && minutes <= 59)) {
    return 0x03;
 }
 else if (hour == 11 && (0 <= minutes && minutes < 30)) {
    return 0x03;
 }

 else if (hour == 11 && (30 <= minutes && minutes <= 59)) {
    return 0x04;
 }
  else if (hour == 12 && (0 <= minutes && minutes < 15)) {
    return 0x04;
 }

 else if (hour == 12 && (15 <= minutes && minutes <= 59)) {
    return 0x05;
 }

 else if (hour == 13 && (0 <= minutes && minutes < 45)) {
    return 0x06;
 }

 else if (hour == 13 && (45 <= minutes && minutes <= 59)) {
    return 0x07;
 }
  else if (hour == 14 && (0 <= minutes && minutes < 30)) {
    return 0x07;
 }

 else if (hour == 14 && (30 <= minutes && minutes <= 59)) {
    return 0x08;
 }
  else if (hour == 15 && (0 <= minutes && minutes < 15)) {
    return 0x08;
 }

 else if (hour == 15 && (15 <= minutes && minutes <= 59)) {
    return 0x09;
 }

 else if (hour == 16 && (0 <= minutes && minutes < 45)) {
    return 0x0A;
 }

 else if (hour == 16 && (45 <= minutes && minutes <= 59)) {
    return 0x0B;
 }
  else if (hour == 17 && (0 <= minutes && minutes < 30)) {
    return 0x0B;
 }

 else if (hour == 17 && (30 <= minutes && minutes <= 59)) {
    return 0x0C;
 }
  else if (hour == 18 && (0 <= minutes && minutes < 15)) {
    return 0x0C;
 }

 else if (hour == 18 && (15 <= minutes && minutes <= 59)) {
    return 0x0D;
 }

 else if (hour == 19 && (0 <= minutes && minutes < 45)) {
    return 0x0E;
 }

 else if (hour == 19 && (45 <= minutes && minutes <= 59)) {
    return 0x0F;
 }
  else if (hour == 20 && (0 <= minutes && minutes < 30)) {
    return 0x0F;
 }

 else if (hour == 20 && (30 <= minutes && minutes <= 59)) {
    return 0x10;
  }
  else if (hour == 21 && (0 <= minutes && minutes < 15)) {
    return 0x10;
 }

 else if (hour == 21 && (15 <= minutes && minutes <= 59)) {
    return 0x11;
 }

 else if (hour == 22 && (0 <= minutes && minutes < 45)) { 
    return 0x12;
 }

 else if (hour == 22 && (45 <= minutes && minutes <= 59)) {
    return 0x13;
 }
  else if (hour == 23 && (0 <= minutes && minutes < 30)) {
    return 0x13;
 }

 else if (hour == 23 && (30 <= minutes && minutes <= 59)) {
    return 0x14;
 }
  else if (hour == 0 && (0 < minutes && minutes < 15)) {
    return 0x14;
 }

 else if (hour == 0 && (15 <= minutes && minutes <= 59)) {
    return 0x15;
 }

 else if (hour == 1 && (0 <= minutes && minutes < 45)) {
    return 0x16;
 }

 else if (hour == 1 && (45 <= minutes && minutes <= 59)) {
    return 0x17;
 }
  else if (hour == 2 && (0 <= minutes && minutes < 30)) {
    return 0x17;
 }

 else if (hour == 2 && (30 <= minutes && minutes <= 59)) {
    return 0x18;
 }
  else if (hour == 3 && (0 < minutes && minutes < 15)) {
    return 0x18;
 }

 else if (hour == 3 && (15 <= minutes && minutes <= 59)) {
    return 0x19;
 }
 else if (hour == 4 && (0 <= minutes && minutes < 45)) {
    return 0x1A;
 }

 else if (hour == 4 && (45 <= minutes && minutes <= 59)) {
    return 0x1B;
 }
  else if (hour == 5 && (0 <= minutes && minutes < 30)) {
    return 0x1B;
 }

 else if (hour == 5 && (30 <= minutes && minutes <= 59)) {
    return 0x1C;
 }
  else if (hour == 6 && (0 < minutes && minutes < 15)) {
    return 0x1C;
 }

 else if (hour == 6 && (15 <= minutes && minutes <= 59)) {
    return 0x1D;
 }

 else if (hour == 7 && (0 <= minutes && minutes < 45)) {
    return 0x1E;
 }

 else if (hour == 7 && (45 <= minutes && minutes <= 59)) {
    return 0x1F;
 }
  else if (hour == 8 && (0 <= minutes && minutes < 30)) {
    return 0x1F;
 }
 else {
    return 0x00;
 }
}
