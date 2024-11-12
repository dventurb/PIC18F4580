// 0,5Hz = 2Segundos (1 Segundo LED LIGADO e 1 SEGUNDO LED DESLIGADO) 
// Calcular o tempo do Timer (8bits) para atinger o overflow = 1/(8/4) * 255 = 127,5microsegundos (0,0001275segundo)
// Calcular o N de Repeticoes de OverFlow para 1 Segundo = 1s / 0.0001275s = 7955 repeticoes


#include<xc.h>
#include"config.h"

#define LED1_OUT TRISDbits.TRISD7 = 0
#define LED2_OUT TRISDbits.TRISD6 = 0
#define PORTC_OUT TRISC = 0b11000000
#define PORTE_OUT TRISE = 0b100

#define LED1 LATDbits.LATD7 
#define LED2 LATDbits.LATD6

#define SEG_A LATCbits.LATC0 
#define SEG_B LATCbits.LATC1
#define SEG_C LATCbits.LATC2 
#define SEG_D LATCbits.LATC3 
#define SEG_E LATCbits.LATC4 
#define SEG_F LATCbits.LATC5 
#define SEG_G LATEbits.LATE0
#define SEG_PD LATEbits.LATE1

void setup(void);
void __interrupt() rotina_ISR(void);
void config_timer(void);
unsigned int N;
unsigned int N_REPS_OVERFLOW = 7955;  // N_REPS_OVERFLOW =  1segundo / 0,0001275segundos
void BCD_7SEG(unsigned int N);


void main(void){
    config_timer();
    setup();
    LED1 = 1;
    N = 1;
    BCD_7SEG(N);
    while(1){
    }
}

void setup(void){
    OSCCON=0x73;
    LED1_OUT;
    LED2_OUT;
    PORTC_OUT;
    PORTE_OUT;
}

void config_timer(void){
    T0CONbits.T08BIT = 1;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 1;
    T0CONbits.T0PS = 0b000;
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;
    T0CONbits.TMR0ON = 1;
}

void __interrupt() rotina_ISR(void){
    if(INTCONbits.TMR0IF){
        N_REPS_OVERFLOW--;
        if (N_REPS_OVERFLOW == 0){
            LED1 = ~LED1;
            LED2 = ~LED2;
            N_REPS_OVERFLOW = 7955;         
        }
    }
}

void BCD_7SEG(unsigned int N){
    switch(N){
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
        case 6:
            SEG_A = 1;
            SEG_B = 0;
            SEG_C = 1;
            SEG_D = 1;
            SEG_E = 1;
            SEG_F = 1;
            SEG_G = 1;
            SEG_PD = 0;
            break;
        case 7:
            SEG_A = 1;
            SEG_B = 1;
            SEG_C = 1;
            SEG_D = 0;
            SEG_E = 0;
            SEG_F = 0;
            SEG_G = 0;
            SEG_PD = 0;
            break;
        case 8:
            SEG_A = 1;
            SEG_B = 1;
            SEG_C = 1;
            SEG_D = 1;
            SEG_E = 1;
            SEG_F = 1;
            SEG_G = 1;
            SEG_PD = 0;
            break;           
    }
}
