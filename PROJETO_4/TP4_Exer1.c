#include <xc.h>
#include "config.h"

#define R_POT TRISAbits.RA0 = 1
#define LEDS_OUT TRISD = 0

void __interrupt(high_priority) high_ISR();
void acender_LEDS(int sample);
void setup(void);

int sample;

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
        acender_LEDS(sample);
        PIR1bits.ADIF = 0;
    }
}

void acender_LEDS(int sample){
    if (sample >= 0 && sample <= 127){
        LATD = 0b00000001;
    }
    if (sample >= 128 && sample <= 255){
        LATD = 0b00000010;
    }
    if (sample >= 256 && sample <= 383){
        LATD = 0b00000100;
    }
    if (sample >= 384 && sample <= 511){
        LATD = 0b00001000;
    }
    if (sample >= 512 && sample <= 639){
        LATD = 0b00010000;
    }
    if (sample >= 640 && sample <= 767){
        LATD = 0b00100000;
    }
    if (sample >= 768 && sample <= 895){
        LATD = 0b01000000;
    }
    if (sample >= 896 && sample <= 1023){
        LATD = 0b10000000;
    }
}