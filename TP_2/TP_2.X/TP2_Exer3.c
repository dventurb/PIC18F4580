#include"config.h"
#include <xc.h>

#define _XTAL_FREQ 8000000

#define BOTAO_IN TRISBbits.TRISB0 = 1;
#define PORTC_OUT TRISC = 0b11000000;   // PINOS C0 a C5 COMO SAIDA
#define PORTE_OUT TRISE = 0b100;       // PINOS E0 e E1 COMO SAIDA


#define SEG_A LATC0 
#define SEG_B LATC1
#define SEG_C LATC2
#define SEG_D LATC3
#define SEG_E LATC4
#define SEG_F LATC5
#define SEG_G LATE0
#define SEG_DP LATE1

void setup(void);
unsigned char BCD_7SEG(unsigned int NUM);

void main(void){
    setup();
    unsigned char NUM = 0;  // CONTADOR
    unsigned char ATUAL_BOTAO = 0;
    unsigned char ANTES_BOTAO = 0;
    
    while(1){
    ATUAL_BOTAO = PORTBbits.RB0;
    
    if (ANTES_BOTAO == 1 && ATUAL_BOTAO == 0){  // VERIFICAR MUDANÇA DE ESTADO NO BOTAO
        __delay_ms(100);
        NUM++;   // INCREMENTAR CONTADOR
        if (NUM>9){  // VERIFICA SE CONTADOR > 9
            NUM = 0;
        }
        BCD_7SEG(NUM);  // VALOR DO CONTADOR PARA A FUNCAO
    }
    ANTES_BOTAO = ATUAL_BOTAO;
}
}

void setup(void){
    OSCCON = 0x73;
    BOTAO_IN;
    PORTC_OUT;
    PORTE_OUT;
}

// FUNCAO PARA ESCREVER NOS SEGMENTOS
unsigned char BCD_7SEG(unsigned int NUM){
    switch(NUM){
        case 0: // CASO O VALOR DO CONTADOR SEJA 0 ESCREVE NO SEGUINTES PINOS
            SEG_A = 1;
            SEG_B = 1;
            SEG_C = 1;
            SEG_D = 1;
            SEG_E = 1;
            SEG_F = 1;
            SEG_G = 0;
            SEG_DP = 0;
            break;
        case 1:
            SEG_A = 0;
            SEG_B = 1;
            SEG_C = 1;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 0;
            SEG_G = 0;
            SEG_DP = 0;
            break;
        case 2:
            SEG_A = 1;
            SEG_B = 1;
            SEG_C = 0;
            SEG_D = 1;
            SEG_E = 1;
            SEG_F = 0;
            SEG_G = 1;
            SEG_DP = 0;
            break;
        case 3:
            SEG_A = 1;
            SEG_B = 1;
            SEG_C = 1;
            SEG_D = 1;
            SEG_E = 0;
            SEG_F = 0;
            SEG_G = 1;
            SEG_DP = 0;
            break;
        case 4:
            SEG_A = 0;
            SEG_B = 1;
            SEG_C = 1;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 1;
            SEG_G = 1;
            SEG_DP = 0;
            break;
        case 5:
            SEG_A = 1;
            SEG_B = 0;
            SEG_C = 1;
            SEG_D = 1;
            SEG_E = 0;
            SEG_F = 1;
            SEG_G = 1;
            SEG_DP = 0;
            break;
        case 6:
            SEG_A = 1;
            SEG_B = 0;
            SEG_C = 1;
            SEG_D = 1;
            SEG_E = 1;
            SEG_F = 1;
            SEG_G = 1;
            SEG_DP = 0;
            break;
        case 7:
            SEG_A = 1;
            SEG_B = 1;
            SEG_C = 1;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 0;
            SEG_G = 0;
            SEG_DP = 0;
            break;
        case 8:
            SEG_A = 1;
            SEG_B = 1;
            SEG_C = 1;
            SEG_D = 1;
            SEG_E = 1;
            SEG_F = 1;
            SEG_G = 1;
            SEG_DP = 0;
            break;
        case 9:
            SEG_A = 1;
            SEG_B = 1;
            SEG_C = 1;
            SEG_D = 1;
            SEG_E = 0;
            SEG_F = 1;
            SEG_G = 1;
            SEG_DP = 0;
            break;
        default: 
            break;
    }
}
