int timerCode(void) {
  //configureFlash();
  //configureClock();
  // tie Timer 16 to appropriate MCU GPIO pin
  // set A6 
  // toggle pin 6
  //togglePin(6); // CHECK

  //turn on GPIO A block
  //RCC->AHB2ENR |= (1 << 0); // Initialize GPIO A Block

  // Turn on GPIOA and GPIOB clock domains (GPIOAEN and GPIOBEN bits in AHB1ENR)
  //RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN);


  RCC->APB2ENR |= (1 << 16); // RCC -> Timer 15
  RCC->APB2ENR |= (1 << 17); // RCC -> Timer 16


  //configure port A (set three bits of AFRL to 1110)
  GPIOA->AFR[0] &= ~(0b1111 << 24);
  GPIOA->AFR[0] |= (0b1110 << 24);


  initTIM(TIM15);
  int i = 0; // seconds
  int j = 0; // minutes
  int k = 0; // hours

  while (k <= 12) {
    j = 0;
    while (j <= 60) {
      i = 0;
      while(i <= 60) {
        delay_millis(TIM15, 600);
        i++;
      }
      j++;
      printf("%d hour and %d mins have passed\n", k, j);
      spinFlapxOnce(4);
    }
    k++;
    printf("%d hour and %d mins have passed\n", k, j);
  }
}

// spins Flap X once
void spinFlapxOnce(int x) {
  int i = 0;
  while (i < 13) {
    spinFlap4();
    i++;
  }
  
}
