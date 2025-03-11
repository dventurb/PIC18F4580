<div align="center" style="text-align: center">
<img src="https://i.imgur.com/EMgErTa.gif" alt="PIC18F4580 Logo"/>
<h3>Projetos em C com PIC18F4580</h3>
<p>
  Repositório com projetos em C, para o microcontrolador PIC18F4580, desenvolvidos na disciplina de Microcontroladores.
</p>
</div>

# Conteudo

- [Resumo](#Resumo)
- [Ferramentas Utilizadas](#Ferramentas)
- [Configurações](#Configurações)
- [Documentação](#Documentação)
- [Visão Geral](#Geral)
- [Projetos](#Projetos)

# Resumo

Este repositório reúne scripts em C desenvolvidos para o microcontrolador PIC18F4580 como parte dos projetos e exercícios práticos da disciplina de Microcontroladores do curso SEC-IPVC. 
Os projetos incluem configurações e operações com diversos periféricos, além do mini-projeto desenvolvido no final.


# Ferramentas

## MPLAB X IDE
Os projetos foram desenvolvidos no MPLAB X IDE, disponível para Windows, macOS e Linux. 
[Download MPLAB X IDE](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)

## Tiny Bootloader
O Tiny Bootloader é utilizado para gravar o código no PIC.

- [Download para Windows](http://www.etc.ugal.ro/cchiculita/software/picbootloader.htm)
- [Download para Linux e macOS](https://github.com/lcgamboa/tinybldlin)

 
# Configurações

# Documentação
- [Esquema Elétrico (PDF)](https://github.com/dventurb/PIC18F4580/blob/main/ESQUEMA_ELETRICO.pdf)
- [Datasheet PIC18F4580 (PDF)](https://github.com/dventurb/PIC18F4580/blob/main/DATASHEET.pdf)




# Geral

O microcontrolador é um pequeno computador em um único chip, possui um processador, memória e entradas e saídas para interagir. 

  ## TRIS 
    Define a direção dos pinos como entrada (1) ou saída (0).
    
  ## LAT
    Escrever estado lógico de um pino configurado como saída, com sinal alto (1) ou sinal baixo (0).
    
  ## PORT
    Ler o estado lógico dos pinos de entrada, com sinal alto (1) ou sinal baixo (0).


# Projetos

Os projetos deste repositório são variados e cobrem desde a configuração básica do microcontrolador até projetos intermediários com sensores e displays. 
Cada projeto está organizado em pastas e inclui scripts em C, com comentários explicativos e instruções de uso. Os projetos abordam tópicos como:

   ## 2. Portos de I/O - Exercícios
   ### Exercício 1
   **Alternância automática dos LEDs a cada 500 ms**  
     Desenvolva um software que alterna o estado dos LEDs no Kit de desenvolvimento, começando com LED1, LED2, LED4 e LED6 desligados (OFF) e os restantes ligados (ON).
     [Exercício 1](https://github.com/dventurb/PIC18F4580/blob/main/PROJETO_2/exercicio1_leds.c)

 ### Exercício 2
 **Alternância dos LEDs controlada pelo Botão 1**  
   Modifique o software do exercício anterior para que os LEDs alternem de estado quando o Botão 1 for acionado. Inicialmente, LED1, LED2, LED4 e LED6 devem estar ligados (ON).
   [Exercício 2](https://github.com/dventurb/PIC18F4580/blob/main/PROJETO_2/exercicio2_leds_botao.c)

 ### Exercício 3
 **Driver para display de 7 segmentos com contador acionado por botão**  
 Crie uma função que escreve números de 0 a 9 no display de 7 segmentos. O valor deve ser incrementado sempre que o Botão 1 for pressionado, reiniciando a contagem ao chegar a 9.
 [Exercício 3](https://github.com/dventurb/PIC18F4580/blob/main/PROJETO_2/exercicio3_display_contador.c)

  ## 3. Timers - Exercícios
   ### Exercício 1
   **Contador binário de 8 bits com LEDs**
   Desenvolva um contador que incremente de 0x00 a 0xFF, utilizando o Timer 0 para gerar atrasos. Os LEDs refletem o valor binário.
   [Exercício 1](https://github.com/dventurb/PIC18F4580/blob/main/PROJETO_3/TP3_Exer1.c)

   ### Exercício 2
   **Contador usando interrupções do Timer 0**
   Modifique o software do exercício anterior para utilizar interrupções em vez de polling, criando uma rotina de serviço de interrupção.
   [Exercício 2](https://github.com/dventurb/PIC18F4580/blob/main/PROJETO_3/TP3_Exer2.c)

   ### Exercício 3
   **Geração de onda quadrada no pino RD0**
   Desenvolva um software que gere uma onda quadrada de 2^n Hz, onde n é incrementado pelo Botão 1, até um máximo de 5, exibindo o valor no display de 7 segmentos.
   [Exercício 3](https://github.com/dventurb/PIC18F4580/blob/main/PROJETO_3/TP3_Exer3.c)

   ### Exercício 4
   **Varrimento de LEDs com Timer 0**
   Implemente um varrimento sequencial dos LEDs do kit utilizando o Timer 0 e suas interrupções, explorando o operador de shift bit a bit.
   [Exercício 4](https://github.com/dventurb/PIC18F4580/blob/main/PROJETO_3/TP3_Exer4.c)
