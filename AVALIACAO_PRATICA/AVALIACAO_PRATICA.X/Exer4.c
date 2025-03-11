#include <xc.h>
#include "config.h"

#define _XTAL_FREQ 8000000

#define LED1_OUT TRISDbits.TRISD7 = 0
#define LED2_OUT TRISDbits.TRISD6 = 0
#define PORTC_OUT TRISC = 0b11000000
#define PORTE_OUT TRISE = 0b100
#define BOTAO_IN TRISBbits.TRISB0 = 1

#define BOTAO1 PORTBbits.RB0

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
void __interrupt(low_priority) rotina_ISR(void);
void __interrupt(high_priority) rotina_BOTAO(void);
void config_timer(void);
void config_btn_int(void);
unsigned int N;
unsigned int N_REPS_OVERFLOW;
void BCD_7SEG(unsigned int N);
void tempo_desejado(unsigned int N);
unsigned int contador = 0;
unsigned int botao_pressionado = 0;

void main(void) {
    config_timer();
    config_btn_int();
    setup();
    N = 1;
    LED1 = 1;
    LED2 = 0;
    BCD_7SEG(N);
    tempo_desejado(N);
    
    while (1) {
        
     if (BOTAO1 == 1 && botao_pressionado == 1) {
         
        contador++;
        __delay_ms(1000);
        
        if (contador >= 5){
            N++;
            botao_pressionado = 0;
            contador = 0;
            
            if (N > 4) {
              N = 1;
              }
            
            BCD_7SEG(N);   
            }
        
        } else {
            contador = 0;
        }
        }
    }

void setup(void) {
    OSCCON = 0x73;
    LED1_OUT;
    LED2_OUT;
    PORTC_OUT;
    PORTE_OUT;
    BOTAO_IN;
}

void config_timer(void) {
    RCONbits.IPEN = 1;
    T0CONbits.T08BIT = 1;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 1;
    T0CONbits.T0PS = 0b000;
    INTCONbits.TMR0IE = 1;
    INTCONbits.GIE = 1;
    INTCON2bits.TMR0IP = 0;
    INTCONbits.GIEL = 1;
    T0CONbits.TMR0ON = 1;
}

void config_btn_int(void){
    INTCONbits.GIEH = 1;
    INTCON2bits.INTEDG0 = 0; // Configuração para detectar a borda de descida do botão
    INTCONbits.INT0IE = 1;
    INTCONbits.INT0IF = 0;
    INTCONbits.GIE = 1;
    INTCON2bits.RBIP = 0;  // Configura a interrupção INT0 como de baixa prioridade
}

void __interrupt(low_priority) rotina_ISR(void) {
    if (INTCONbits.TMR0IF) {
        N_REPS_OVERFLOW--;
        if (N_REPS_OVERFLOW == 0) {
            LED1 = ~LED1;
            LED2 = ~LED2;
            tempo_desejado(N);        
        }
        
        INTCONbits.TMR0IF = 0;
    }
}

void __interrupt(high_priority) rotina_BOTAO(void) {
    if (INTCONbits.INT0IF) {
        botao_pressionado = 1;
    }
    INTCONbits.INT0IF = 0;
}


void BCD_7SEG(unsigned int N) {
    switch (N) {
        case 1: 
            SEG_A = 0; SEG_B = 1; SEG_C = 1; SEG_D = 0;
            SEG_E = 0; SEG_F = 0; SEG_G = 0; SEG_PD = 0;
            break;
        case 2:
            SEG_A = 1; SEG_B = 1; SEG_C = 0; SEG_D = 1;
            SEG_E = 1; SEG_F = 0; SEG_G = 1; SEG_PD = 0;
            break;
        case 3:
            SEG_A = 1; SEG_B = 1; SEG_C = 1; SEG_D = 1;
            SEG_E = 0; SEG_F = 0; SEG_G = 1; SEG_PD = 0;
            break;
        case 4:
            SEG_A = 0; SEG_B = 1; SEG_C = 1; SEG_D = 0;
            SEG_E = 0; SEG_F = 1; SEG_G = 1; SEG_PD = 0;
            break;
    }
}

void tempo_desejado(unsigned int N) {
    double periodo;
    switch (N) {
        case 1: periodo = 2; break;
        case 2: periodo = 1; break;
        case 3: periodo = 0.5; break;
        case 4: periodo = 0.25; break;
    }
    double ciclo = periodo / 2;
    N_REPS_OVERFLOW = (unsigned int)(ciclo / 0.0001275);
}
