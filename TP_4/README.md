# 3. ADC - Exercícios

## Exercício 1
**Conversão do sinal analógico e representação por LEDs**  
Desenvolva um software que converte para digital o sinal analógico presente no canal AN0, ligado a um potenciômetro. A frequência de amostragem deve ser de 100 Hz e o resultado de cada conversão, C, deve ser ajustado à direita.

As tensões de referência da ADC devem ser 0 V e 5 V. A gama de conversão [0, 1023] deve ser dividida em 8 níveis, cada um dos quais representado por um LED. 

## Exercício 2
**Alternância entre canais de entrada**  
Modifique o software do exercício anterior para alternar entre o canal AN0 e o canal AN1. A mudança de canal deve ocorrer sempre que o Botão 1 for pressionado. O funcionamento da representação dos LEDs deve ser mantido.

## Exercício 3
**Multímetro digital com leitura aproximada da tensão**  
Desenvolva um software que funcione como um multímetro digital, permitindo medir a tensão presente no canal AN0. A tensão deve ser calculada com uma casa decimal, onde:

O valor das unidades deve ser apresentado no display de 7 segmentos. O valor das décimas deve ser representado pelos LEDs, onde cada LED corresponde a 0,11 V.
