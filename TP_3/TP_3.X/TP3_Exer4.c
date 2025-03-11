#include"config.h"
#include<xc.h>

#define _XTAL_FREQ 8000000
#define LEDS_OUT TRISD = 0x00
#define LEDS LATD

void setup(void);
void __interrupt() rotina_isr();

unsigned int contador = 1; 


void main(void){
    setup();
    LEDS = 0b00011000;
    
    while(1){
        
    }
    
}


void setup(void){
    OSCCON = 0x73;
    LEDS_OUT;
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 1;
    T0CONbits.T0PS = 0b000;
    INTCONbits.GIE = 1;
    INTCONbits.TMR0IE = 1;
    TMR0 = 15536;    // 1 / (8MHz / 4) * (65536 - 15536) = 25000 us (25ms)
    T0CONbits.TMR0ON = 1;
}

void __interrupt()rotina_isr(){
    if (INTCONbits.TMR0IF){
        if (contador == 1){
            LEDS <<= 1;
            INTCONbits.TMR0IF = 0;
            if (LEDS == 0b11000000){
                contador = 2;
                INTCONbits.TMR0IF = 0;
            }
    }else {
            LEDS >>=1;
            INTCONbits.TMR0IF = 0;
            if (LEDS == 0b00000011){
                contador = 1;
                INTCONbits.TMR0IF = 0;
            }
    }
}
}