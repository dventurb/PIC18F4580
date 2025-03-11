#include"config.h"
#include<xc.h>

#define _XTAL_FREQ 8000000
#define LEDS_OUT TRISD = 0x00;  // PINOS D como Saída


void setup(void);
void my_delay_ms(unsigned int t);

void main(void){
    
    setup();
    unsigned char NUM_LED = 0x00;  // Contador 
    unsigned int t = 1;
    
    while(1){
        LATD = NUM_LED;  // Escrever o número do Contador em PINOS D
        NUM_LED++;    // Incrementa o Contador
        my_delay_ms(t);
        
        if(NUM_LED >= 0xFF){   
            NUM_LED = 0x00;
        }                    
    }
}

void setup(void){
    OSCCON = 0x73;
    LEDS_OUT;
}

void my_delay_ms(unsigned int t){
    
    // Registrador das Configurações do Timer0
    T0CONbits.T08BIT = 0; // 16bits = 0; 8bits = 1;
    T0CONbits.T0CS = 0;  // Clock Interno
    T0CONbits.PSA = 1; // Prescaler Desativo = 1; Prescaler Ativado = 0;
    T0CONbits.T0PS = 0b000; // Configuração do Prescaler
    T0CONbits.TMR0ON = 1; // Timer0 Ativado
   
    while(t){
        
        TMR0 = 0;
        while(!INTCONbits.TMR0IF);  // Fica aqui até atingir Overflow do Timer0 = 1
        INTCONbits.TMR0IF = 0;  // Reset na Flag do Overflow
        t--;
    }
}