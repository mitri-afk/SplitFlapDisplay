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
#include "STM32L432KC_TIM.h"

/*********************************************************************
*
*       main()
*
*  Function description
*   Application entry point.
*/

void delay(int cycles);
#define DELAY_DURATION  120

void delay(int cycles) {
   while (cycles-- > 0) {
      volatile int x=200;
      while (x-- > 0)
         __asm("nop");
   }
}


void initializeFlap1() {
  pinMode(PA0, 1);
  pinMode(PA1, 1);
  pinMode(PA3, 1);
  pinMode(PA4, 1);
}

void initializeFlap2() {
  pinMode(PA5, 1);
  pinMode(PA6, 1);
  pinMode(PA7, 1);
  pinMode(PA2, 1);
}

void initializeFlap2UsingPB3() {
  pinMode(PB3, 1);
  pinMode(PA6, 1);
  pinMode(PA7, 1);
  pinMode(PA2, 1);
}

void initializeFlap3() {
  pinMode(PA9, 1);
  pinMode(PA10, 1);
  pinMode(PA12, 1);
  pinMode(PA11, 1);
}


void initializeFlap4() {
  pinMode(PB0, 1);
  pinMode(PB5, 1);
  pinMode(PB4, 1);
  pinMode(PB1, 1);
}

void disableFlap1() {
  digitalWrite(PA0, 0);
  digitalWrite(PA1, 0);
  digitalWrite(PA3, 0);
  digitalWrite(PA4, 0);
  pinMode(PA8, 1);
}

void disableFlap2() {
  digitalWrite(PA5, 0);
  digitalWrite(PA6, 0);
  digitalWrite(PA7, 0);
  digitalWrite(PA2, 0);
  pinMode(PB3, 1);
}


void disableFlap3() {
  digitalWrite(PA11, 0);
  digitalWrite(PA12, 0);
  digitalWrite(PA10, 0);
  digitalWrite(PA9, 0);
  pinMode(PB7, 0);
}


void disableFlap4() {
  digitalWrite(PB0, 0);
  digitalWrite(PB5, 0);
  digitalWrite(PB4, 0);
  digitalWrite(PB1, 0);
  pinMode(PB6, 0);
}
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

void spinFlap2WithPB3() {
    digitalWrite(PA2, 0);
    digitalWrite(PA7, 0);
    digitalWrite(PA6, 0);
    digitalWrite(PB3, 1);

    delay(DELAY_DURATION);

    digitalWrite(PA2, 0);
    digitalWrite(PA7, 0);
    digitalWrite(PA6, 1);
    digitalWrite(PB3, 0);

    delay(DELAY_DURATION);

    digitalWrite(PA2, 0);
    digitalWrite(PA7, 1);
    digitalWrite(PA6, 0);
    digitalWrite(PB3, 0);

    delay(DELAY_DURATION);

    digitalWrite(PA2, 1);
    digitalWrite(PA7, 0);
    digitalWrite(PA6, 0);
    digitalWrite(PB3, 0);

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



// Function to spin to example hours, so hour 0 2
void spinToHours() {
  initializeFlap1();
  int i = 0;
  while(i < 390) {
    spinFlap1();
    i++;
  }

  initializeFlap2();
  i = 0;
  while(i < 429) {
    spinFlap2();
    i++;
  }
}

// Function to spin to example minutes, so minutes 0 2
void spinToMinutes() {
  initializeFlap3();
  int i = 0;
  while(i < 390) {
    spinFlap3();
    i++;
  }

  initializeFlap4();
  i = 0;
  while(i < 429) {
    spinFlap4();
    i++;
  }
}




// Sends flap to home state
int calibrateFlap1() {
  initializeFlap1();
  pinMode(PA8, 0); // Flap 1 Hall Sensor (works with
  while(digitalRead(PA8) != 0) {
    printf("1: %d \n", digitalRead(PA8));
    spinFlap1();
  }
  //disableFlap1();
  return 1;
}

int calibrateFlap2() {
  initializeFlap2();
  pinMode(PB3, 0); // Flap 2 Hall Sensor (works with spinFlap2)
  while(digitalRead(PB3) != 0) {
    printf("2: %d \n", digitalRead(PB3));
    spinFlap2();
  }
  //disableFlap2();
  return 1;
}

int calibrateFlap2UsingPB3forMotor() {
 initializeFlap2UsingPB3();
 pinMode(PA5, 0);
 while(digitalRead(PA5) != 0) {
    printf("2: %d \n", digitalRead(PA5));
    spinFlap2WithPB3();
  }
  return 1;
}

int calibrateFlap3() {
  initializeFlap3();
  pinMode(PB7, 0); // Flap 3 Hall Sensor (works with spinFlap3, works with spinflap4)
  while(digitalRead(PB7) != 0) {
    printf("3: %d \n", digitalRead(PB7));
    spinFlap3();
  }
  //disableFlap3();
  return 1;
}

int calibrateFlap4() {
  initializeFlap4();
  printf("Initialized\n");
  pinMode(PB6, 0); // Flap 4 Hall Sensor (Works with spinflap1, not spinflap2, works with spinflap3, works with spinflap4)
  printf("%d\n", digitalRead(PB6));
  while(digitalRead(PB6) != 0) {
    printf("4: %d \n", digitalRead(PB6));
    spinFlap4();
  } 
  //disableFlap4();
  return 1;
}


// spins Flap X once
void spinFlap4Once() {
  int i = 0;
  while (i < 13) {
    spinFlap4();
    i++;
  }
  
}

void spinFlap4to0() {
  int i = 0;
  while(i < 369) {
    spinFlap4();
    spinFlap3();
    ++i;
  }

}

void spinFlap3Once() {
  int i = 0;
  while (i < 13) {
    spinFlap3();
    i++;
  }
  
}


int timerCode(int hr, int min) {

  // Turn on GPIOA and GPIOB clock domains (GPIOAEN and GPIOBEN bits in AHB1ENR)
  //RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN);


  RCC->APB2ENR |= (1 << 16); // RCC -> Timer 15
  RCC->APB2ENR |= (1 << 17); // RCC -> Timer 16


  //configure port A (set three bits of AFRL to 1110)
  GPIOA->AFR[0] &= ~(0b1111 << 24);
  GPIOA->AFR[0] |= (0b1110 << 24);


  initTIM(TIM15);
  int second = 0; // seconds
  int minute = min; // minutes
  int hour = hour; // hours
  
  hour = hour % 24;
  while (hour < 24) {
    minute = minute % 60;
    while (minute < 60) {
      second = 0;
      while(second <= 60) {
        delay_millis(TIM15, 600);
        second++;
      }
      minute++;
      printf("%d hour and %d mins have passed\n", hour, minute);
      if (minute % 10 == 0) {
        //spinFlap4Once();
        calibrateFlap4();
        spinFlap3Once();
        //spinFlap4to0();
        //spinFlap3();
      } else {
        spinFlap4Once();
      }
    }
    hour++;
    printf("%d hour and %d mins have passed\n", hour, minute);
  }
}


void spinToMin4(int x){
  //int var = 13 * x;
  int z = 0;
  for(int j = 0; j < x; j++) {
    z = 0;
    while(z < 13) { 
      spinFlap4();
      ++z;
    }
    delay(50000);
  }
}

void spinToMin3(int x){
  int z = 0;
  for(int j = 0; j < x; j++) {
    z = 0;
    while(z < 13) { 
      spinFlap3();
      ++z;
    }
    delay(50000);
  }
}


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



int main(void) {
  configureFlash();
  configureClock();

  // Turn on GPIOA and GPIOB clock domains (GPIOAEN and GPIOBEN bits in AHB1ENR)
  RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN);
  
  //initializeFlap1();
  //initializeFlap2();
  initializeFlap3();
  initializeFlap4();
  int i = 0;
  while (i < 80) {
    //spinFlap1();
    //spinFlap2();
    spinFlap3();
    spinFlap4();
    i++;
  }

  
  int hour1 = 0;
  int hour2 = 5;
  int min3 = 4;
  int min4 = 9;
  int combinedMin = 49;

  //calibrateFlap4();
  //calibrateFlap3();

  
  
  //initializeFlap4();
  //timerCode();
  //printf("initialized");


  //delay(90000);
  //while(1) {
  //  double i = 0;
  //  while(i < 12) {
  //    spinFlap4();
  //    ++i;
  //  }
  //  delay(50000);

  while(1) {
    // Spin flap to its home
    calibrateFlap4();
    calibrateFlap3();
    //calibrateFlap2();
    //printf("Finished Calibration of 2\n");
    //calibrateFlap1();

    //printf("reached");
    // Pause for us to see it reach home 
    spinToMin4(min4);
    spinToMin3(min3);
    //spinToHour2(hour2);
    //printf("Finished hour2");

    delay(50000);

    //Spin flaps to 0
    //int i = 0;
    //while(i < 369) {
    //  spinFlap4();
    //  //spinFlap3();
    //  ++i;
    //}
    timerCode(hour2, combinedMin);
  }

}

  // Slowly count to 9
  //int z = 0;
  //for(int j = 0; j < 9; j++) {
  //  z = 0;
  //  while(z < 13) { 
  //    spinFlap4();
  //    ++z;
  //  }
  //  delay(50000);
  //}

  // Move from 9 to home
  //z = 0;
  //while(z < 17) { 
  //    spinFlap4();
  //    ++z;
  //  }

  // Repeat


  //while(1) {
  //  while(i < 13) {
  //  }
  //  spinFlap1()
  //  delay(50000);
  //}
 
  //debugging...
  //spinToHours();


  //spinToHours();

  //spinToMinutes();

  //calibrateFlap1();
  //printf("Flap 1 done");
  //delay(50000);

  //calibrateFlap2();
  //printf("Flap 2 done");
  //delay(50000);

  //initializeFlap3();
  //int i = 0;
  //while (i < 100) {
  //  spinFlap3();
  //  i++;
  //}
  //printf("reached");

  //calibrateFlap3();
  //printf("Flap 3 done");
  //delay(50000);
  

  //calibrateFlap4();
  //printf("Flap 4 done");
  //delay(50000);
  
  //spinToMinutes();
//}


/*
The purpose of this function was to test whether or not setting the sensor
pins to things other than read mode, such as input, fixes the issue where 
hall effect sensors stop reading. The code currently o
*/
//int mainDiscard(void){
//  configureFlash();
//  configureClock();

//  // Turn on GPIOA and GPIOB clock domains (GPIOAEN and GPIOBEN bits in AHB1ENR)
//  RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN);


//  initializeFlap2UsingPB3();

//  // initializeFlap2
//  //pinMode(PA6, 1);
//  //pinMode(PA7, 1);
//  //pinMode(PA2, 1);
//  //pinMode(PB3, 1);

//  //pinMode(PA5, 1); //PROBLEMATIC using pb3 instead?

//  //initializeFlap3();
//  //initializeFlap4();




//  // read pins
//  //pinMode(PA8, 0);
//  //pinMode(PA5, 0); //swapped from PB3 (so PB3 which was for sensor is for flap2 motor) pa5 is now reading
//  //pinMode(PB7, 0);
//  //pinMode(PB6, 0);

// //calibrateFlap1();
// calibrateFlap2UsingPB3forMotor();
// //calibrateFlap2();
//}

  ////Test if sensor 2 works with flap 2
  //while(1){
  //  int valuePB3 = digitalRead(PB3);
  //  printf("%d value of sensor 2: \n", valuePB3);
  //  spinFlap2();
  //  if(valuePB3 == 0) {
  //    delay(50000);
  //    printf("found home");
  //  }
  //}


  ////Test if sensor 2 works with flap 2 using PB3 for motor and PA5
  //while(1){
  //  int valuePA5 = digitalRead(PA5);
  //  printf("%d value of sensor 2: \n", valuePA5);
  //  spinFlap2WithPB3();
  //  if(valuePA5 == 0) {
  //    delay(50000);
  //    printf("found home");
  //  }
  //}

  ////flap3 and read its sensor
  //while(1){
  //  int valuePB7 = digitalRead(PB7);
  //  printf("%d value of sensor 3: \n", valuePB7);
  //  spinFlap3();
  //  if(valuePB7 == 0) {
  //    delay(50000);
  //    int i = 0;
  //    while(i < 40) {
  //      spinFlap3();
  //      ++i;
  //    }
  //    printf("found home");
  //  }
  //}




/*************************** End of file ****************************/

