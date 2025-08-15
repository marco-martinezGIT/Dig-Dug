// Lab9HMain.cpp
// Runs on MSPM0G3507
// Lab 9 ECE319H
// Your name Swajal Padhi
// Last Modified: 12/26/2024

#include <cstdint>
#include <cstdio>
//#include <machine/_stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/ST7735.h"
#include "../inc/Clock.h"
#include "../inc/LaunchPad.h"
#include "../inc/TExaS.h"
#include "../inc/Timer.h"
//AAA
#include "GameObjects/Enemy.h"
//AAA
#include "../inc/SlidePot.h"
#include "../inc/DAC5.h"
//#include "../inc/ADC.h"
#include "GameObjects/Tile.h"
#include "SmallFont.h"  
#include "LED.h"
#include "Switch.h"
#include "Sound.h"
#include "images/images.h" 
#include "../ECE319K_Lab9H/BitResource.h"
#include "GameObjects/Character.h"  
#include "GameObjects/Displayable.h" 
#include "GameObjects/GameBoard.h"
//AAA
#include "Constants.h"
#include "BFS.h"
//AAA
#include "ti/devices/msp/m0p/mspm0g350x.h"
//AAA
#include <queue>
#include <utility>
#include "Game.h"
//AAA

extern "C" void __disable_irq(void);  
extern "C" void __enable_irq(void);
extern "C" void TIMG12_IRQHandler(void);

const char Text0_E[] = "Playing!          ";
const char Text0_S[] = "¡Jugando!         ";
const char Text1_E[] = "Paused!           ";
const char Text1_S[] = "¡Pausado!         ";
const char Text2_E[] = "Resuming in 3!    ";
const char Text2_S[] = "¡Reanudando en 3! ";
const char Text3_E[] = "Resuming in 2!    ";
const char Text3_S[] = "¡Reanudando en 2! ";
const char Text4_E[] = "Resuming in 1!    ";
const char Text4_S[] = "¡Reanudando en 1! ";
const char *texts[2][5] = {{Text0_E, Text1_E, Text2_E, Text3_E, Text4_E}, {Text0_S, Text1_S, Text2_S, Text3_S, Text4_S}};

bool languageSelection = true;
uint8_t language;

//AAA
Character* user;
Enemy* monster;

bool bfsFlag = false;
uint32_t g12Counter = 0;
uint32_t score = 0;
//AAA

bool flag = false;
// ****note to ECE319K students**** 
// the data sheet says the ADC does not work when clock is 80 MHz
// however, the ADC seems to work on my boards at 80 MHz
// I suggest you try 80MHz, but if it doesn't work, switch to 40MHz
void PLL_Init(void){ // set phase lock loop (PLL)
  // Clock_Init40MHz(); // run this line for 40MHz
  Clock_Init80MHz(0);   // run this line for 80MHz
}

//AAA
volatile uint32_t timerCounter = 0;
//AAA

uint32_t M=1;
uint32_t Random32(void){
  M = 1664525*M+1013904223;
  return M;
}
uint32_t Random(uint32_t n){
  return (Random32()>>16)%n;
}

SlidePot Sensor(1500,0); // copy calibration from Lab 7

// games  engine runs at 30Hz
void TIMG12_IRQHandler(void){uint32_t pos,msg;
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
// game engine goes here
    // 1) sample slide pot
    // 2) read input switches
    // 3) move sprites
    flag = true;
    ++g12Counter;
    // ST7735_DrawBitmap(60, 60, taizo_stand, 16, 16);

    // 4) start sounds
    // 5) set semaphore
    // NO LCD OUTPUT IN INTERRUPT SERVICE ROUTINES

    GPIOB->DOUTTGL31_0 = GREEN; // toggle PB27 (minimally intrusive debugging)
  }
}
uint8_t TExaS_LaunchPadLogicPB27PB26(void){
  return (0x80|((GPIOB->DOUT31_0>>26)&0x03));
}

typedef enum {English, Spanish, Portuguese, French} Language_t;
Language_t myLanguage=English;
typedef enum {HELLO, GOODBYE, LANGUAGE} phrase_t;
const char Hello_English[] ="Hello";
const char Hello_Spanish[] ="\xADHola!";
const char Hello_Portuguese[] = "Ol\xA0";
const char Hello_French[] ="All\x83";
const char Goodbye_English[]="Goodbye";
const char Goodbye_Spanish[]="Adi\xA2s";
const char Goodbye_Portuguese[] = "Tchau";
const char Goodbye_French[] = "Au revoir";
const char Language_English[]="English";
const char Language_Spanish[]="Espa\xA4ol";
const char Language_Portuguese[]="Portugu\x88s";
const char Language_French[]="Fran\x87" "ais";
const char *Phrases[3][4]={ 
  {Hello_English,Hello_Spanish,Hello_Portuguese,Hello_French},
  {Goodbye_English,Goodbye_Spanish,Goodbye_Portuguese,Goodbye_French},
  {Language_English,Language_Spanish,Language_Portuguese,Language_French}
};
// use main1 to observe special characters
int main1(void){ // main1 
    char l;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init(); 
  ST7735_InitPrintf();
  ST7735_FillScreen(0x0000);            // set screen to black
  for(int myPhrase=0; myPhrase<= 2; myPhrase++){
    for(int myL=0; myL<= 3; myL++){
         ST7735_OutString((char *)Phrases[LANGUAGE][myL]);
      ST7735_OutChar(' ');
         ST7735_OutString((char *)Phrases[myPhrase][myL]);
      ST7735_OutChar(13);
    }
  }
  Clock_Delay1ms(3000);
  ST7735_FillScreen(0x0000);       // set screen to black
  l = 128;
  while(1){
    Clock_Delay1ms(2000);
    for(int j=0; j < 3; j++){
      for(int i=0;i<16;i++){
        ST7735_SetCursor(7*j+0,i);
        ST7735_OutUDec(l);
        ST7735_OutChar(' ');
        ST7735_OutChar(' ');
        ST7735_SetCursor(7*j+4,i);
        ST7735_OutChar(l);
        l++;
      }
    }
  }
}

// use main2 to observe graphics
int main2(void){ // main2
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_DrawBitmap(22, 159, PlayerShip0, 18,8); // player ship bottom
  ST7735_DrawBitmap(53, 151, Bunker0, 18,5);
  ST7735_DrawBitmap(42, 159, PlayerShip1, 18,8); // player ship bottom
  ST7735_DrawBitmap(62, 159, PlayerShip2, 18,8); // player ship bottom
  ST7735_DrawBitmap(82, 159, PlayerShip3, 18,8); // player ship bottom
  ST7735_DrawBitmap(0, 9, SmallEnemy10pointA, 16,10);
  ST7735_DrawBitmap(20,9, SmallEnemy10pointB, 16,10);
  ST7735_DrawBitmap(40, 9, SmallEnemy20pointA, 16,10);
  ST7735_DrawBitmap(60, 9, SmallEnemy20pointB, 16,10);
  ST7735_DrawBitmap(80, 9, SmallEnemy30pointA, 16,10);

  for(uint32_t t=500;t>0;t=t-5){
    SmallFont_OutVertical(t,104,6); // top left
    Clock_Delay1ms(50);              // delay 50 msec
  }
  ST7735_FillScreen(0x0000);   // set screen to black
  ST7735_SetCursor(1, 1);
  ST7735_OutString((char *)"GAME OVER");
  ST7735_SetCursor(1, 2);
  ST7735_OutString((char *)"Nice try,");
  ST7735_SetCursor(1, 3);
  ST7735_OutString((char *)"Earthling!");
  ST7735_SetCursor(2, 4);
  ST7735_OutUDec(1234);
  while(1){
    
  }
}
// use main3 to test switches and LEDs
int main3(void){ // main3
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  while(1){
    // write code to test switches and LEDs

  }
}
// use main4 to test sound outputs
int main4(void){ uint32_t last=0,now;
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  Switch_Init(); // initialize switches
  LED_Init(); // initialize LED
  Sound_Init();  // initialize sound
  TExaS_Init(ADC0,6,0); // ADC1 channel 6 is PB20, TExaS scope
  __enable_irq();
  while(1){
    now = Switch_In(); // one of your buttons
    // modify this to test all your sounds
  }

}

// ALL ST7735 OUTPUT MUST OCCUR IN MAIN
void JoystickInit();
void JoystickIn(uint32_t *d1, uint32_t *d2);
int main(void){ // final main
  __disable_irq();
  PLL_Init(); // set bus speed
  LaunchPad_Init();
  ST7735_InitPrintf();
  JoystickInit();
    //note: if you colors are weird, see different options for
    // ST7735_InitR(INITR_REDTAB); inside ST7735_InitPrintf()
  //ST7735_FillScreen(ST7735_BLACK);
  Sensor.Init(); // PB18 = ADC1 channel 5, slidepot
  Switch_Init(); // initialize switches
  LED_Init();    // initialize LED  
  Sound_Init();  // initialize sound
  TExaS_Init(0,0,&TExaS_LaunchPadLogicPB27PB26); // PB27 and PB26
  
// initialize interrupts on TimerG12 at 30 Hz 
   printf("Select a language:\nACTION1 -> English\nACTION2 -> Espanol");
   while (languageSelection){
    if (switchActive(28)){
      language = 0;
      languageSelection = false;
    }
    else if (switchActive(31)){
      language = 1;
      languageSelection = false;
    }
   }
   Clock_Delay1ms(200);
// initialize all data structures
//  __enable_irq();
//     Character(bool shoot, int numLives, int* image, int xPos, int yPos);******* CHARACTER CONSTRCUTOR

  //AAA
  TimerG12_IntArm(80000000/15, 3);
  //AAA

  GameBoard board;
  board.board_init();
  board.printBoard();

//int centerRow = 6;
//int centerCol = 5;

//AAA
  monster = board.spawnMonster(1, 2);   
  user = board.spawnPlayer(GRID_ROWS / 2, GRID_COLS / 2, monster);          

  user->setUser(user);
  monster->setMonster(monster);

  AnimationState anim;

__enable_irq();
//AAA

// Correct indexing: [row][col]
//Tile& spawnTile = board.getBoardArr()[centerRow][centerCol];

//int spawnX = spawnTile.getX() + (TILE_WIDTH / 2) - (BOX_SIZE / 2);
//int spawnY = spawnTile.getY() + (TILE_LENGTH / 2) - (BOX_SIZE / 2) + Y_OFFSET;

// Character user(
//     false, 
//     3,     
//     taizo_stand, 
//     spawnX,
//     spawnY,  
//     0  
// );

// user.drawCharacter();

 //   printf("%d", board.getBoardArr()[centerCol][centerRow].getY());
       // clear semaphore  
       // update ST7735R  
    // check for end game or level switch

    //TimerG12_IntArm(80000000/15, 3);


    //input x LEFT PIN 0
    //input x RIGHT PIN 1 
    //input y UP PIN 2
    //input y DOWN PIN 3
uint32_t x, y;

bool screenUpdated = false;

while (1) {
  //AAA
  __WFI();

    if (anim.isAnimating) {
      BFS::animateStepFrame(anim, monster, &board, &g12Counter);
      continue; 
    }

    if (g12Counter >= 16) { 
      int mRow = monster->getRow();
      int mCol = monster->getCol();

      BFS::randomStepTowardPlayer(mRow, mCol,
                                  user->getRow(), user->getCol(),
                                  &board, monster,
                                  &g12Counter, anim);

      monster->setRow(mRow);
      monster->setCol(mCol);
      g12Counter = 0; 
      screenUpdated = true;
    }
    //AAA
   if (flag) {
        flag = false; 
        // Update logic
        JoystickIn(&x, &y);
        ST7735_SetCursor(0, 0);
        ST7735_OutString((char*)texts[language][0]);
        ST7735_SetCursor(12, 0);
        printf("%d", score);

        //printf("%d  %d", x, y);
        if (switchActive(27)){
          Sound_Attack();
        }
        else if (x > 2800 && x > y) {
            user->moveLeft(board);
            screenUpdated = true;
            }
        else if (x < 2000 && x < y) {
            user->moveRight(board);
            screenUpdated = true;
        } else if (y < 2000 && y < x) {
            user->moveUp(board);
            screenUpdated = true;
        } else if (y > 2800 && y > x) {
            user->moveDown(board);
            screenUpdated = true;
        } else {
            user->setImage(taizo_stand);
        }

        if (checkCollision(*user, *monster)) {
            handleCollision(*user, *monster, board, score);
            Sound_Pop();

            if (user->getLives() == 0) {
                showGameOver();
                __disable_irq();
                break;
            }
        }

        if (screenUpdated) {
            user->drawCharacter();
            monster->drawCharacter();
            screenUpdated = false;
        }

        if (switchActive(31)){
            __disable_irq();
            ST7735_SetCursor(0, 0);
              ST7735_OutString((char*)texts[language][1]);
              Clock_Delay1ms(1000);
              int bufCounter = 0;
            while (1){
              if (switchActive(31)) break;
             ST7735_DrawBitmap(110, 20, loadingArr[(bufCounter++ / 50) % 8], 17, 17);
            }
            ST7735_SetCursor(0, 0);
            ST7735_OutString((char*)texts[language][2]);
            Clock_Delay1ms(1000);
            ST7735_SetCursor(0, 0);
            ST7735_OutString((char*)texts[language][3]);
            Clock_Delay1ms(1000);
            ST7735_SetCursor(0, 0);
            ST7735_OutString((char*)texts[language][4]);
            Clock_Delay1ms(1000);
            ST7735_SetCursor(0, 0);
            ST7735_OutString((char*)texts[language][0]);
            ST7735_SetCursor(12, 0);
            printf("%d", score);
            board.printBoard();
            __enable_irq();
        }
        

 }
    // Optionally add low-power or idle instruction here
}
}
 
void JoystickInit(){
    // Reset ADC and VREF
    // RSTCLR
    //   bits 31-24 unlock key 0xB1
    //   bit 1 is Clear reset sticky bit
    //   bit 0 is reset ADC
  ADC1->ULLMEM.GPRCM.RSTCTL = (uint32_t)0xB1000003;
    // Enable power ADC and VREF
    // PWREN
    //   bits 31-24 unlock key 0x26
    //   bit 0 is Enable Power
  ADC1->ULLMEM.GPRCM.PWREN = (uint32_t)0x26000001;
  Clock_Delay(24); // time for ADC and VREF to power up
  ADC1->ULLMEM.GPRCM.CLKCFG = 0xA9000000; // ULPCLK
  // bits 31-24 key=0xA9
  // bit 5 CCONSTOP= 0 not continuous clock in stop mode
  // bit 4 CCORUN= 0 not continuous clock in run mode
  // bit 1-0 0=ULPCLK,1=SYSOSC,2=HFCLK
  ADC1->ULLMEM.CLKFREQ = 7; // 40 to 48 MHz
  ADC1->ULLMEM.CTL0 = 0x03010000;
  // bits 26-24 = 011 divide by 8
  // bit 16 PWRDN=1 for manual, =0 power down on completion, if no pending trigger
  // bit 0 ENC=0 disable (1 to 0 will end conversion)
  ADC1->ULLMEM.CTL1 = 0x00010000;
  // bits 30-28 =0  no shift
  // bits 26-24 =0  no averaging
  // bit 20 SAMPMODE=0 high phase
  // bits 17-16 CONSEQ=01 ADC at start to end
  // bit 8 SC=0 for stop, =1 to software start
  // bit 0 TRIGSRC=0 software trigger
  ADC1->ULLMEM.CTL2 = 0x02010000;
  // bits 28-24 ENDADD=2 (which  MEMCTL to end)
  // bits 20-16 STARTADD=1 (which  MEMCTL to start)
  // bits 15-11 SAMPCNT (for DMA)
  // bit 10 FIFOEN=0 disable FIFO
  // bit 8  DMAEN=0 disable DMA
  // bits 2-1 RES=0 for 12 bit (=1 for 10bit,=2for 8-bit)
  // bit 0 DF=0 unsigned formant (1 for signed, left aligned)
  ADC1->ULLMEM.MEMCTL[1] = 6;
  ADC1->ULLMEM.MEMCTL[2] = 4;
  // bit 28 WINCOMP=0 disable window comparator
  // bit 24 TRIG trigger policy, =0 for auto next, =1 for next requires trigger
  // bit 20 BCSEN=0 disable burn out current
  // bit 16 = AVGEN =0 for no averaging
  // bit 12 = STIME=0 for SCOMP0
  // bits 9-8 VRSEL = 10 for internal VREF,(00 for VDDA)
  // bits 4-0 channel = 0 to 7 available
  ADC1->ULLMEM.SCOMP0 = 0; // 8 sample clocks
//  ADC1->ULLMEM.GEN_EVENT.ICLR |= 0x0100; // clear flag MEMCTL[1] ??
  ADC1->ULLMEM.GEN_EVENT.IMASK = 0; // no interrupt
}

void JoystickIn(uint32_t *d1, uint32_t *d2){
  ADC1->ULLMEM.CTL0 |= 0x00000001; // enable conversions
  ADC1->ULLMEM.CTL1 |= 0x00000100; // start ADC
  uint32_t volatile delay=ADC1->ULLMEM.STATUS; // time to let ADC start
  while((ADC1->ULLMEM.STATUS&0x01)==0x01){}; // wait for completion
  *d2 = ADC1->ULLMEM.MEMRES[1];
  *d1 = ADC1->ULLMEM.MEMRES[2];
}