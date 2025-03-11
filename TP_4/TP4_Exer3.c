#include <xc.h>
#include "config.h"

#define R_POT TRISAbits.RA0 = 1
#define LEDS_OUT TRISD = 0
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

void __interrupt(high_priority) high_ISR();
void acender_LEDS(int decimas);
void setup(void);
unsigned char BCD_7SEG(int unidades);
void tensao(int sample);

int sample;
int unidades, decimas;

void main(){
    setup();
    while(1){
    }
}

void setup(){
    OSCCON = 0x73;
    R_POT;
    LEDS_OUT;
    LATD = 0x00;
    SEG_PINOS_C;
    SEG_PINOS_E;
    
    // Configurações do Timer
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0b001;
    TMR0 = 60535;
    INTCONbits.TMR0IF = 0;
    INTCONbits.T0IE = 1;
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

void __interrupt(high_priority) high_ISR(){
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF){
        TMR0 = 60535;
        INTCONbits.TMR0IF = 0;
        ADCON0bits.GO = 1;
    }
    if (PIE1bits.ADIE && PIR1bits.ADIF){
        sample = (ADRESH<<8)+ADRESL;
        tensao(sample);
        BCD_7SEG(unidades);
        acender_LEDS(decimas);
        PIR1bits.ADIF = 0;
    }
}

void acender_LEDS(int decimas){
    if (decimas >= 0 && decimas < 11){
        LATD = 0b00000000;
    }else if (decimas >= 11 && decimas < 22){
        LATD = 0b10000000;
    }else if (decimas >= 22 && decimas < 33){
        LATD = 0b11000000;
    }else if (decimas >= 33 && decimas < 44){
        LATD = 0b11100000;
    }else if (decimas >= 44 && decimas < 55){
        LATD = 0b11110000;
    }else if (decimas >= 55 && decimas < 66){
        LATD = 0b11111000;
    }else if (decimas >= 66 && decimas < 77){
        LATD = 0b11111100;
    }else if (decimas >= 77 && decimas < 88){
        LATD = 0b11111110;
    }else if (decimas >= 88 && decimas < 99){
        LATD = 0b11111111;
    }
}

/* Testei está formula no Visual Studio para evitar o uso de casting e resultou, por alguma razão no PIC não deu certo. 
int sample = 511; (Valor de Exemplo)
int tensao = ((sample * 5) * 100) / 1023;
int decimas = tensao % 100;
int unidades = tensao / 100;
 */ 

// Sendo assim utilizei o casting nas variáveis.
void tensao(int sample){
    float tensao;
    tensao = ((float)sample * 5) / 1023;
    tensao = tensao * 100;
    decimas = (int)tensao % 100;
    unidades = (int)tensao / 100;
}

unsigned char BCD_7SEG(int unidades){
    switch(unidades){
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
