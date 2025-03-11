#include <xc.h>
#include "config.h"

#define LEDs_OUT TRISD = 0x00
#define BOTAO_IN TRISBbits.TRISB0 = 1

#define LEDs LATD 
#define LED1 LATDbits.LATD0
#define LED2 LATDbits.LATD1
#define LED3 LATDbits.LATD2
#define LED4 LATDbits.LATD3
#define LED5 LATDbits.LATD4
#define LED6 LATDbits.LATD5
#define LED7 LATDbits.LATD6
#define LED8 LATDbits.LATD7


void setup(void);
void __interrupt() rotina_ISR(void);
unsigned int NUM;
unsigned char acender(unsigned int NUM);

void main(void){
    setup();
    NUM = 1;
    while(1){
        acender(NUM);
    }
}

void setup(void){
    OSCCON = 0x73;
    BOTAO_IN;
    LEDs_OUT;
    INTCON2bits.INTEDG0 = 1; // Define qual a mudança de nivel que vai gerar a interrupcao (0 para 1) ou (1 para 0) 
    INTCONbits.INT0IE = 1;
    INTCONbits.INT0IF = 0;
    INTCONbits.GIE = 1;
}

void __interrupt() rotina_ISR(void){
    if (INTCONbits.INT0IF){
            NUM++;
            if (NUM > 8){
                NUM = 1;
            }
        INTCONbits.INT0IF = 0;
    }
}


unsigned char acender(unsigned int NUM){
    switch(NUM){
        case 1: 
            LED1 = 1;
            LED2 = 0;
            LED3 = 0;
            LED4 = 0;
            LED5 = 0;
            LED6 = 0;
            LED7 = 0;
            LED8 = 0;
            break;
        case 2:
            LED1 = 0;
            LED2 = 1;
            LED3 = 0;
            LED4 = 0;
            LED5 = 0;
            LED6 = 0;
            LED7 = 0;
            LED8 = 0;
            break;
        case 3:
            LED1 = 0;
            LED2 = 0;
            LED3 = 1;
            LED4 = 0;
            LED5 = 0;
            LED6 = 0;
            LED7 = 0;
            LED8 = 0;
            break;
        case 4:
            LED1 = 0;
            LED2 = 0;
            LED3 = 0;
            LED4 = 1;
            LED5 = 0;
            LED6 = 0;
            LED7 = 0;
            LED8 = 0;
            break;
        case 5:
            LED1 = 0;
            LED2 = 0;
            LED3 = 0;
            LED4 = 0;
            LED5 = 1;
            LED6 = 0;
            LED7 = 0;
            LED8 = 0;
            break;
        case 6:
            LED1 = 0;
            LED2 = 0;
            LED3 = 0;
            LED4 = 0;
            LED5 = 0;
            LED6 = 1;
            LED7 = 0;
            LED8 = 0;
            break;
        case 7:
            LED1 = 0;
            LED2 = 0;
            LED3 = 0;
            LED4 = 0;
            LED5 = 0;
            LED6 = 0;
            LED7 = 1;
            LED8 = 0;
            break;
        case 8:
            LED1 = 0;
            LED2 = 0;
            LED3 = 0;
            LED4 = 0;
            LED5 = 0;
            LED6 = 0;
            LED7 = 0;
            LED8 = 1;
            break;            
    }
    
}