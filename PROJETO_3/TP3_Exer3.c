#include "config.h"
#include <xc.h>

#define _XTAL_FREQ 8000000
#define BOTAO_IN TRISBbits.RB0 = 1
#define LED1_OUT TRISDbits.RD7 = 0  // Neste caso eu estou a utilizar o LED do PINO 7
#define SEG_PINOS_C TRISC = 0b11000000
#define SEG_PINOS_E TRISE = 0b100

#define SEG_A LATCbits.LATC0
#define SEG_B LATCbits.LATC1
#define SEG_C LATCbits.LATC2
#define SEG_D LATCbits.LATC3
#define SEG_E LATCbits.LATC4
#define SEG_F LATCbits.LATC5
#define SEG_G LATEbits.LATE0
#define SEG_PD LATEbits.LATE1
#define LED1 LATDbits.LATD7 

unsigned int NUM = 0;
void setup(void);
void config_timer(void);
unsigned char BCD_7SEG(unsigned int NUM);
unsigned int tempo_desejado(unsigned int NUM);

unsigned int n_overflow; // Repeticoes necessarias de overflow


void main(void){
    LED1 = 1;
    unsigned char ATUAL_BOTAO = 0;
    unsigned char ANTES_BOTAO = 0;
    setup();
    BCD_7SEG(NUM);
    n_overflow = tempo_desejado(NUM);
    config_timer();
    
    while(1){
    ATUAL_BOTAO = PORTBbits.RB0;
    if (ANTES_BOTAO == 0 && ATUAL_BOTAO == 1){
        NUM++;
        if (NUM > 5){
            NUM = 0;   
        }
        BCD_7SEG(NUM);
        n_overflow = tempo_desejado(NUM);
    }
    ANTES_BOTAO = ATUAL_BOTAO;
    __delay_ms(100); 
    }
}

void setup(void){
    OSCCON = 0x73;
    BOTAO_IN;
    LED1_OUT;
    SEG_PINOS_C;
    SEG_PINOS_E;
}

void config_timer(void){
    T0CONbits.T08BIT = 1;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 1;
    T0CONbits.T0PS = 0b000;
    INTCONbits.GIE = 1;
    INTCONbits.TMR0IE = 1;
    T0CONbits.TMR0ON = 1;
}

void __interrupt() rotina_isr(){
    if (INTCONbits.TMR0IF){ // Verifica se houve uma interrupcao no Timer0
        INTCONbits.TMR0IF = 0; 
        n_overflow--; // Decrementa o numero de repeticoes necessarias de overflow
        if(n_overflow == 0){  // Verifica se completou a repeticoes necessarias
            LED1 = ~LED1; // Altera o estado do LED
            n_overflow = tempo_desejado(NUM); // Retoma as repeticoes necessarias para a variavel, para repetir o ciclo. 
        }
    }
    }

unsigned char BCD_7SEG(unsigned int NUM){
    switch(NUM){
        case 0: 
            SEG_A = 1;
            SEG_B = 1;
            SEG_C = 1;
            SEG_D = 1;
            SEG_E = 1;
            SEG_F = 1;
            SEG_G = 0;
            SEG_PD = 0;
            break;
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
        default: 
            break;
    }
}
    
unsigned int tempo_desejado (unsigned int NUM){
    double potencia;
    
    switch(NUM){
        case 0:
            potencia = 1;
            break;
        case 1:
            potencia = 2;
            break;
        case 2:
            potencia = 4;
            break;
        case 3:
            potencia = 8;
            break;
        case 4:
            potencia = 16;
            break;
        case 5:
            potencia = 32;
            break;
        default:
            break;
    }
    
    double periodo;
    periodo = 1 / potencia;  
    
    double ciclo;
    ciclo = periodo / 2; // 2 Ciclos (1 Ligado e 1 Apagado)
     
    n_overflow = ciclo / 0.0001275;  // 0.0001275 segundos = Tempo até ao o Timer0 atingir o overflow 
   
    return n_overflow; // Numero de repeticoes de overflow necessarias para o Tempo que queremos
}
