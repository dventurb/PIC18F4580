/* 
 * Calculando Tempo: 
 *    Até atingir o overflow:
 *      (1 / ((8MHz / 4) * 2 * (65535 - 60535)) = 0.005 segundo
 *    Repetições necessárias: 
 *      1 segundo / 00.5 segundo = 200 repetições
 *      0.5 segundo / 00.5 segundo = 100 repetições
 *      0.25 segundo / 00.5 segundo = 50 repetições 
 *      0.125 segundo / 00.5 segundo = 25 repetições
 */

#include <xc.h>
#include "config.h"

// Definir as Entradas e Saídas
#define LED7_OUT TRISDbits.TRISD6 = 0
#define LED8_OUT TRISDbits.TRISD7 = 0
#define PORTC_OUT TRISC = 0b11000000
#define PORTE_OUT TRISE = 0b1100
#define BOTAO_IN TRISBbits.TRISB0 = 1

// Definir as Macros dos LED7 e LED6
#define LED1 LATDbits.LATD7 
#define LED2 LATDbits.LATD6

// Definir as Macros do Display de 7 Segmentos
#define SEG_A LATCbits.LATC0 
#define SEG_B LATCbits.LATC1
#define SEG_C LATCbits.LATC2 
#define SEG_D LATCbits.LATC3 
#define SEG_E LATCbits.LATC4 
#define SEG_F LATCbits.LATC5 
#define SEG_G LATEbits.LATE0
#define SEG_PD LATEbits.LATE1

// Funções
void setup(void);
void num2disp(int n);
int tempo_desejado(int n);
void __interrupt(high_priority) high_ISR(void);

// Variáveis 
int n = 1;
int repeticoes = 200; // 1 segundo
int repeticoes_btn = 1000; // 5 segundos
int botao_pressionado = 1;

void main (void){
    setup();
    while(1){
        
    }
}

void setup(void){
    OSCCON = 0x73;
    LED7_OUT;
    LED8_OUT;
    PORTC_OUT;
    PORTE_OUT;
    BOTAO_IN;
    num2disp(n);
    
    // Configurações do Botão e do Timer
    INTCONbits.INT0IE = 1;
    INTCON2bits.INTEDG0 = 1;
    INTCONbits.INT0IF = 0;
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0b000; 
    TMR0 = 60535;
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    RCONbits.IPEN = 1;
    INTCON2bits.TMR0IP = 1;
    INTCONbits.TMR0IE = 1;
    INTCONbits.TMR0IF = 0;
    T0CONbits.TMR0ON = 1;
}

// Rotina de Interrupções (Timer e Botão)
void __interrupt(high_priority) high_ISR(void){
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF){
        if(repeticoes){
            repeticoes--;
        }else{
            LED1 = ~LED1;
            LED2 = ~LED2;
            repeticoes = tempo_desejado(n);
        }
        if (repeticoes_btn && PORTBbits.RB0){
            repeticoes_btn--;
        }else if (PORTBbits.RB0 == 0){
            repeticoes_btn = 1000;
        }else if (repeticoes_btn == 0 && PORTBbits.RB0 && botao_pressionado){
            n++;
            if (n > 4){
                n = 1;
                }
                repeticoes_btn = 1000;
                num2disp(n);
                botao_pressionado = 0;
        }
        TMR0 = 60535;
        INTCONbits.TMR0IF = 0;
    }
    
    if (INTCONbits.INT0IE && INTCONbits.INT0IF){
        repeticoes_btn = 1000;
        botao_pressionado = 1;
        INTCONbits.INT0IF = 0;
        num2disp(n);
    }
}

// Display de 7 Segmentos (1 ao 4)
void num2disp(int n){
        switch (n) {
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

// Número de repetições 
int tempo_desejado(int n){
    
    switch(n){
        case 1:
            return 200; // 1 segundo
            break;
        case 2:
            return 100; // 0,5 segundos
            break;
        case 3:
            return 50; // 0,25 segundos
            break;
        case 4:
            return 25; // 0,125 segundos
            break;
        default:
            break;
    }
}
