/**
        @file main.c
    @authors: Dimitri Avila, 
              Javier Perez,
              Nithya Yeluri 
        Date: 10/7/23

*/

#include <stdio.h>
#include <stm32l432xx.h>
#include "STM32L432KC_GPIO.h"
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_TIM.h"
#include "STM32L432KC_FLASH.h"
#include "STM32L432KC_USART.h"
#include "STM32L432KC_SPI.h"

//Note: functions without comments are commented
//      on the other c file in the GitHub

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

#define MCK_FREQ 100000

////////////////////////////////////////////////
// Function Prototypes
////////////////////////////////////////////////

void SPISendHelper(char);
char ScrollingSignal(int hours);
char StaticSignal(int hours, int minutes);
int timerCodeStatic(int hour, int minutes);
int timerCodeScrolling(int hour, int minutes);
void initializeFlap1(void);
void initializeFlap2(void);
void spinFlap1(void);
void spinFlap2(void);
void delay(int cycles);
int calibrateFlap2(void);
int calibrateFlap1(void);
void spinToHour2(int x);
void spinToHour1(int x);

#define DELAY_DURATION  120



////////////////////////////////////////////////
// Main
////////////////////////////////////////////////

int main(void) {
  // Configure clock
  configureFlash();
  configureClock();




  // Enable GPIOA clock
  RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN);

  // "clock divide" = master clock frequency / desired baud rate
  // the phase for the SPI clock is 1 and the polarity is 0
  initSPI(1, 0, 0);

  //initialize flaps
  initializeFlap1();
  initializeFlap2();


  // LOAD pin
  pinMode(PA5, GPIO_OUTPUT);  // LOAD

  


  // hardware accelerated encryption

  /*Spin Flap 1 and 2 for calibration */
  int i = 0;
  while (i < 80) {
    spinFlap1();
    spinFlap2();
    i++;
  }

  
  int hr1 = 1;
  int hr2 = 6;
  int combinedHr = 16;
  int min = 59;


  while(1) {
    calibrateFlap1();
    calibrateFlap2();

    // Spin to real time 
    //spinToMin4(min4);
    //spinToMin3(min3);
    spinToHour2(hr2);
    spinToHour1(hr1);

    delay(50000);

    // start the timer
    timerCodeScrolling(combinedHr, min);
  }
}

////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////


void spinFlap1Once(void) {
  int i = 0;
  while (i < 13) {
    spinFlap1();
    i++;
  }
  
}

//spins Flap 2 once
void spinFlap2Once(void) {
  int i = 0;
  while (i < 13) {
    spinFlap2();
    i++;
  }
  
}
//Spins to flap labeled x from Flap 2's home state
void spinToHour2(int x){
  int z = 0;
  for(int j = 0; j < x; j++) {
    z = 0;
    while(z < 13) { 
      spinFlap2();
      ++z;
    }
    delay(50000);
  }
}

//Spins to flap labeled x from Flap 1's home state
void spinToHour1(int x){
  int z = 0;
  for(int j = 0; j < x; j++) {
    z = 0;
    while(z < 13) { 
      spinFlap1();
      ++z;
    }
    delay(50000);
  }
}

int calibrateFlap1(void) {
  pinMode(PA8, 0); // Flap 3 Hall Sensor (works with spinFlap3, works with spinflap4)
  printf("%d: \n", digitalRead(PA8));
  while(digitalRead(PA8) != 0) {
    printf("3: %d \n", digitalRead(PA8));
    spinFlap1();
  }
  //disableFlap3();
  return 1;
}

int calibrateFlap2(void) {
  //initializeFlap2();
  printf("Initialized\n");
  pinMode(PB6, 0); // Flap 4 Hall Sensor (Works with spinflap1, not spinflap2, works with spinflap3, works with spinflap4)
  printf("%d\n", digitalRead(PB6));
  while(digitalRead(PB6) != 0) {
    printf("4: %d \n", digitalRead(PB6));
    spinFlap2();
  } 
  //disableFlap4();
  return 1;
}

void delay(int cycles) {
   while (cycles-- > 0) {
      volatile int x=200;
      while (x-- > 0)
         __asm("nop");
   }
}

void spinFlap2(void){
  digitalWrite(PA11, 0);
  digitalWrite(PA12, 0);
  digitalWrite(PA10, 0);
  digitalWrite(PA9, 1);

  delay(DELAY_DURATION);

  digitalWrite(PA11, 0);
  digitalWrite(PA12, 0);
  digitalWrite(PA10, 1);
  digitalWrite(PA9, 0);

  delay(DELAY_DURATION);

  digitalWrite(PA11, 0);
  digitalWrite(PA12, 1);
  digitalWrite(PA10, 0);
  digitalWrite(PA9, 0);

  delay(DELAY_DURATION);

  digitalWrite(PA11, 1);
  digitalWrite(PA12, 0);
  digitalWrite(PA10, 0);
  digitalWrite(PA9, 0);

  delay(DELAY_DURATION);

}

void spinFlap1(void){
    digitalWrite(PA4, 0);
    digitalWrite(PA3, 0);
    digitalWrite(PA1, 0);
    digitalWrite(PA0, 1);

    delay(DELAY_DURATION);

    digitalWrite(PA4, 0);
    digitalWrite(PA3, 0);
    digitalWrite(PA1, 1);
    digitalWrite(PA0, 0);

    delay(DELAY_DURATION);

    digitalWrite(PA4, 0);
    digitalWrite(PA3, 1);
    digitalWrite(PA1, 0);
    digitalWrite(PA0, 0);

    delay(DELAY_DURATION);

    digitalWrite(PA4, 1);
    digitalWrite(PA3, 0);
    digitalWrite(PA1, 0);
    digitalWrite(PA0, 0);

    delay(DELAY_DURATION);

}

void initializeFlap1(void) {
  pinMode(PA0, 1);
  pinMode(PA1, 1);
  pinMode(PA3, 1);
  pinMode(PA4, 1);
}

void initializeFlap2(void) {
  pinMode(PA9, 1);
  pinMode(PA10, 1);
  pinMode(PA12, 1);
  pinMode(PA11, 1);
}

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
// creates the signal sent to the 
// FPGA for scrolling mode.

  //creates SPI message corresponding to 
  // the interval of 6 PM <= T < 6 AM
  if ( hours < 6  || hours >= 18) {
    return 0x20; //creates scrolling Moon
  } 
    // creates SPI message corresponding to 
   //  the intrval of 6 AM <= T < 6 PM
   else {
    return 0x21; //creates scrolling 
  }
}

char StaticSignal(int hour, int minutes) {
// creates the signal sent to the 
// FPGA for static mode.

 // creates SPI message corresponding to 
 //  the interval of 8:30 AM <= T < 9:15 AM
 if (hour == 8 && (30 <= minutes && minutes <= 59)) {
    return 0x00;
 }
 else if (hour == 9 && (0 <= minutes && minutes < 15)) {
    return 0x00;
 }

 // creates SPI message corresponding to 
 //  the interval of 9:15 AM <= T < 10:00 AM
 else if (hour == 9 && (15 <= minutes && minutes <= 59)) {
    return 0x01;
 }

 // creates SPI message corresponding to 
 //  the interval of 10:00 AM <= T < 10:45 AM
 else if (hour == 10 && (0 <= minutes && minutes < 45)) {
    return 0x02;
 }

    // creates SPI message corresponding to 
   //  the interval of 10:45 PM <= T < 11:30 PM
 else if (hour == 10 && (45 <= minutes && minutes <= 59)) {
    return 0x03;
 }
 else if (hour == 11 && (0 <= minutes && minutes < 30)) {
    return 0x03;
 }

 // creates SPI message corresponding to 
 //  the interval of 11:30 AM <= T < 12:15 PM
 else if (hour == 11 && (30 <= minutes && minutes <= 59)) {
    return 0x04;
 }
  else if (hour == 12 && (0 <= minutes && minutes < 15)) {
    return 0x04;
 }

 // creates SPI message corresponding to 
 //  the interval of 12:15 PM <= T < 1:00 PM
 else if (hour == 12 && (15 <= minutes && minutes <= 59)) {
    return 0x05;
 }

 // creates SPI message corresponding to 
 //  the interval of 1:00 PM <= T < 1:45 PM
 else if (hour == 13 && (0 <= minutes && minutes < 45)) {
    return 0x06;
 }

 // creates SPI message corresponding to 
 //  the interval of 1:45 PM <= T < 2:30 PM
 else if (hour == 13 && (45 <= minutes && minutes <= 59)) {
    return 0x07;
 }
  else if (hour == 14 && (0 <= minutes && minutes < 30)) {
    return 0x07;
 }

 // creates SPI message corresponding to 
 //  the interval of 2:30 PM <= T < 3:15 PM
 else if (hour == 14 && (30 <= minutes && minutes <= 59)) {
    return 0x08;
 }
  else if (hour == 15 && (0 <= minutes && minutes < 15)) {
    return 0x08;
 }

 // creates SPI message corresponding to 
 //  the interval of 3:15 PM <= T < 4:00 PM
 else if (hour == 15 && (15 <= minutes && minutes <= 59)) {
    return 0x09;
 }

 // creates SPI message corresponding to 
 //  the interval of 4:00 PM <= T < 4:45 PM
 else if (hour == 16 && (0 <= minutes && minutes < 45)) {
    return 0x0A;
 }

 // creates SPI message corresponding to 
 //  the interval of 4:45 PM <= T < 5:30 PM
 else if (hour == 16 && (45 <= minutes && minutes <= 59)) {
    return 0x0B;
 }
  else if (hour == 17 && (0 <= minutes && minutes < 30)) {
    return 0x0B;
 }

 // creates SPI message corresponding to 
 //  the interval of 5:30 PM <= T < 6:15 PM
 else if (hour == 17 && (30 <= minutes && minutes <= 59)) {
    return 0x0C;
 }
  else if (hour == 18 && (0 <= minutes && minutes < 15)) {
    return 0x0C;
 }

 // creates SPI message corresponding to 
 //  the interval of 6:15 PM <= T < 7:00 PM
 else if (hour == 18 && (15 <= minutes && minutes <= 59)) {
    return 0x0D;
 }

 // creates SPI message corresponding to 
 //  the interval of 7:00 PM <= T < 7:45 PM
 else if (hour == 19 && (0 <= minutes && minutes < 45)) {
    return 0x0E;
 }

 // creates SPI message corresponding to 
 //  the interval of 7:45 PM <= T < 8:30 PM
 else if (hour == 19 && (45 <= minutes && minutes <= 59)) {
    return 0x0F;
 }
  else if (hour == 20 && (0 <= minutes && minutes < 30)) {
    return 0x0F;
 }

 // creates SPI message corresponding to 
 //  the interval of 8:30 PM <= T < 9:15 PM
 else if (hour == 20 && (30 <= minutes && minutes <= 59)) {
    return 0x10;
  }
  else if (hour == 21 && (0 <= minutes && minutes < 15)) {
    return 0x10;
 }

 // creates SPI message corresponding to 
 //  the interval of 9:15 PM <= T < 10:00 PM
 else if (hour == 21 && (15 <= minutes && minutes <= 59)) {
    return 0x11;
 }

 // creates SPI message corresponding to 
 //  the interval of 10:00 PM <= T < 10:45 PM
 else if (hour == 22 && (0 <= minutes && minutes < 45)) { 
    return 0x12;
 }

 // creates SPI message corresponding to 
 //  the interval of 10:45 PM <= T < 11:30 PM
 else if (hour == 22 && (45 <= minutes && minutes <= 59)) {
    return 0x13;
 }
  else if (hour == 23 && (0 <= minutes && minutes < 30)) {
    return 0x13;
 }

 // creates SPI message corresponding to 
 //  the interval of 11:30 PM <= T < 12:15 AM
 else if (hour == 23 && (30 <= minutes && minutes <= 59)) {
    return 0x14;
 }
  else if (hour == 0 && (0 < minutes && minutes < 15)) {
    return 0x14;
 }

 // creates SPI message corresponding to 
 //  the interval of 12:15 AM <= T < 1:00 AM
 else if (hour == 0 && (15 <= minutes && minutes <= 59)) {
    return 0x15;
 }

 // creates SPI message corresponding to 
 //  the interval of 1:00 AM <= T < 1:45 AM
 else if (hour == 1 && (0 <= minutes && minutes < 45)) {
    return 0x16;
 }

 // creates SPI message corresponding to 
 //  the interval of 1:45 AM <= T < 2:30 AM
 else if (hour == 1 && (45 <= minutes && minutes <= 59)) {
    return 0x17;
 }
  else if (hour == 2 && (0 <= minutes && minutes < 30)) {
    return 0x17;
 }

 // creates SPI message corresponding to 
 //  the interval of 2:30 AM <= T < 3:15 AM
 else if (hour == 2 && (30 <= minutes && minutes <= 59)) {
    return 0x18;
 }
  else if (hour == 3 && (0 < minutes && minutes < 15)) {
    return 0x18;
 }

 // creates SPI message corresponding to 
 //  the interval of 3:15 AM <= T < 4:00 AM
 else if (hour == 3 && (15 <= minutes && minutes <= 59)) {
    return 0x19;
 }
 // creates SPI message corresponding to 
 //  the interval of 4:00 AM <= T < 4:45 AM
 else if (hour == 4 && (0 <= minutes && minutes < 45)) {
    return 0x1A;
 }

 // creates SPI message corresponding to 
 //  the interval of 4:45 AM <= T < 5:30 AM
 else if (hour == 4 && (45 <= minutes && minutes <= 59)) {
    return 0x1B;
 }
  else if (hour == 5 && (0 <= minutes && minutes < 30)) {
    return 0x1B;
 }

 // creates SPI message corresponding to 
 //  the interval of 5:30 AM <= T < 6:15 AM
 else if (hour == 5 && (30 <= minutes && minutes <= 59)) {
    return 0x1C;
 }
  else if (hour == 6 && (0 < minutes && minutes < 15)) {
    return 0x1C;
 }

 // creates SPI message corresponding to 
 //  the interval of 6:15 AM <= T < 7:00 AM
 else if (hour == 6 && (15 <= minutes && minutes <= 59)) {
    return 0x1D;
 }

 // creates SPI message corresponding to 
 //  the interval of 7:00 AM <= T < 7:45 AM
 else if (hour == 7 && (0 <= minutes && minutes < 45)) {
    return 0x1E;
 }

 // creates SPI message corresponding to 
 //  the interval of 7:45 AM <= T < 8:30 AM
 else if (hour == 7 && (45 <= minutes && minutes <= 59)) {
    return 0x1F;
 }
  else if (hour == 8 && (0 <= minutes && minutes < 30)) {
    return 0x1F;
 }

 // else statement should never be 
 // called but here in case error occurs.
 else {
    return 0x00;
 }
}

int timerCodeStatic(int hour, int minutes) {
// creates timer and spins flap, while sending
// messages to FPGA correspondinf to static mode


  RCC->APB2ENR |= (1 << 16); // RCC -> Timer 15
  RCC->APB2ENR |= (1 << 17); // RCC -> Timer 16


  //configure port A (set three bits of AFRL to 1110)
  GPIOA->AFR[0] &= ~(0b1111 << 24);
  GPIOA->AFR[0] |= (0b1110 << 24);


  initTIM(TIM15);
  int seconds = 0; // seconds
  int originminutes = minutes;
  int originhour = hour;

  while (1) {
    hour = hour % 24;
    while (hour < 24) {
      minutes = minutes % 60;
      char mat = StaticSignal(hour, minutes);
      SPISendHelper(mat);
      while (minutes < 60) {
        seconds = 0;
        while(seconds < 60) {
          delay_millis(TIM15, 600); //one sec
          seconds++; // count up one sec
        }
        minutes++;
        if (minutes % 10 == 0) {
          if (minutes / 10 == 6) {
            if (hour == 9) {
              spinFlap2Once();
              calibrateFlap1();
            } else if (hour == 19) {
              spinFlap2Once();
              calibrateFlap1();
            } else if (hour == 23) {
              calibrateFlap2();
              calibrateFlap1();
            }
          }
        }
        char mat = StaticSignal(hour, minutes);
        SPISendHelper(mat);
      }
      hour++;
    }
  }
}

int timerCodeScrolling(int hour, int minutes) {
// creates timer and spins flap, while sending
// messages to FPGA correspondinf to scrolling mode

  RCC->APB2ENR |= (1 << 16); // RCC -> Timer 15
  RCC->APB2ENR |= (1 << 17); // RCC -> Timer 16


  //configure port A (set three bits of AFRL to 1110)
  GPIOA->AFR[0] &= ~(0b1111 << 24);
  GPIOA->AFR[0] |= (0b1110 << 24);


  initTIM(TIM15);
  int seconds = 0; // seconds
  int originminutes = minutes;
  int originhour = hour;

  while (1) {
    hour = hour % 24;
    while (hour < 24) {
      minutes = minutes % 60;
      char mat = ScrollingSignal(hour);
      SPISendHelper(mat);
      while (minutes < 60) {
        seconds = 0;
        while(seconds < 60) {
          delay_millis(TIM15, 600); //one sec
          seconds++; // count up one sec
        }
        minutes++;
        if (minutes % 10 == 0) {
          if (minutes / 10 == 6) {
            if (hour == 9) {
              spinFlap2Once();
              calibrateFlap1();
            } else if (hour == 19) {
              spinFlap2Once();
              calibrateFlap1();
            } else if (hour == 23) {
              calibrateFlap2();
              calibrateFlap1();
            } else {
              spinFlap2Once();
            }
          }
        }
        char mat = ScrollingSignal(hour);
        SPISendHelper(mat);
      }
      hour++;
    }
  }
}
