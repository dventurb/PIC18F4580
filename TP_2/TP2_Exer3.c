#include"config.h"
#include <xc.h>

#define _XTAL_FREQ 8000000

#define BOTAO_IN TRISBbits.TRISB0 = 1
#define PORTC_OUT TRISC = 0b11000000  // PINOS C0 a C5 COMO SAIDA
#define PORTE_OUT TRISE = 0b100       // PINOS E0 e E1 COMO SAIDA


#define SEG_A LATCbits.LATC0
#define SEG_B LATCbits.LATC1
#define SEG_C LATCbits.LATC2
#define SEG_D LATCbits.LATC3
#define SEG_E LATCbits.LATC4
#define SEG_F LATCbits.LATC5
#define SEG_G LATEbits.LATE0
#define SEG_DP LATEbits.LATE1

void setup(void);
unsigned char BCD_7SEG(unsigned int NUM);
void __interrupt() rotina_ISR(void);
unsigned char NUM = 0;  // CONTADOR

void main(void){
    setup();

    while(1){
        BCD_7SEG(NUM);
}
}

void setup(void){
    OSCCON = 0x73;
    BOTAO_IN;
    PORTC_OUT;
    PORTE_OUT;
    INTCON2bits.INTEDG0 = 1; // Define qual a mudança de nivel que vai gerar a interrupcao (0 para 1) ou (1 para 0) 
    INTCONbits.INT0IE = 1;
    INTCONbits.INT0IF = 0;
    INTCONbits.GIE = 1;
}

void __interrupt() rotina_ISR(){
    if (INTCONbits.INT0IF){
            NUM++;
            if (NUM > 9){
                NUM = 0;
            }
        INTCONbits.INT0IF = 0;
    }
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
