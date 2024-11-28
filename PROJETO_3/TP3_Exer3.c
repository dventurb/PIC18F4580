/* 
 * Calculando Tempo: 
 *    Configurações do Timer:
 *       Modo: 16bits(65535) | Prescaler: 1:2 | Valor Inicial do Timer: 64285 (65535 - 1250) 
 *    Até atingir o overflow:
 *       (1 / ((8MHz / 4) * 2 * (65535 - 64285)) = 0.00125 segundo
 *    Repetições necessárias: 
 *       2^0Hz = 1 segundo / 0.00125 segundo = 800 repetições
 *       2^1Hz = 0.5 segundo / 0.00125 segundo = 400 repetições
 *       2^2Hz = 0.25 segundo / 0.00125 segundo = 200 repetições ¹
 *       2^3Hz = 0.125 segundo / 0.00125 segundo = 100 repetições
 *       2^4Hz = 0.0625 segundo / 0.00125 segundo = 50 repetições
 *       2^5Hz = 0.015625 segundo / 0.00125 segundo = 100 repetições
 */



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

void setup(void);
void BCD_7SEG(int NUM);
int tempo_desejado(int NUM);

int repeticoes = 800; // Repeticoes necessarias para 2
int NUM = 0;
int ATUAL_BOTAO;
int ANTES_BOTAO;


void main(void){
    setup();
    while(1){
        
    }
    }

void setup(void){
    OSCCON = 0x73;
    BOTAO_IN;
    LED1_OUT;
    SEG_PINOS_C;
    SEG_PINOS_E;
    BCD_7SEG(NUM);
    repeticoes = tempo_desejado(NUM);
    
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0b000;
    TMR0 = 64910; // 1250 contagens
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCON2bits.TMR0IP = 1;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    T0CONbits.TMR0ON = 1;
}

void __interrupt() rotina_isr(){
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF){ // Verifica se houve uma interrupcao no Timer0
        if (repeticoes){       
         repeticoes--; // Decrementa o numero de repeticoes necessarias
        }else{  // Verifica se completou a repeticoes necessarias
            LED1 = ~LED1; // Altera o estado do LED
            repeticoes = tempo_desejado(NUM); // Retoma as repeticoes necessarias para a variavel, para repetir o ciclo. 
        }
        TMR0 = 64910;
        INTCONbits.TMR0IF = 0; 
    }
    
    ATUAL_BOTAO = PORTBbits.RB0; 
    if (ATUAL_BOTAO == 1 && ANTES_BOTAO == 0){
        NUM++;
        if (NUM > 5){
            NUM = 0;
        }
        BCD_7SEG(NUM);
        repeticoes = tempo_desejado(NUM);
    }
    ANTES_BOTAO = ATUAL_BOTAO;
    }

void BCD_7SEG(int NUM){
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
    
int tempo_desejado (int NUM){
    switch(NUM){
        case 0:
            return 800;
            break;
        case 1:
            return 400;
            break;
        case 2:
            return 200;
            break;
        case 3:
            return 100;
            break;
        case 4:
            return 50;
            break;
        case 5:
            return 25;
            break;
        default:
            break;
    }
}
