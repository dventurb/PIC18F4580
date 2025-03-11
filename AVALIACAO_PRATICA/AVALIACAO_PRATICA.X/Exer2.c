#include <xc.h>
#include "config.h"


#define BOTAO_IN TRISBbits.TRISB0 = 1
#define PORTC_OUT TRISC = 0b11000000
#define PORTE_OUT TRISE = 0b100
#define LEDs_OUT TRISD = 0x00

#define SEG_A LATCbits.LATC0 
#define SEG_B LATCbits.LATC1
#define SEG_C LATCbits.LATC2 
#define SEG_D LATCbits.LATC3 
#define SEG_E LATCbits.LATC4 
#define SEG_F LATCbits.LATC5 
#define SEG_G LATEbits.LATE0
#define SEG_PD LATEbits.LATE1

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
void BCD_7SEG(unsigned int NUM);
unsigned char acender(unsigned int NUM);

void main(void){
    setup();
    NUM = 1;
    while(1){
        BCD_7SEG(NUM);
        acender(NUM);
    }
}

void setup(void){
    OSCCON = 0x73;
    BOTAO_IN;
    PORTC_OUT;
    PORTE_OUT;
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


void BCD_7SEG(unsigned int NUM){
    switch(NUM){
        case 1: 
            SEG_A = 0;
            SEG_B = 1;
            SEG_C = 1;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 0;
            SEG_G = 0;
            SEG_PD = 0;
            break;          
        case 2:
            SEG_A = 1;
            SEG_B = 1;
            SEG_C = 0;
            SEG_D = 1;
            SEG_E = 1;
            SEG_F = 0;
            SEG_G = 1;
            SEG_PD = 0;
            break;
        case 3:
            SEG_A = 1;
            SEG_B = 1;
            SEG_C = 1;
            SEG_D = 1;
            SEG_E = 0;
            SEG_F = 0;
            SEG_G = 1;
            SEG_PD = 0;
            break;
        case 4:
            SEG_A = 0;
            SEG_B = 1;
            SEG_C = 1;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 1;
            SEG_G = 1;
            SEG_PD = 0;
            break;
        case 5:
            SEG_A = 1;
            SEG_B = 0;
            SEG_C = 1;
            SEG_D = 1;
            SEG_E = 0;
            SEG_F = 1;
            SEG_G = 1;
            SEG_PD = 0;
            break;
        case 6:
            SEG_A = 1;
            SEG_B = 0;
            SEG_C = 1;
            SEG_D = 1;
            SEG_E = 1;
            SEG_F = 1;
            SEG_G = 1;
            SEG_PD = 0;
            break;
        case 7:
            SEG_A = 1;
            SEG_B = 1;
            SEG_C = 1;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 0;
            SEG_G = 0;
            SEG_PD = 0;
            break;
        case 8:
            SEG_A = 1;
            SEG_B = 1;
            SEG_C = 1;
            SEG_D = 1;
            SEG_E = 1;
            SEG_F = 1;
            SEG_G = 1;
            SEG_PD = 0;
            break;           
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