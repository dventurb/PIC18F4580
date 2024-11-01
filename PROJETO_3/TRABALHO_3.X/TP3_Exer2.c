#include"config.h"
#include <xc.h>

#define _XTAL_FREQ 8000000
#define LEDS_OUT TRISD = 0x00;

unsigned int NUM_LEDS = 0x00;
void setup(void);
void config_timer(void);
void __interrupt() rotina_isr(void);

void main(void){
    
    setup();
    config_timer();
    
    
    while (1){
        
        }
    }  

void setup(void){
    OSCCON = 0x73;
    LEDS_OUT;
}

void config_timer(void){
    T0CONbits.T08BIT = 1; // Modo 8bits
    T0CONbits.T0CS = 0; // Clock Interno
    T0CONbits.PSA = 0; // Prescaler Ativado = 0;
    T0CONbits.T0PS = 0b111; // Prescaler = 1:256;
    // TMR0 = 100; Define o valor inicial do Timer0, ou seja vai contar de 100 a 255.
    INTCONbits.GIE = 1; // Interrupcoes Gerais Ativadas = 1 
    INTCONbits.TMR0IE= 1; // Interrupcoes do Timer0 Ativadas = 1
    T0CONbits.TMR0ON = 1; // Timer0 Ativado = 1
}

// Rotina da Interrupcao
void __interrupt() rotina_isr(void){
    if(INTCONbits.TMR0IF){  // Verifica se a interrupcao foi causada pelo Timer0 (Nao necessario)
        NUM_LEDS++;
        LATD = NUM_LEDS;
        
        
        if (NUM_LEDS >= 0xFF){
            NUM_LEDS = 0x00;
        }        
        
        INTCONbits.TMR0IF = 0; // Reset 
    }
}
