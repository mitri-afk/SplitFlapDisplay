# Split Flap Clock Project
Welcome to the Split Flap Clock Project repository! This project merges the charm of vintage split flap displays with modern technology to create a fun timepiece. The clock features an FPGA-controlled LED display and four split-flaps controlled by an MCU.

Visit our project website [here](https://nyeluri53.github.io/E155-Final-Project-Website/)!

## Overview
Our split flap clock displays the time in a 24-hour format, arranged as "hour hour minute minute." The FPGA code controls the dynamic LED display, presenting a sun and moon emoji to indicate the time of day. Simultaneously, the MCU code controls the movement of the split-flaps with the use of stepper motors and hall effect sensors for positional feedback.

## Features
- **Split Flap Display:** Four flap units provide an intuitive representation of time, with the vintage charm of split flap movements.
  
- **LED Indicator:** The clock includes a dual-mode LED display that dynamically updates to show a sun or moon emoji, giving users an instant visual cue of the time of day.
  
- **FPGA and MCU Integration:** The project seamlessly integrates FPGA code for LED control and MCU code for motor and sensor control, achieving a unique and synchronized timekeeping experience.

## Getting Started
This project was created using the [Lattice Radiant Design Software](https://www.latticesemi.com/LatticeRadiant?pr031521) environment to develop our SystemVerilog modules and program our FPGA (iCE40 Family). We also used ModelSim to validate our SystemVerilog designs using testbenches. For our STM32L432KCU microcontoller, we used Segger Embedded Studio to write the code and program it.

## Usage
All the SystemVerilog files (.sv) are used for programming the FPGA and the C files (.c) are used for the microcontroller. Be sure to download the MCU specific source libraries in the src folder!

## MCU to FPGA SPI Communication Signal and LED Display Table
The table below shows what the MCU sends to the FPGA through SPI and what this causes the LED Display to depict depending on the time and mode selected.

<img width="293" alt="Screen Shot 2023-12-07 at 11 36 00 PM" src="https://github.com/mitri-afk/SplitFlapDisplay/assets/123135076/e4f23fc7-e860-4039-a109-fad1b3882e35">
 


