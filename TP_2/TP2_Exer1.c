#include"config.h"
#include<xc.h>

#define _XTAL_FREQ 8000000  // OSCILADOR 8Mhz
#define LEDS_OUT TRISD=0b00000000; // DEFINIR PINOS D COMO SAIDA

void setup(void);

void main(void){
    
    setup();
    
    LATD = 0b11010100; // SINAL ALTO = 1 ; SINAL BAIXO = 0
    
    while(1){
        __delay_ms(500);
        LATD = ~LATD;    // INVERTER O SINAL 
    } 
}

void setup(void){
    OSCCON = 0x73;
    LEDS_OUT;
}