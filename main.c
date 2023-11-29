/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : main.c
Purpose : Generic application start

*/


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
#define DELAY_DURATION  300

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


  pinMode(PA3, 1);
  pinMode(PA4, 1);
  pinMode(PA5, 1);
  pinMode(PA6, 1);


  pinMode(PA0, 1);
  pinMode(PA1, 1);
  pinMode(PA7, 1);
  pinMode(PA8, 1);


  int i = 0;
  while (1) {
      //helper();

      // Flap #2
      digitalWrite(PA9, 0);
      digitalWrite(PA10, 0);
      digitalWrite(PA11, 0);
      digitalWrite(PA2, 1);

      // Flap #3
      digitalWrite(PA3, 0);
      digitalWrite(PA4, 0);
      digitalWrite(PA5, 0);
      digitalWrite(PA6, 1);

      digitalWrite(PA0, 0);
      digitalWrite(PA1, 0);
      digitalWrite(PA7, 0);
      digitalWrite(PA8, 1);
      
      
      delay(DELAY_DURATION);

      // Flap #2
      digitalWrite(PA9, 0);
      digitalWrite(PA10, 0);
      digitalWrite(PA11, 1);
      digitalWrite(PA2, 0);

      // Flap #3
      digitalWrite(PA3, 0);
      digitalWrite(PA4, 0);
      digitalWrite(PA5, 1);
      digitalWrite(PA6, 0);

      digitalWrite(PA0, 0);
      digitalWrite(PA1, 0);
      digitalWrite(PA7, 1);
      digitalWrite(PA8, 0);
      
      delay(DELAY_DURATION);

      // Flap #2
      digitalWrite(PA9, 0);
      digitalWrite(PA10, 1);
      digitalWrite(PA11, 0);
      digitalWrite(PA2, 0);

      // Flap #3
      digitalWrite(PA3, 0);
      digitalWrite(PA4, 1);
      digitalWrite(PA5, 0);
      digitalWrite(PA6, 0);

      digitalWrite(PA0, 0);
      digitalWrite(PA1, 1);
      digitalWrite(PA7, 0);
      digitalWrite(PA8, 0);
      
      delay(DELAY_DURATION);

      // Flap #2
      digitalWrite(PA9, 1);
      digitalWrite(PA10, 0);
      digitalWrite(PA11, 0);
      digitalWrite(PA2, 0);

      // Flap #3
      digitalWrite(PA3, 1);
      digitalWrite(PA4, 0);
      digitalWrite(PA5, 0);
      digitalWrite(PA6, 0);

      digitalWrite(PA0, 1);
      digitalWrite(PA1, 0);
      digitalWrite(PA7, 0);
      digitalWrite(PA8, 0);
      
        
      delay(DELAY_DURATION);

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

