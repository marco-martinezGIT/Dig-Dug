/*
 * Switch.cpp
 *
 *  Created on: Nov 5, 2023
 *      Author:
 */
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "../ECE319K_Lab9H/GameObjects/Character.h"
#include "ti/devices/msp/m0p/mspm0g350x.h"
// LaunchPad.h defines all the indices into the PINCM table
void Switch_Init(void){
    // write this
  // IOMUX->SECCFG.PINCM[PA28INDEX] = 0x00040081; // input, no pull
  // IOMUX->SECCFG.PINCM[PA27INDEX] = 0x00040081; // input, no pull
  // IOMUX->SECCFG.PINCM[PA16INDEX] = 0x00040081; // input, no pull
  // IOMUX->SECCFG.PINCM[PA15INDEX] = 0x00040081; // input, no pull

  // IOMUX->SECCFG.PINCM[PB0INDEX] = 0x00040081; //input x LEFT
  // IOMUX->SECCFG.PINCM[PB1INDEX] = 0x00040081; //input x RIGHT
  // IOMUX->SECCFG.PINCM[PB2INDEX] = 0x00040081; //input y UP
  // IOMUX->SECCFG.PINCM[PB3INDEX] = 0x00040081; //input y DOWN
  
  IOMUX->SECCFG.PINCM[PA28INDEX] = 0x00040081; //input x LEFT
  IOMUX->SECCFG.PINCM[PA27INDEX] = 0x00040081; //input x RIGHT
  IOMUX->SECCFG.PINCM[PA31INDEX] = 0x00040081; //input y UP
  IOMUX->SECCFG.PINCM[PA26INDEX] = 0x00040081; //input y DOWN


}
// return current state of switches
uint32_t Switch_In(void){
    // write this
  uint32_t data = GPIOA->DIN31_0;
  data = ((data>>15)&0x03) | ((data&((1<<28)|(1<<27)))>>25);
  return data; // return 0; //replace this your code
}

bool switchActive(int pinIndex){
  return (GPIOA->DIN31_0 >> pinIndex) & 0x01;
}