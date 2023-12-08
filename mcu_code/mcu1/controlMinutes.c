/*
File    : controlMinutes.c
Purpose : Code for running the two split flaps that control minutes.

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
void initializeFlap1(void);
void initializeFlap2(void);
void initializeFlap3(void);
void initializeFlap4(void);
void spinFlap1(void);
void spinFlap2(void);
void spinFlap3(void);
void spinFlap4(void); 
int calibrateFlap1(void);
int calibrateFlap2(void);
int calibrateFlap3(void);
int calibrateFlap4(void);
int timerCode(int hr, int min);
void spinToMin4(int x);
void spinToMin3(int x);
void spinToHour2(int x);
void spinToHour1(int x);

#define DELAY_DURATION  120



// delay function
void delay(int cycles) {
   while (cycles-- > 0) {
      volatile int x=200;
      while (x-- > 0)
         __asm("nop");
   }
}

//initialize pins need to spin motor for Flap 1
void initializeFlap1() {
  pinMode(PA0, 1);
  pinMode(PA1, 1);
  pinMode(PA3, 1);
  pinMode(PA4, 1);
}

//initialize pins need to spin motor for Flap 2
void initializeFlap2() {
  pinMode(PA5, 1);
  pinMode(PA6, 1);
  pinMode(PA7, 1);
  pinMode(PA2, 1);
}


//initialize pins need to spin motor for Flap 3
void initializeFlap3() {
  pinMode(PA9, 1);
  pinMode(PA10, 1);
  pinMode(PA12, 1);
  pinMode(PA11, 1);
}


//initialize pins need to spin motor for Flap 3
void initializeFlap4() {
  pinMode(PB0, 1);
  pinMode(PB5, 1);
  pinMode(PB4, 1);
  pinMode(PB1, 1);
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



// Sends flap 1 to home state
int calibrateFlap1() {
  initializeFlap1();
  pinMode(PA8, 0); // Flap 1 Hall Sensor
  while(digitalRead(PA8) != 0) { //read for hall sensor detection
    printf("1: %d \n", digitalRead(PA8));
    spinFlap1();
  }
  //disableFlap1();
  return 1;
}


// Sends flap 2 to home state
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

// Sends flap 3 to home state
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


// Sends flap 3 to home state
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


//spins Flap 1 once
void spinFlap1Once() {
  int i = 0;
  while (i < 13) {
    spinFlap1();
    i++;
  }
  
}

//spins Flap 2 once
void spinFlap2Once() {
  int i = 0;
  while (i < 13) {
    spinFlap2();
    i++;
  }
  
}


// spins Flap 3 once
void spinFlap3Once() {
  int i = 0;
  while (i < 13) {
    spinFlap3();
    i++;
  }
  
}

// spins Flap 4 once
void spinFlap4Once() {
  int i = 0;
  while (i < 13) {
    spinFlap4();
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
  
  while(1){
    hour = hour % 24;
    while (hour < 24) {
      minute = minute % 60;
      while (minute < 60) {
        second = 0;
        while(second <= 60) {
          delay_millis(TIM15, 600); // delay for one sec 
          second++;
        }
        minute++;
        printf("%d hour and %d mins have passed\n", hour, minute);
        if (minute % 10 == 0) {
          //spinFlap4Once();
          calibrateFlap4();
          printf("finished callibrating");
          spinFlap3Once();
          if (minute / 10 == 6) {
            printf("Time is xx:59"); //if minutes are xx:59, reset to xx:00
            //spinFlap2Once();
            calibrateFlap3();
          }
        } else {
          spinFlap4Once();
        }
      }
      hour++;
      printf("%d hour and %d mins have passed\n", hour, minute); 
    }
  }
}



//Spins to flap labeled x from Flap 4's home state
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

//Spins to flap labeled x from Flap 3's home state
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



int main(void) {
  configureFlash();
  configureClock();

  // Turn on GPIOA and GPIOB clock domains (GPIOAEN and GPIOBEN bits in AHB1ENR)
  RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN);
  
  //initializeFlap1();
  //initializeFlap2();
  initializeFlap3(); 
  initializeFlap4();

  /*Spin Flap 3 and 4 for calibration */
  int i = 0;
  while (i < 80) {
    //spinFlap1();
    //spinFlap2();
    spinFlap3();
    spinFlap4();
    i++;
  }

  // manually input real time
  //int hour1 = 1;
  //int hour2 = 2;
  int combinedHour = 12;
  int min3 = 5;
  int min4 = 9;
  int combinedMin = 59;


  while(1) {
    // Spin flap 4 and 3 to home state
    calibrateFlap4();
    calibrateFlap3();
    //calibrateFlap1();
    //calibrateFlap1();

    // Spin to real time 
    spinToMin4(min4);
    spinToMin3(min3);
    //spinToHour2(hour2);
    //spinToHour1(hour1);

    delay(50000);

    // start the timer
    timerCode(combinedHour, combinedMin);
  }

}
  
  














/*************************** End of file ****************************/

