#include"config.h"
#include<xc.h>

#define _XTAL_FREQ 8000000
#define LEDS_OUT TRISD = 0x00;     // PINOS D COMO SAIDA
#define BOTAO_IN TRISBbits.TRISB0 = 1;   // PINO B0 COMO ENTRADA

void setup(void);

void main(void){
    setup();
    LATD = 0b00101011;    // LIGAR LED1; LED2; LED4; LED6
    unsigned char ATUAL_BOTAO = 0;
    unsigned char ANTES_BOTAO = 0;
    
    while(1){
        ATUAL_BOTAO = PORTBbits.RB0;   // VALOR LIDO NO PINO B0
        
        if (ANTES_BOTAO == 1 && ATUAL_BOTAO == 0){  // VERIFICA MUDANÇA DE SINAL NO B0
            LATD = ~LATD;  // INVERTE OS LEDS
        }
        
        ANTES_BOTAO = ATUAL_BOTAO;
        __delay_ms(100);
    }  
}

void setup(void){
    OSCCON = 0x73;
    LEDS_OUT;
    BOTAO_IN;
}