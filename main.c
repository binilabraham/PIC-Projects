
#include "system.h"
#include "lcd.h"
#include "delay.h"
#include "fixedwidth.h"
#include "keypad.h"
#define SYS_FREQ 		(8000000L)
#define SCK2   _TRISB15    // tris control for SCK2 pin26
//note CSEE define and set in SEE.C as RBP11


const	char Message1[] ="Select The Menu";

const	char Message2[] ="1)Music 2)Piano ";

const	char Message3[] ="3)User";

const	char Message4[] ="1)Track1 2)Track2";

const	char Message5[] ="3)Track3";

const	char Message6[] ="Enjoy the Piano";

const	char Message7[] ="Press # to exit";

const	char Message8[] ="1) Save";

const	char Message9[] ="2) Recall";

int keypad=0;
char keypadc;
    
  
void Sound ( long frequency, int duration);
void doremi(void);
void twinkletwinkle(void);
void actiontones (void);
void humterebin(void);
void jinglebell_jinglebell(void);
void keypadread(void);
void selection(void);
void music(void);
void memory(void);
void piano();
int a[32],i;
int var,var1,temp,var2;
char temp1[16];

//#define led2 LATAbits.LATA2;
int main(void) {
    
    configKeypad();
    Configtimer2();
    ANSELA =0; //make sure analog is cleared
    ANSELB =0;
    LCD_Initialize();			//LCD initialize
    clear_display();
    //PPSInput( 3,SDI2,RPB13);      //Assign SDI2 to RBP13
   // PPSOutput( 3,RPB3, SDO2);        //Assign SD02 to pin RPB2
    
    PPSOutput( 2,RPB7, OC2);       //rb7 for buzzer
    
    #define SCK2   _TRISB15    // tris control for SCK2 pin26
        //note CSEE define and set in SEE.C as RBP11
    int data;
    SCK2 =0;        //set as output

    var1=0;
    var2=0;
    var=0;
     temp=0;       
     while(1){
       selection();
       keypadread();
       if(keypad==1)
       {
           music();
           
           if (keypad==1)
           { var1=0;
            clear_display();
            position_cursor(0);
            write_string_LCD((char*)"Now Playing");
            position_cursor(40);
            write_string_LCD((char*)"Music 1");
            actiontones();
           }
           else if(keypad==2)
           { var1=0;
             clear_display();
            position_cursor(0);
            write_string_LCD((char*)"Now Playing");
            position_cursor(40);
            write_string_LCD((char*)"Music 2");  
             humterebin();  
           }
           else if (keypad==3)
           { var1=0;
             clear_display();
            position_cursor(0);
            write_string_LCD((char*)"Now Playing");
            position_cursor(40);
            write_string_LCD((char*)"Music 3");  
             jinglebell_jinglebell();   
           }
       }
       
       else if(keypad==2)
       {    for(i=0;i<32;i++)
            {    
              a[i]=0;
            }
           piano();
       }
       else if(keypad==3)
       {
           memory();
       }
       clear_display();
       
         
         
     }
  
   }
        
void selection(void)
{      clear_display();
       position_cursor(0);
       write_string_LCD((char*)Message1);
       Delayms(1000);
       clear_display();
       position_cursor(0);
       write_string_LCD((char*)Message2);
       position_cursor(40);		// position to beginning of second row
       write_string_LCD((char*)Message3); 
}

void memory(void)
{
    keypad=0;
    clear_display();
    position_cursor(0);
    write_string_LCD((char*)Message8);
    position_cursor(40);		// position to beginning of second row
    write_string_LCD((char*)Message9);
    Delayms(500);
    keypadread();
    if(keypad==1)
    {   
        
        if(var==1 && temp==1 && temp==2 && temp==3)
        
        //int j=0;
        clear_display();
        position_cursor(0);
        for(i=0;i<32;i++)
        {   clear_display();
            write_string_LCD((char*)"saving.....");
           // if(a[i]!= 0)
               // writeSEE( j, a[i]);
            //j=j+1;
            var2=temp;
        }
        
        var1=6;
    
    }   
    
    else if (var==0)
    {
       clear_display();
            write_string_LCD((char*)"Select the music"); 
            
    }
    if(keypad==2)
    {   if (var1==6)
    {
        //int b[32];
        clear_display();
        
           clear_display();
            write_string_LCD((char*)"Searching.....");
            Delayms(1000);
         
        
        clear_display();
        write_string_LCD((char*)"You Played");
        sprintf(temp1,"Track %d", var2);
     position_cursor(40);		// position to beginning of second row
     write_string_LCD((char*)temp1); 
     Delayms(2000);
    }
    }
}

void music(void)
{
     clear_display();
     position_cursor(0);
     write_string_LCD((char*)Message4);
     position_cursor(40);		// position to beginning of second row
     write_string_LCD((char*)Message5); 
     Delayms(500);
     keypad=0;
     temp=0;
     var=1;
    while(1)
    {
        if(doKeyScan()=='1')
         {  
            keypad=1;
            break;
          }
        if(doKeyScan()=='2')
         {  
            keypad=2;
            break;
         }
        if(doKeyScan()=='3')
         { 
            keypad=3;
            break;
         }
        if(doKeyScan()=='4')
         {
            keypad=4;
            break;
         }
        if(doKeyScan()=='5')
         {
            keypad=5;
            break;
         }
        if(doKeyScan()=='6')
         {
            keypad=6;
            break;
         }
        if(doKeyScan()=='7')
         {
            keypad=7;
            break;
         }
        if(doKeyScan()=='8')
         {
            keypad=8;
            break;
         }
        if(doKeyScan()=='9')
         {
            keypad=9;
            break;
         }
        if(doKeyScan()=='0')
         {
            keypad=0; 
            break;
         }
        if(doKeyScan()=='*')
         {
            keypadc='*'; 
            break;
         }
        if(doKeyScan()=='#')
         {
            keypadc='#'; 
            break;
         }
        
    }
}

void piano(void)
{   i=0;
    clear_display();
     position_cursor(0);
     write_string_LCD((char*)Message6);
     position_cursor(40);		// position to beginning of second row
     write_string_LCD((char*)Message7);
     Delayms(500);
     do
     {   
          if(doKeyScan()=='1')
         {  a[i]=245;
            i++;
            Sound(240,500);
          }
        if(doKeyScan()=='2')
         {  a[i]=254;
            i++;
            Sound(254,500);
         }
        if(doKeyScan()=='3')
         {  a[i]=269;
            i++;
            Sound(269,500);
         }
        if(doKeyScan()=='4')
         {  a[i]=285;
            i++;
            Sound(285, 500);
         }
        if(doKeyScan()=='5')
         {  a[i]=302;
            i++;
            Sound(302,500);
         }
        if(doKeyScan()=='6')
         {  a[i]=310;
            i++;
            Sound(310, 500);
         }
        if(doKeyScan()=='7')
         {  a[i]=320;
            i++;
            Sound(320,500);
         }
        if(doKeyScan()=='8')
         {  a[i]=339;
            i++;
            Sound(339,500);
         }
        if(doKeyScan()=='9')
         {  a[i]=359;
            i++;
            Sound(359,500);
         }
        if(doKeyScan()=='0')
         {  a[i]=381;
            i++;
            Sound(381,500);
         }
        if(doKeyScan()=='*')
         {  
            a[i]=401;
            i++;
            Sound(401,500);
         }
        if(doKeyScan()=='#')
         {  /*for(i=0;i<32;i++)
            {
             sprintf(temp,"%d",a[i]);
             clear_display();
             write_string_LCD((char*)temp);
             Delayms(2000);
            }*/
           break; 
         }
     }while(i<32);    
}

void keypadread(void)
{  var=1;
    while(1)
    {
        if(doKeyScan()=='1')
         {  
            keypad=1;
            break;
          }
        if(doKeyScan()=='2')
         {  
            keypad=2;
            break;
         }
        if(doKeyScan()=='3')
         {
            keypad=3;
            break;
         }
        if(doKeyScan()=='4')
         {
            keypad=4;
            break;
         }
        if(doKeyScan()=='5')
         {
            keypad=5;
            break;
         }
        if(doKeyScan()=='6')
         {
            keypad=6;
            break;
         }
        if(doKeyScan()=='7')
         {
            keypad=7;
            break;
         }
        if(doKeyScan()=='8')
         {
            keypad=8;
            break;
         }
        if(doKeyScan()=='9')
         {
            keypad=9;
            break;
         }
        if(doKeyScan()=='0')
         {
            keypad=0; 
            break;
         }
        if(doKeyScan()=='*')
         {
            keypadc='*'; 
            break;
         }
        if(doKeyScan()=='#')
         {
            keypadc='#'; 
            break;
         }
        
    }   
        /*
         if(doKeyScan()=='3')
         {   temp=3;
             //LATAbits.LATA2=1;
              doremi();
          
         }
         if(doKeyScan()=='4')
         {     temp=4;
             //LATAbits.LATA2=0;
             //position_cursor(40);		// position to beginning of second row
              actiontones ();
       
         }
         if(doKeyScan()=='5')
         {
             
             
         }
         if(doKeyScan()=='6')
         {
             clear_display();
             write_string_LCD((char*)"saved...");
             position_cursor(40);		// position to beginning of second row
             write_string_LCD((char*)Message3);
             
             var=6;
             
         }
         if(doKeyScan()=='7')
         {
             
             
             if(temp==4)
             {
                 if(var == 6){
            actiontones ();
             clear_display();
             position_cursor(0);
             write_string_LCD((char*)"U played music3");
             position_cursor(40);
             write_string_LCD((char*)"press 9 to clear");
                 }
             }
             if(temp==1)
             {
                 
             if(var == 6){
             jinglebell_jinglebell();
             clear_display();
             position_cursor(0);
             write_string_LCD((char*)"u played music1");
             position_cursor(40);
             write_string_LCD((char*)"press 9 to clear");
             }
             }
              if(temp==3)
             {
                  if(var == 6){
             doremi();
             clear_display();
             position_cursor(0);
             write_string_LCD((char*)"u played music2");
             position_cursor(40);
             write_string_LCD((char*)"press 9 to clear");
             }}
             /*else if(x==4)
             {
            actiontones ();
             clear_display();
             position_cursor(0);
             write_string_LCD((char*)"You played");
             position_cursor(40);
             write_string_LCD((char*)"music3");
             }
             
         }
         if(doKeyScan()=='8')
         {
            
         }
         if(doKeyScan()=='9')
         {
            
             clear_display();
         }
         if(doKeyScan()=='0')
         {
             
         }*/   
}


void Sound ( long frequency, int duration) {
    unsigned int period;
    period = (unsigned int) (SYS_CLK/frequency);
    OpenTimer23(T2_ON |  T2_32BIT_MODE_ON | T2_PS_1_2,period); //32 bit time
    OpenOC1( OC_ON | OC_TIMER_MODE32 | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE , period,period ); //center right
     SetDCOC1PWM(period/2); //> 50% duty cycle
   Delayms(duration);
    CloseOC1();
}
void doremi(void) {

		Sound(262,2000)	; //C6
		Sound(294,2000)	; //D6
		Sound(330,2000)	; //E6
		Sound(349,2000)	; //F6
		Sound(392,2000)	; //G6
		Sound(440,2000)	; //A6
		Sound(494,2000)	; //B6
		Sound(523,2000)	; //C7

}
void twinkletwinkle(void){
        Sound(1047,500)	; //
		Sound(2093,500)	; //
		Sound(2093,500)	; //
		Sound(3136,500)	; //
		Sound(3136,500)	; //
		Sound(3520,500)	; //
		Sound(3520,500)	; //
		Sound(3136,1000); //

}

void humterebin(void){
    temp=2;
    var=1;
        Sound(262,500)	; 
		Sound(349,500)	; 
		Sound(311,500)	;
        Delayms(100);
		Sound(311,500)	; 
		Sound(277,500)	; 
        Delayms(100);
		Sound(277,500)	; 
		Sound(262,500)	;
        Delayms(100);
		Sound(466,500);
        Sound(415,500);
        Sound(466,500);
        Sound(277,500);
        Delayms(100);
        Sound(262,500)	; 
        Delayms(100);
        Delayms(100);
        Sound(262,500)	; 
        Delayms(100);
        Delayms(100);
        Delayms(100);
        Delayms(100);
        
        
        Sound(466,500)	; 
        Delayms(100);
        Sound(466,500)	; 
        Delayms(100);
        Sound(415,500)	; 
        Delayms(100);
        Sound(466,500)	; 
        Delayms(100);
        Sound(466,500)	; 
        Delayms(100);
        Sound(415,500)	; 
        Delayms(100);
        Sound(492,500)	; 
        Delayms(100);
        Sound(492,500)	; 
        Delayms(100);
        Sound(349,500)	; 
        Sound(311,500)	; 
        Delayms(100);
        Sound(349,500)	; 
        Delayms(100);
        Delayms(100);
}

void jinglebell_jinglebell(void){
    temp=3;
    var=1;
    Sound(330,500);
    Sound(330,500);
    Delayms(100);
    Sound(330,500);
    Delayms(100);
    Sound(330,500);
    Sound(330,500);
    Delayms(100);
    Sound(330,500);
    Delayms(100);
    Delayms(100);
    Delayms(100);
    
    Sound(330,500);
    Sound(392,500);
    Delayms(100);
    Sound(262,500);
    Delayms(100);
    Sound(292,500);
    Delayms(100);
    Sound(330,500);
    Delayms(100);
    Delayms(100);
    
    Sound(349,500);
    Delayms(100);
    Sound(349,500);
    Delayms(100);
    Sound(349,500);
    Delayms(100);
    Sound(349,500);
    Sound(349,500);
    Delayms(100);
    Sound(330,500);
    Delayms(100);
    Sound(330,500);
    Delayms(100);
    Delayms(100);
    
       Sound(330,500);
       Delayms(100);
       Sound(330,500);
       Delayms(100);
       Sound(392,500);
       Delayms(100);
       Sound(392,500);
       Delayms(100);
       Sound(349,500);
       Sound(292,500);
       Delayms(100);
       Sound(262,500);
       Delayms(100);
       Delayms(100);
}
void actiontones (void) {
//alarm, 
    temp=1;
    var=1;
	Delayms(100);
	Sound (1500,500);
	Delayms(500);
	Sound (1500,500);
	Delayms(500);
	Sound (1500,500);
	Delayms(500);
	Sound (1500,500);
	Delayms(500);
	//robot
	Delayms(100);
	Sound (2800,100);
	Sound (2400,200);
	Sound (4200,140);
	Sound (2000,30);
	Delayms(500);
	Delayms(100);
	Sound (2800,100);
	Sound (2400,200);
	Sound (4200,140);
	Sound (2000,30);
	Delayms(500);
	Delayms(100);
	Sound (2800,100);
	Sound (2400,200);
	Sound (4200,140);
	Sound (2000,30);
	Delayms(500);
	//Hyperspace
	Delayms(100);
	int d =0;
	int f= 0;
	for (d=0;d<15; d++)
	 {
		for (f =2000; f<=2500; f=f+20)
			{
			Sound (f,d);
			}

		}

	}






