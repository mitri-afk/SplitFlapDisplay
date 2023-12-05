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
#include "stdio.h"

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



void spinFlap1(){
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
void spinFlap2() {
    digitalWrite(PA2, 0);
    digitalWrite(PA7, 0);
    digitalWrite(PA6, 0);
    digitalWrite(PA5, 1);

    delay(DELAY_DURATION);

    digitalWrite(PA2, 0);
    digitalWrite(PA7, 0);
    digitalWrite(PA6, 1);
    digitalWrite(PA5, 0);

    delay(DELAY_DURATION);

    digitalWrite(PA2, 0);
    digitalWrite(PA7, 1);
    digitalWrite(PA6, 0);
    digitalWrite(PA5, 0);

    delay(DELAY_DURATION);

    digitalWrite(PA2, 1);
    digitalWrite(PA7, 0);
    digitalWrite(PA6, 0);
    digitalWrite(PA5, 0);

    delay(DELAY_DURATION);
  
}
void spinFlap3(){
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

void spinFlap4() {
  digitalWrite(PB0, 0);
  digitalWrite(PB5, 0);
  digitalWrite(PB4, 0);
  digitalWrite(PB1, 1);

  delay(DELAY_DURATION);

  digitalWrite(PB0, 0);
  digitalWrite(PB5, 0);
  digitalWrite(PB4, 1);
  digitalWrite(PB1, 0);

  delay(DELAY_DURATION);

  digitalWrite(PB0, 0);
  digitalWrite(PB5, 1);
  digitalWrite(PB4, 0);
  digitalWrite(PB1, 0);

  delay(DELAY_DURATION);

  digitalWrite(PB0, 1);
  digitalWrite(PB5, 0);
  digitalWrite(PB4, 0);
  digitalWrite(PB1, 0);

  delay(DELAY_DURATION);


}


// For testing!
int mainTESTING(void){
  configureFlash();
  configureClock();

  // Turn on GPIOA and GPIOB clock domains (GPIOAEN and GPIOBEN bits in AHB1ENR)
  RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN);

  pinMode(PA0, 1);
  pinMode(PA1, 1);
  pinMode(PA3, 1);
  pinMode(PA4, 1);

  pinMode(PA5, 1);
  pinMode(PA6, 1);
  pinMode(PA7, 1);
  pinMode(PA2, 1);

  pinMode(PA9, 1);
  pinMode(PA10, 1);
  pinMode(PA12, 1);
  pinMode(PA11, 1);

  pinMode(PB0, 1);
  pinMode(PB5, 1);
  pinMode(PB4, 1);
  pinMode(PB1, 1);

  while(1) {

    spinFlap4();
  }
}

// CODE THAT MADE THE FLAPS WORK! ACTUAL MAIN IS THIS ONE. USE THIS ONE!
int mainACTUAL(void) {
  configureFlash();
  configureClock();

  // Turn on GPIOA and GPIOB clock domains (GPIOAEN and GPIOBEN bits in AHB1ENR)
  RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN);

  pinMode(PA0, 1);
  pinMode(PA1, 1);
  pinMode(PA3, 1);
  pinMode(PA4, 1);

  pinMode(PA5, 1);
  pinMode(PA6, 1);
  pinMode(PA7, 1);
  pinMode(PA2, 1);

  pinMode(PA9, 1);
  pinMode(PA10, 1);
  pinMode(PA12, 1);
  pinMode(PA11, 1);

  pinMode(PB0, 1);
  pinMode(PB5, 1);
  pinMode(PB4, 1);
  pinMode(PB1, 1);

  int i = 0;
  while (1){

    digitalWrite(PA4, 0);
    digitalWrite(PA3, 0);
    digitalWrite(PA1, 0);
    digitalWrite(PA0, 1);

    digitalWrite(PA11, 0);
    digitalWrite(PA12, 0);
    digitalWrite(PA10, 0);
    digitalWrite(PA9, 1);

    digitalWrite(PA2, 0);
    digitalWrite(PA7, 0);
    digitalWrite(PA6, 0);
    digitalWrite(PA5, 1);

    digitalWrite(PB0, 0);
    digitalWrite(PB5, 0);
    digitalWrite(PB4, 0);
    digitalWrite(PB1, 1);

    delay(DELAY_DURATION);

    digitalWrite(PA4, 0);
    digitalWrite(PA3, 0);
    digitalWrite(PA1, 1);
    digitalWrite(PA0, 0);

    digitalWrite(PA11, 0);
    digitalWrite(PA12, 0);
    digitalWrite(PA10, 1);
    digitalWrite(PA9, 0);

    digitalWrite(PA2, 0);
    digitalWrite(PA7, 0);
    digitalWrite(PA6, 1);
    digitalWrite(PA5, 0);

    digitalWrite(PB0, 0);
    digitalWrite(PB5, 0);
    digitalWrite(PB4, 1);
    digitalWrite(PB1, 0);


    delay(DELAY_DURATION);

    digitalWrite(PA4, 0);
    digitalWrite(PA3, 1);
    digitalWrite(PA1, 0);
    digitalWrite(PA0, 0);

    digitalWrite(PA11, 0);
    digitalWrite(PA12, 1);
    digitalWrite(PA10, 0);
    digitalWrite(PA9, 0);

    digitalWrite(PA2, 0);
    digitalWrite(PA7, 1);
    digitalWrite(PA6, 0);
    digitalWrite(PA5, 0);

    digitalWrite(PB0, 0);
    digitalWrite(PB5, 1);
    digitalWrite(PB4, 0);
    digitalWrite(PB1, 0);


    delay(DELAY_DURATION);

    digitalWrite(PA4, 1);
    digitalWrite(PA3, 0);
    digitalWrite(PA1, 0);
    digitalWrite(PA0, 0);

    digitalWrite(PA11, 1);
    digitalWrite(PA12, 0);
    digitalWrite(PA10, 0);
    digitalWrite(PA9, 0);

    digitalWrite(PA2, 1);
    digitalWrite(PA7, 0);
    digitalWrite(PA6, 0);
    digitalWrite(PA5, 0);

    digitalWrite(PB0, 1);
    digitalWrite(PB5, 0);
    digitalWrite(PB4, 0);
    digitalWrite(PB1, 0);

    delay(DELAY_DURATION);

    i += 1;

  }
}


int oldmain(void) {
  configureFlash();
  configureClock();
  //RCC->AHB2ENR |= (1 << 0); // turn on GPIO_A
  //RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; // turn on GPIO_B

  // Turn on GPIOA and GPIOB clock domains (GPIOAEN and GPIOBEN bits in AHB1ENR)
  RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN);
    

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


  pinMode(PA12, 1);
  pinMode(PB7, 1);
  pinMode(PB1, 1);
  pinMode(PB0, 1);



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

      //digitalWrite(PA12, 0);
      //digitalWrite(PB7, 0);
      //digitalWrite(PB6, 0);
      //digitalWrite(PB1, 1);
      
      
      
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

      //digitalWrite(PA12, 0);
      //digitalWrite(PB7, 0);
      //digitalWrite(PB6, 1);
      //digitalWrite(PB1, 0);
      
      
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

      //digitalWrite(PA12, 0);
      //digitalWrite(PB7, 1);
      //digitalWrite(PB6, 0);
      //digitalWrite(PB1, 0);
      
      
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
      
      //digitalWrite(PA12, 1);
      //digitalWrite(PB7, 0);
      //digitalWrite(PB6, 0);
      //digitalWrite(PB1, 0);
      
        
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






// Working on Hall Effect Sensor...

int hallEffect(void){ 
  // Set pin mode to input
  pinMode(PB6, 0);

  pinMode(PB0, 1);
  pinMode(PB5, 1);
  pinMode(PB4, 1);
  pinMode(PB1, 1);

  //spinFlap4();

  while(1) {
    // Continuously read sensor output from pin PB6 
    int valueLED = digitalRead(PB6);
    printf("%d value of LED: \n", valueLED);
    if(digitalRead(PB6) == 0) {
      // If we detect the magnet, turn off the LED
      //digitalWrite(PB7, 0);
      delay(500);
      //printf("Magnet Detected\n");
    } else {
    // If we don't, turn on LED
    digitalWrite(PB7, 1);
    //printf("Magnet Not Detected\n");
    }
    delay(500);
  }
}

//working to splin flap 4 with hall sensor
int spinFlap4WithHall(void) {
  configureFlash();
  configureClock();

  // Turn on GPIOA and GPIOB clock domains (GPIOAEN and GPIOBEN bits in AHB1ENR)
  RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN);


  // Motor pin assignments
  //pinMode(PA0, 1);
  //pinMode(PA1, 1);
  //pinMode(PA3, 1);
  //pinMode(PA4, 1);
    
  //pinMode(PA5, 1);
  //pinMode(PA6, 1);
  //pinMode(PA7, 1);
  //pinMode(PA2, 1);
    
  //pinMode(PA9, 1);
  //pinMode(PA10, 1);
  //pinMode(PA12, 1);
  //pinMode(PA11, 1);
    
  pinMode(PB0, 1);
  pinMode(PB5, 1);
  pinMode(PB4, 1);
  pinMode(PB1, 1);

  // Set pin mode to input
  pinMode(PB6, 0);

  while(1) {
    spinFlap4();
    int valueLED = digitalRead(PB6);
    printf("%d value of LED: \n", valueLED);
    if(digitalRead(PB6) == 0) {
      // If we detect the magnet, turn off the LED
      //digitalWrite(PB7, 0);

      // Wait while magnet is detected for a bit for us to see it stop
      delay(50000);

      // Spin past the magnet a bit so we dont detect it anymore.
      int i = 0;
      while(i < 364){ //60
        spinFlap4();
        i++;
      }
      delay(50000);
      
      //printf("Magnet Detected\n");
    }
  }
}


int main(void){
  configureFlash();
  configureClock();

  // Turn on GPIOA and GPIOB clock domains (GPIOAEN and GPIOBEN bits in AHB1ENR)
  RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN);


  // Motor pin assignments
  pinMode(PA0, 1);
  pinMode(PA1, 1);
  pinMode(PA3, 1);
  pinMode(PA4, 1);
    
  pinMode(PA5, 1);
  pinMode(PA6, 1);
  pinMode(PA7, 1);
  pinMode(PA2, 1);
    
  pinMode(PA9, 1);
  pinMode(PA10, 1);
  pinMode(PA12, 1);
  pinMode(PA11, 1);
    
  pinMode(PB0, 1);
  pinMode(PB5, 1);
  pinMode(PB4, 1);
  pinMode(PB1, 1);

  // Set pin mode to input
  pinMode(PB7, 0);
  pinMode(PB6, 0);
  pinMode(PB3, 0);
  pinMode(PC14, 0);

  //to test the last flap 
  while (1) {
    printf("%d: \n", digitalRead(PB7)); 
  }


  int i = 0;
  while(i < 364){ //60
    spinFlap2();
    //spinFlap3();
    //spinFlap4();
    i++;
  }
  delay(50000);

  while(1) {
    spinFlap2();
    //spinFlap3();
    //spinFlap4();

    int valueLED3 = digitalRead(PB7);
    int valueLED4 = digitalRead(PB6);

    while (1) {

      while(digitalRead(PB3) != 0) {
        spinFlap2();
        printf("%d split flap 2: \n", digitalRead(PB3));
      }

      delay(50000);
      int j = 0;
      while (j < 140) {
        spinFlap2();
        j++;

      }

    }


    while((digitalRead(PB7) != 0)) {
      spinFlap3();
      printf("%d split flap 3: \n", digitalRead(PB7));
    }

    while(digitalRead(PB6) != 0) {
      spinFlap4();
      printf("%d split flap 4: \n", digitalRead(PB6));
    }

    printf("Reached here");
    delay(50000);

    while (1) {
      spinFlap2();
      //spinFlap3();
      //spinFlap4();

    }

    //printf("%d value of LED for Flap 3: \n", valueLED3);
    //printf("%d value of LED for Flap 4: \n", valueLED4);

    //// While flaps are not home
    //while((digitalRead(PB7) && digitalRead(PB6)) != 0) {
    //  // Spin the flaps
    //  spinFlap3();
    //  spinFlap4();

    //  // If flap 3 or flap 4 is home
    //  if(digitalRead(PB7) == 0 | digitalRead(PB6) == 0) {
    //    // Spin flap 4 if not at home
    //    while(digitalRead(PB6) != 0) {
    //      //printf("%d value of LED for Flap 4: \n", valueLED4);
    //      spinFlap4();
    //    }
    //    // Spin flap 3 if not at home
    //    while(digitalRead(PB7) != 0) {
    //      printf("%d value of LED for Flap 3: \n", valueLED3);
    //      printf("%d value of LED for Flap 4: \n", valueLED4);

    //      spinFlap3();
    //    }
    //  }

    //// When all are home. Pause for a bit.
    //delay(50000);
    //int i = 0;
    //while(i < 1000) {
    //  spinFlap3();
    //  spinFlap4();
    //  ++i;
    //}
 // }



    //if(digitalRead(PB7) == 0) {
    //  // Wait while magnet is detected for a bit for us to see it stop
    //  delay(50000);

    //  // Spin past the magnet a bit so we dont detect it anymore.
    //  int i = 0;
    //  while(i < 364){
    //    spinFlap3();
    //    i++;
    //  }
    //   delay(50000);
    //}

    //if(digitalRead(PB6) == 0) {
    //  // Wait while magnet is detected for a bit for us to see it stop
    //  delay(50000);

    //  // Spin past the magnet a bit so we dont detect it anymore.
    //  int i = 0;
    //  while(i < 364){
    //    spinFlap4();
    //    i++;
    //  }
    //   delay(50000);
    //}
  }
}





/*************************** End of file ****************************/

