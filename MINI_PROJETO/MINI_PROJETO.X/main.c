/*  
 *  Configurações do Timer:
 *      Modo: 16 bits(65535)  |  Prescaler: 1:64  |  Valor Inicial: 34285 (65535 - 31250)
 * 
 *      Até atingir o overflow:
 *          (1 / (8MHz / 4) * 64 * (65535 - 31250)) = 10 segundos 
 *
 */

// BIBLIOTECAS
#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "config.h"

#define _XTAL_FREQ 8000000  // Oscilador 8MHz (Função _delay_ms)

// ENTRADAS E SAÍDAS 
#define R_POT TRISAbits.RA0 = 1
#define PORTC_OUT TRISC = 0b11000000
#define PORTE_OUT TRISE = 0b100
#define LEDS_OUT TRISD = 0b00011111
#define RX_IN TRISCbits.RC7 = 1
#define TX_OUT TRISCbits.RC6 = 0
#define BUZZER_OUT TRISAbits.RA2 = 0
#define VETOINHA_OUT TRISAbits.RA3 = 0

// LEDS
#define LED_1 LATDbits.LATD7  // +ARREFECIMENTO
#define LED_2 LATDbits.LATD6  // -ARREFECIMENTO
#define LED_3 LATDbits.LATD5  // AQUECIMENTO

// BUZZER 
#define BUZZER LATAbits.LATA2  // Buzzer Externo no Pino RA2

// VETOINHA 
#define VETOINHA LATAbits.LATA3 // Vetoinha Externa no Pino RA3

// Display 7 Segmentos
#define SEG_A LATCbits.LATC0
#define SEG_B LATCbits.LATC1
#define SEG_C LATCbits.LATC2
#define SEG_D LATCbits.LATC3
#define SEG_E LATCbits.LATC4
#define SEG_F LATCbits.LATC5
#define SEG_G LATEbits.LATE0
#define SEG_DP LATEbits.LATE1

// VARIÁVEIS GLOBAIS
#define MAX_STRING 5
char buffer[MAX_STRING];
char str[MAX_STRING];
int indice = 0;
int tempDesejada = 18;   // A/C: 18ºC a 26ºC (Manual)
bool automatico = false; // Automatico Ligado ou Desligado
bool manual = false;     // Manual Ligado ou Desligado

// FUNÇÕES 
void setup(void);
void configTimer(void);
void configAdc(void);
void configUsart(void);
void display7Seg(int num);
char rxUsart(void);
void txUsart(char ch);
void enviarString(char *str);
void displayTemperatura(float temp);
void limparDisplay(void);
float lerTemperatura(void);
void regularTemperatura(float temp);

// INTERRUPÇÕES 
void __interrupt(high_priority) rotina_ISR();

void main(void){
    setup();
    while(1){
        float temp = lerTemperatura();
        displayTemperatura(temp);
        if(automatico){
            regularTemperatura(temp);
        }
        if(manual){
            if(tempDesejada >= 18 && tempDesejada < 22){
                LED_1 = 1;
                LED_2 = 0;
                LED_3 = 0;
                VETOINHA = 1;
            }else if(tempDesejada >= 22 && tempDesejada < 26){
                LED_1 = 0;
                LED_2 = 1;
                LED_3 = 0;
                VETOINHA = 0;
            }else if(tempDesejada >= 26){
                LED_1 = 0;
                LED_2 = 0;
                LED_3 = 1;
                VETOINHA = 0;
            }
        }
    }
}

// CONFIGURAÇÕES
void setup(void){
    OSCCON = 0x73;
    R_POT;
    PORTC_OUT;
    PORTE_OUT;
    LEDS_OUT;
    RX_IN;
    TX_OUT;
    BUZZER_OUT;
    VETOINHA_OUT;
    LATD = 0x00;
    VETOINHA = 0x00;
    configTimer();
    configAdc();
    configUsart();
    T0CONbits.TMR0ON = 1;
    ADCON0bits.ADON = 1;
    enviarString("\r\nComandos Disponiveis: \r\nA     Modo Automatico\r\nM+    Manual +Temperatura\r\nM-    Manual -Temperatura\r\nOff   Desligar o A/C\r\n\r\n");
}

// ROTINA DE INTERRUPÇÕES 
void __interrupt(high_priority) rotina_ISR(){
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF){
        TMR0 = 34285;
        INTCONbits.TMR0IF = 0;
        INTCONbits.TMR0IE = 1;
        ADCON0bits.GO = 1;
    }
    if (PIE1bits.ADIE && PIR1bits.ADIF){
        PIR1bits.ADIF = 0;
    }
    if (PIR1bits.RCIF){
        char ch = rxUsart();
        if (ch != '\n' && ch != '\r' && indice < MAX_STRING - 1){
            buffer[indice] = ch;
            indice++;
            buffer[indice] = '\0';
        }else {
            buffer[indice] = '\0';
            if (strcmp(buffer, "Off") == 0){
                LED_1 = 0;
                LED_2 = 0;
                LED_3 = 0;
                VETOINHA = 0;
                BUZZER = 1;
                __delay_ms(250);
                BUZZER = 0;
                automatico = false;
                manual = false;
            }else if (strcmp(buffer, "M+") == 0){
                manual = true;
                automatico = false;
                if (tempDesejada >= 18 && tempDesejada < 26){
                    tempDesejada++;
                    sprintf(str, "A/C: %d", tempDesejada);
                    enviarString(str);
                }
                BUZZER = 1;
                __delay_ms(250);
                BUZZER = 0;
            }else if (strcmp(buffer, "M-") == 0){
                manual = true;
                automatico = false;
                if (tempDesejada > 18 && tempDesejada <= 26){
                    tempDesejada--;
                    sprintf(str, "A/C: %d", tempDesejada);
                    enviarString(str);
                }
                BUZZER = 1;
                __delay_ms(250);
                BUZZER = 0;
            }else if (strcmp(buffer, "A") == 0){
                automatico = true;
                manual = false;
                BUZZER = 1;
                __delay_ms(250);
                BUZZER = 0;
            }
            indice = 0;
            memset(buffer, 0, MAX_STRING);
        }
        PIR1bits.RCIF = 0;
    }
}

// Receber Dados
char rxUsart(void){
    return RCREG;
}

// Transmitir Dados
void txUsart(char ch){
    while(!PIR1bits.TX1IF);
    TXREG = ch;
}

// Transmitir uma String
void enviarString(char *str){
    while(*str != '\0'){
        txUsart(*str);
        str++;
    }
    txUsart(13);  // Carriage Return (\r)
    txUsart(10);  // Line Feed (\n)
}

// Regular o A/C no Modo Automático 
void regularTemperatura(float temp){
    if (temp >= 30.0){
        enviarString("A/C: 18.0");
        LED_1 = 1;
        LED_2 = 0;
        LED_3 = 0;
        VETOINHA = 1;
    }else if (temp >= 20.0 && temp < 30.0){
        enviarString("A/C: 22.0");
        LED_1 = 0;
        LED_2 = 1;
        LED_3 = 0;
        VETOINHA = 0;
    }else if (temp >= 0.0 && temp < 20.0){
        enviarString("A/C: 26.0");
        LED_1 = 0;
        LED_2 = 0;
        LED_3 = 1;
        VETOINHA = 0;
    }
}

// Ler Valor do ADC
float lerTemperatura(void){
    int sample = (ADRESH << 8) | ADRESL;
    return ((float)sample / 1023.0) * 50.0;  // 0ºC até 50ºC
}

// Display de 7 Segmentos 
void display7Seg(int num){
    const unsigned char numeros[10] = {
        0x3F,  // 0 - 00111111
        0x06,  // 1
        0x6B,  // 2
        0x4F,  // 3
        0x66,  // 4
        0x6D,  // 5
        0x7D,  // 6
        0x07,  // 7
        0x7F,  // 8
        0x6F   // 9
    };
    if (num < 10){
        unsigned char segmentos = numeros[num];
        // Máscara de bits (AND)
        SEG_A = (segmentos & 0x01) ? 1 : 0;  // bit 0
        SEG_B = (segmentos & 0x02) ? 1 : 0;  // bit 1
        SEG_C = (segmentos & 0x04) ? 1 : 0;  // bit 2
        SEG_D = (segmentos & 0x08) ? 1 : 0;  // bit 3
        SEG_E = (segmentos & 0x10) ? 1 : 0;  // bit 4
        SEG_F = (segmentos & 0x20) ? 1 : 0;  // bit 5
        SEG_G = (segmentos & 0x40) ? 1 : 0;  // bit 6
        SEG_DP = (segmentos & 0x80) ? 1: 0;  // bit 7      
    }
}

// Enviar Temperatura para o Display
void displayTemperatura(float temp){
    int inteiro = (int)temp;
    int decimal = (int)((temp - inteiro) * 10);
    int digitos[3];
    digitos[0] = inteiro / 10;
    digitos[1] = inteiro % 10;
    digitos[2] = decimal;
    for (int i = 0; i < 2; i++){
        display7Seg(digitos[i]);
        if (i == 1){
            SEG_DP = 1;
        }
        __delay_ms(1000);
    }
    SEG_DP = 0;
    display7Seg(digitos[2]);
    __delay_ms(1000);
    limparDisplay();
    __delay_ms(500);
}

void limparDisplay(void){
    SEG_A = 0;
    SEG_B = 0;
    SEG_C = 0;
    SEG_D = 0;
    SEG_E = 0;
    SEG_F = 0;
    SEG_G = 0;
    SEG_DP = 0;
}
// Configurações do Timer0
void configTimer(void){
    T0CONbits.T08BIT = 0;    // bits do Timer0
    T0CONbits.T0CS = 0;      // Clock Interno
    T0CONbits.PSA = 0;       // Prescaler Ativado
    T0CONbits.T0PS = 0b101;  // 1:64 Prescaler
    TMR0 = 34285;            // Valor Inicial
    INTCONbits.TMR0IF = 0;   // Limpar flag
    INTCONbits.TMR0IE = 1;   // Interrupções Timer0
    INTCONbits.PEIE = 1;     // Interrupções Periféricas
    INTCONbits.GIE = 1;      // Interrupções Globais
}

// Configurações do ADC
void configAdc(void){
    ADCON1bits.PCFG = 0b1101;  // Pinos Analógicos
    ADCON1bits.VCFG = 0b00;    // Referência de Tensão 
    ADCON0bits.CHS = 0b0000;   // Canal de Entrada
    ADCON2bits.ADCS = 0b110;   // Prescaler do ADC
    ADCON2bits.ACQT = 0b010;   // Tempo de Justificação
    ADCON2bits.ADFM = 1;       // Right Justified
    PIE1bits.ADIE = 1;         // Interrupções do ADC
}

// Configurações do USART
void configUsart(void){
    SPBRG = 25;          // baud rate (19200)
    TXSTAbits.BRGH = 1;  // Alta Velocidade baud rate
    TXSTAbits.SYNC = 0;  // Assícrono
    RCSTAbits.SPEN = 1;  // Habilitar pinos TX e RX
    RCSTAbits.RC9 = 0;   // 8 bits RX
    RCSTAbits.CREN = 1;  // Recepção contínua
    TXSTAbits.TX9 = 0;   // 8 bits TX
    TXSTAbits.TXEN = 1;  // Transmisão 
    PIR1bits.RCIF = 0;   // Limpar flag
    PIE1bits.RCIE = 1;   // Interrupções RX
}