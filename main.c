/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : main.c
Purpose : Generic application start

*/

#include 
#include 
#include "STM32L432KC_RCC.h"
#include "STM32L432KC_FLASH.h"
#include "stm32l432xx.h"
#include "STM32L432KC_GPIO.h"

/*********************************************************************
*
*       main()
*
*  Function description
*   Application entry point.
*/


#define GPIO GPIOA
void helper(void);
void delay(int cycles);
void setStep(int w1, int w2, int w3, int w4);
void forward(int steps, int delay);
#define DELAY_DURATION  200

int main(void) {
  configureFlash();
  configureClock();
  RCC->AHB2ENR |= (1 << 0); // turn on GPIO_A
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; // turn on GPIO_B
  //GPIO->AFRL &= ~(0b1111 << 24);
  //GPIO->AFRL |= (0b1110 << 24);
  pinMode(PA9, 1);
  pinMode(PA10, 1);
  pinMode(PA11, 1);
  pinMode(PA2, 1);
  pinMode(PB0, 1);
  pinMode(PA5, 1);
  int i = 0;
  while (i < 20) {
      //helper();
      digitalWrite(PA9, 1);
      digitalWrite(PA10, 0);
      digitalWrite(PA11, 0);
      digitalWrite(PA2, 0);
      
      delay(200);

      digitalWrite(PA9, 0);
      digitalWrite(PA10, 1);
      digitalWrite(PA11, 0);
      digitalWrite(PA2, 0);

      delay(200);

      digitalWrite(PA9, 0);
      digitalWrite(PA10, 0);
      digitalWrite(PA11, 1);
      digitalWrite(PA2, 0);

      delay(200);

      digitalWrite(PA9, 0);
      digitalWrite(PA10, 0);
      digitalWrite(PA11, 0);
      digitalWrite(PA2, 1);

      delay(200);

      i += 1;

    }
  /*while (1) {
    i = 0;
    while (i < 20) {
      //helper();
      digitalWrite(PA9, 1);
      digitalWrite(PA10, 0);
      digitalWrite(PA11, 0);
      digitalWrite(PA2, 0);
      
      delay(200);

      digitalWrite(PA9, 0);
      digitalWrite(PA10, 1);
      digitalWrite(PA11, 0);
      digitalWrite(PA2, 0);

      delay(200);

      digitalWrite(PA9, 0);
      digitalWrite(PA10, 0);
      digitalWrite(PA11, 1);
      digitalWrite(PA2, 0);

      delay(200);

      digitalWrite(PA9, 0);
      digitalWrite(PA10, 0);
      digitalWrite(PA11, 0);
      digitalWrite(PA2, 1);

      delay(200);

      i += 1;

    }
  }*/

  //forward(512, DELAY_DURATION);

}



void delay(int cycles) {
   while (cycles-- > 0) {
      volatile int x=200;
      while (x-- > 0)
         __asm("nop");
   }
}


void setStep(int w1, int w2, int w3, int w4) {
    digitalWrite(PA9, w1);
    digitalWrite(PA10, w2);
    digitalWrite(PA11, w3);
    digitalWrite(PA12, w4);
    delay(5);  // Delay to control the speed of the stepper motor
}

void forward(int steps, int delay_time) {
    for (int i = 0; i < steps; ++i) {
        setStep(1, 0, 0, 0);
        setStep(0, 1, 0, 0);
        setStep(0, 0, 1, 0);
        setStep(0, 0, 0, 1);
    }
    delay(delay_time);
}

void helper(void) {
  for (int i = 0; i < 1; i++) {
    digitalWrite(10,1);
    digitalWrite(9,0);
    digitalWrite(11,0);
    digitalWrite(12,0);
  }
  delay(DELAY_DURATION);
  for (int j = 0; j < 1; j++) {
    digitalWrite(9,1);
    digitalWrite(10,0);
    digitalWrite(11,0);
    digitalWrite(12,0);
  }
  delay(DELAY_DURATION);
  for (int x = 0; x < 1; x++) {
    digitalWrite(9,0);
    digitalWrite(10,0);
    digitalWrite(11,1);
    digitalWrite(12,0);
  }
  delay(DELAY_DURATION);
  for (int y = 0; y < 1; y++) {
    digitalWrite(9,0);
    digitalWrite(10,0);
    digitalWrite(11,0);
    digitalWrite(12,1);
  }
  delay(DELAY_DURATION);
}

/*************************** End of file ****************************/


