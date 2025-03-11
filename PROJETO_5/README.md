# 4. Comunicação Serial - Exercícios

## Exercício 1
**Recepção de dados e exibição no Display de 7 segmentos**  
Desenvolva um software que permita comunicar com o PC através da porta serial, utilizando o Terminal do TinyBootLoader. A USART do PIC18F4580 deve ser configurada com os seguintes parâmetros:

8 bits de dados, Sem bit de paridade, 1 stop-bit 19200 bps, modo de alta velocidade.

## Exercício 2
**Envio da resposta ao PC**  
Altere o software do exercício anterior para que o microcontrolador envie de volta ao PC o dobro do algarismo recebido. Exemplo de funcionamento:

Entrada: "3" + ENTER → O display mostra "3", e o PC recebe "6".

## Exercício 3
**Multímetro digital com envio de dados ao PC**  
Desenvolva um software que funcione como um multímetro digital, permitindo medir a tensão no canal AN0 da ADC do PIC18F4580. O valor da tensão deve ser calculado com uma casa decimal e enviado para o PC sempre que houver uma alteração no valor medido.



