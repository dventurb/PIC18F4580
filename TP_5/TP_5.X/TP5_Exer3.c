#include <xc.h>
#include "config.h"
#include <stdlib.h>
#include <stdio.h>

#define R_POT TRISAbits.RA0 = 1
#define TX_OUT TRISCbits.RC6 = 0

// Funçoes
void setup(void);
void TX_USART(char data);
void enviarString(char *string);
void __interrupt() rotinaISR(void);

// Variáveis Globais
int numero = 0;
char data;
char string[3];
int sample;
float tensaoAnterior = -1;
char str[10];

void main(void) {
    setup();
    while(1) {
    }
}

void setup(void){
    OSCCON=0x73;
    R_POT;
    TX_OUT;
    //Configurações RX
    SPBRG = 25;
    TXSTAbits.BRGH = 1;
    TXSTAbits.SYNC = 0; // Assícrono
    RCSTAbits.SPEN = 1; // Habilitar TX e RX
    RCSTAbits.RC9 = 0; // 8 bits
    RCSTAbits.CREN = 1; // Rececao continua
    TXSTAbits.TXEN = 1; // Transmissao
    TXSTAbits.TX9 = 0;
    PIR1bits.RCIF = 0;
    PIE1bits.RCIE = 1;
    // Configurações do Timer
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0b001;
    TMR0 = 60535;
    INTCONbits.TMR0IF = 0;
    INTCONbits.T0IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1; 
    // Configurações do ADC
    ADCON1bits.PCFG = 0b1101;
    ADCON1bits.VCFG = 0b00;
    ADCON0bits.CHS = 0b0000;
    ADCON2bits.ADCS = 0b110;
    ADCON2bits.ACQT = 0b010;
    ADCON2bits.ADFM = 1;
    PIE1bits.ADIE = 1;
    
    T0CONbits.TMR0ON = 1;
    ADCON0bits.ADON = 1;
}

void __interrupt() rotinaISR(void){
    if(INTCONbits.TMR0IF){
        TMR0 = 60535;
        INTCONbits.TMR0IF = 0;
        ADCON0bits.GO = 1;
    }
    if (PIE1bits.ADIE && PIR1bits.ADIF){
        sample = (ADRESH << 8) + ADRESL;
        float tensao = (float)sample * (5.0 / 1023.0);
        int tensaoUnidade = (int)tensao;
        int tensaoDecimal = (int)((tensao - tensaoUnidade) * 100);
        if (tensao != tensaoAnterior){
            tensaoAnterior = tensao;
            sprintf(str, "%d.%02d", tensaoUnidade, tensaoDecimal);
            enviarString(str);
        }
        PIR1bits.ADIF = 0;
    }
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

