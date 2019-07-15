
#include <plib.h>
#include "delay.h"
#include "fixedwidth.h"
#define C0 PORTBbits.RB5
#define C1 PORTBbits.RB8
#define C2 PORTBbits.RB9


static inline void CONFIG_COLUMN() {
    TRISBbits.TRISB5=1;
    CNPUBbits.CNPUB5=1;
    TRISBbits.TRISB8=1;
    CNPUBbits.CNPUB8=1;
    TRISBbits.TRISB9=1;
    CNPUBbits.CNPUB9=1;
}

#define R0 LATBbits.LATB0 
#define R1 LATBbits.LATB1 
#define R2 LATAbits.LATA4
#define R3 LATAbits.LATA3


void CONFIG_ROW() {
    LATBbits.LATB0=0;
    TRISBbits.TRISB0=0;
    LATBbits.LATB1=0;
    TRISBbits.TRISB1=0;   
    LATAbits.LATA4=0;
    TRISAbits.TRISA4=0;
    LATAbits.LATA3=0;
    TRISAbits.TRISA3=0;
}

static inline void DRIVE_ROW_LOW() {
  R0 = 0;
  R1 = 0;
  R2 = 0;
  R3 = 0;
}

static inline void DRIVE_ROW_HIGH() {
  R0 = 1;
  R1 = 1;
  R2 = 1;
  R3 = 1;
}

void configKeypad(void) {
  CONFIG_ROW();
  DRIVE_ROW_LOW();
  CONFIG_COLUMN();
  delay_1us();     //wait for pullups to stabilize inputs
}

//drive one row low
void setOneRowLow(uint8_t u8_x) {
  switch (u8_x) {
    case 0:
      R0 = 0;
      R1 = 1;
      R2 = 1;
      R3 = 1;
      break;
    case 1:
      R0 = 1;
      R1 = 0;
      R2 = 1;
      R3 = 1;
      break;
    case 2:
      R0 = 1;
      R1 = 1;
      R2 = 0;
      R3 = 1;
      break;
    default:
      R0 = 1;
      R1 = 1;
      R2 = 1;
      R3 = 0;
      break;  
  }
}
#define NUM_ROWS 4
#define NUM_COLS 3
const uint8_t au8_keyTable[NUM_ROWS][NUM_COLS] = { 
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'},
};

#define KEY_PRESSED() (!C0 || !C1 || !C2 )   //any low
#define KEY_RELEASED() (C0 && C1 && C2 )  //all high

uint8_t doKeyScan(void) {
  uint8_t u8_row, u8_col;
  //determine column
  if (!C0) u8_col = 0;
  else if (!C1) u8_col = 1;
  else if (!C2) u8_col = 2;
   //error
  //determine row
  for (u8_row = 0; u8_row < NUM_ROWS; u8_row++) {
    setOneRowLow(u8_row); //enable one row low
    if (KEY_PRESSED()) {  ///????????
      DRIVE_ROW_LOW(); //return rows to driving low
      return(au8_keyTable[u8_row][u8_col]);
    }
  }
  DRIVE_ROW_LOW(); //return rows to driving low //error
}


typedef enum  {
  STATE_WAIT_FOR_PRESS = 0,
  STATE_WAIT_FOR_PRESS2,
  STATE_WAIT_FOR_RELEASE,
} ISRSTATE;

ISRSTATE e_isrState = STATE_WAIT_FOR_PRESS;
volatile uint8_t u8_newKey = 0;

//Interrupt Service Routine for Timer3
void __ISR(_TIMER_1_VECTOR, ipl2) Timer1Handler (void) {
  switch (e_isrState) {
    case STATE_WAIT_FOR_PRESS:
      if (KEY_PRESSED() && (u8_newKey == 0)) {
        //ensure that key is sampled low for two consecutive interrupt periods
        e_isrState = STATE_WAIT_FOR_PRESS2;
      }
      break;
    case STATE_WAIT_FOR_PRESS2:
      if (KEY_PRESSED()) {
        // a key is ready
        u8_newKey = doKeyScan();
        e_isrState = STATE_WAIT_FOR_RELEASE;
      } else e_isrState = STATE_WAIT_FOR_PRESS;
      break;

    case STATE_WAIT_FOR_RELEASE:
      //keypad released
      if (KEY_RELEASED()) {
        e_isrState = STATE_WAIT_FOR_PRESS;
      }
      break;
    default:
      e_isrState = STATE_WAIT_FOR_PRESS;
      break;
  }
     
     mT1ClearIntFlag();              //clear the timer interrupt bit
}


/**
void  configTimer3(void) {
  //ensure that Timer2,3 configured as separate timers.
  T2CONbits.T32 = 0;     // 32-bit mode off
  //T3CON set like this for documentation purposes.
  //could be replaced by T3CON = 0x0020
  T3CON = T3_OFF | T3_IDLE_CON | T3_GATE_OFF
          | T3_SOURCE_INT
          | T3_PS_1_64 ;  //results in T3CON= 0x0020
  PR3 = msToU16Ticks (ISR_PERIOD, getTimerPrescale(T3CONbits)) - 1;
  TMR3  = 0;                       //clear timer3 value
  _T3IF = 0;                       //clear interrupt flag
  _T3IP = 1;                       //choose a priority
  _T3IE = 1;                       //enable the interrupt
  T3CONbits.TON = 1;               //turn on the timer
}
*/
#define SYS_FREQ 		(8000000L) //8 Mhz internal fast oscillator
// Let compile time pre-processor calculate the PR1 (period)
#define PB_DIV                 1
#define PRESCALE1               64
#define TOGGLES_PER_SEC        5
#define T2_TICK               (SYS_FREQ/PB_DIV/PRESCALE1/TOGGLES_PER_SEC)

void Configtimer2 (void){
    // STEP 4 set up timer2 for interrupts
     OpenTimer1(T1_ON | T1_SOURCE_INT | T1_PS_1_64, T2_TICK);
  INTEnableSystemMultiVectoredInt();
    // set up the timer interrupt with a priority of 2
    ConfigIntTimer2(T1_INT_ON | T1_INT_PRIOR_1);
      mT1ClearIntFlag();
     /* setup system wide interrupts */
}
