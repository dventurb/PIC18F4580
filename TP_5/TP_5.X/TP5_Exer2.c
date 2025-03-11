#include <xc.h>
#include "config.h"
#include <stdlib.h>
#include <stdio.h>

#define PORTC_OUT TRISC = 0b11000000
#define PORTE_OUT TRISE = 0b100
#define RX_IN TRISCbits.RC7 = 1
#define TX_OUT TRISCbits.RC6 = 0
#define SEG_A LATCbits.LATC0
#define SEG_B LATCbits.LATC1
#define SEG_C LATCbits.LATC2
#define SEG_D LATCbits.LATC3
#define SEG_E LATCbits.LATC4
#define SEG_F LATCbits.LATC5
#define SEG_G LATEbits.LATE0
#define SEG_DP LATEbits.LATE1

// Funçoes
void BCD_7SEG(int numero);
void setup(void);
char RX_USART(void);
void TX_USART(char data);
void enviarString(char *string);
void __interrupt() rotinaISR(void);

// Variáveis Globais
int numero = 0;
char data;
char string[3];

void main(void) {
    setup();
    while(1) {
    }
}

void setup(void){
    OSCCON=0x73;
    PORTC_OUT;
    PORTE_OUT;
    RX_IN;
    TX_OUT;
    //Configurações de Interrupções 
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    //Configurações RX
    SPBRG = 25;
    TXSTAbits.BRGH = 1; // Baixa velocidade
    TXSTAbits.SYNC = 0; // Assícrono
    RCSTAbits.SPEN = 1; // Habilitar TX e RX
    RCSTAbits.RC9 = 0; // 8 bits
    RCSTAbits.CREN = 1; // Rececao continua
    TXSTAbits.TXEN = 1; // Transmissao
    TXSTAbits.TX9 = 0;
    PIR1bits.RCIF = 0;
    PIE1bits.RCIE = 1;
}

void __interrupt() rotinaISR(void){
    if (PIR1bits.RCIF){
        char ch = RX_USART();
        if (ch >= '0' && ch <= '9'){
            numero = ch - '0';
            BCD_7SEG(numero);
            sprintf(string, "%d", numero*2);
            enviarString(string);
        }
        PIR1bits.RCIF = 0;
    }
}

char RX_USART(void){
    return RCREG;
}

void TX_USART(char data){
    while(!PIR1bits.TXIF);
    TXREG = data;
}

void enviarString(char *string){
    while(*string != '\0'){
        TX_USART(*string);
        string++;
    }
    TX_USART(13); // \r - Carriage Return
    TX_USART(10); // \n - Line Feed
}

void BCD_7SEG(int numero){
    switch(numero){
        case 0: 
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