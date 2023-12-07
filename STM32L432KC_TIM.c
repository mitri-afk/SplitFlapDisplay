// STM32F401RE_TIM.c
// TIM functions

#include "STM32L432KC_TIM.h"
#include "STM32L432KC_RCC.h"




#define SystemCoreClock 4e6


void initTIM(TIM_TypeDef * TIMx){
  // Set prescaler to give 1 ms time base
  uint32_t psc_div = (uint32_t) ((SystemCoreClock/1e3));

  // Set prescaler division factor
  //TIMx->PSC = (psc_div - 1);
  //TIMx->PSC |= (0b1111010 << 0);
  TIMx->PSC &= 0; //clear prescaler bits
  TIMx->PSC = 79999; // set prescaler to be 7999 to make CLK_INT 1kHz

  // Generate an update event to update prescaler value
  TIMx->EGR |= 1;
  // Enable counter
  TIMx->CR1 |= 1; // Set CEN = 1
}

void delay_millis(TIM_TypeDef * TIMx, uint32_t ms){
  uint32_t cyc = (ms*9) - 1; // 9 is MY TEMPO
  TIMx->ARR = cyc;// Set timer max count
  TIMx->EGR |= 1;     // Force update
  TIMx->SR &= ~(0x1); // Clear UIF
  TIMx->CNT = 0;      // Reset count

  while(!(TIMx->SR & 1)); // Wait for UIF to go high
}

//void initTIM(TIM_TypeDef * TIMx){

////clear CR1 bit
//TIMx->CR1 &= (1 << 0); 


////set OCxM bits to mode 110
//TIMx->CCMR1 &= ~(0b111 << 4);   //clear OCxM bits
//TIMx->CCMR1 |= (0b110 << 4);    // set mode to 110


//TIMx->CCMR1 |= (1 << 3); // set OC1PE bit to 1
//TIMx->CR1   |= (1 << 7); // set ARPE bit in CR1 Register


//TIMx->PSC &= 0; //clear prescaler bits
//TIMx->PSC |= (0b1111010 << 0); // set prescaler to be 122 to make CLK_INT 1kHz


//TIMx->CCER |= (1 << 0);  //set CC1E bit to 1 (bit 4 of CCER register)
//TIMx->BDTR |= (1 << 15); //set MOE bit to 1


//TIMx->EGR |= (1 << 0);  // initialize all the registers by setting the UG bit in the TIMx_EGR register
//TIMx->CR1 |= (1 << 0);  // set CEN to 1 so that clk is set to CLK_INT


//}

//void delay_millis(TIM_TypeDef * TIMx, uint32_t ms){
//// use TIM15 here


//if (ms < 1) {
//  return;
//}

////disable slave mode
//TIMx->SMCR &= ~(0b1 << 16);  //set SMS[3]  bit 16 to 0 
//TIMx->SMCR &= ~(0b111 << 0); //set SMS[2:0] bit 0, 1, 2 to 0



////set CEN to 0 for TIM15 (turn off counter)
//TIMx->CR1 &= ~(1 << 0);

////define cycles 
//uint32_t cyc = (ms*9) - 1; // 9 is MY TEMPO

////load cyc to ARR
//TIMx->ARR &= 0; //clear ARR bits
//TIMx->ARR |= ms; //set ARR to cyc

//TIMx->PSC &= 0; //clear prescaler bits
//TIMx->PSC = 79999; // set prescaler to be 7999 to make CLK_INT 1kHz

////set update event (SR bit 0) to 0
//TIMx->SR &= ~(1 << 0);

////before starting the timer, reset counter
//TIMx->CNT &= 0;

////set CEN to 1 for TIM15
//TIMx->CR1 |= (1 << 0);

////while loop checking for flag if 0
//while((TIMx->SR & 1) == 0);

////set CEN to 0 for TIM15
//TIMx->CR1 &= ~(1 << 0);


//}

//void initTIM(TIM_TypeDef * TIMx){
//  // Set prescaler to give 1 ms time base
//  uint32_t psc_div = (uint32_t) ((SystemCoreClock/1e3));
//  printf("PSC_DIV is: %lu\n", psc_div);

//  // Set prescaler division factor
//  TIMx->PSC = (psc_div - 1);
//  // Generate an update event to update prescaler value
//  TIMx->EGR |= 1;
//  // Enable counter
//  TIMx->CR1 |= 1; // Set CEN = 1
//}

//void delay_millis(TIM_TypeDef * TIMx, uint32_t ms){
//  TIMx->ARR = ms;// Set timer max count
//  printf("Setting ARR to %lu\n", ms);
//  TIMx->EGR |= 1;     // Force update
//  TIMx->SR &= ~(0x1); // Clear UIF
//  TIMx->CNT = 0;      // Reset count
  
//  printf("Before loop: CNT = %lu, SR = %lu\n", TIMx->CNT, TIMx->SR);
//  while(!(TIMx->SR & 1)); // Wait for UIF to go high
//  printf("After loop: CNT = %lu, SR = %lu\n", TIMx->CNT, TIMx->SR);
//}

