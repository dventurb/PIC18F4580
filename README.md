<div align="center" style="text-align: center">
<img src="https://kswichit.net/887Projectboard/images/IMG_0683.jpg" alt="PIC18F4580 Logo"/>
<h3>Projetos em C com PIC18F4580</h3>
<p>
  Repositório com projetos em C, para o microcontrolador PIC18F4580, desenvolvidos na disciplina de Microcontroladores.
</p>
</div>

# Conteudo

- [Resumo](#Resumo)
- [Ferramentas Utilizadas](#Ferramentas)
- [Configurações](#Configurações)
- [Visão Geral](#Geral)
- [Projetos](#Projetos)

# Resumo

Este repositório reúne scripts em C desenvolvidos para o microcontrolador PIC18F4580 como parte dos projetos e exercícios práticos da disciplina de Microcontroladores do curso. 
Os projetos incluem configurações e operações com diversos periféricos, além de aplicações básicas e intermediárias de controle e automação.


# Ferramentas

## MPLAB X IDE
Os projetos foram desenvolvidos no MPLAB X IDE, disponível para Windows, macOS e Linux. 
[Download MPLAB X IDE](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)

## Tiny Bootloader
O Tiny Bootloader é utilizado para gravar o código no PIC.

- [Download para Windows](http://www.etc.ugal.ro/cchiculita/software/picbootloader.htm)
- [Download para Linux e macOS](https://github.com/lcgamboa/tinybldlin)

 
# Configurações




# Geral

O microcontrolador PIC18F4580 é um dispositivo robusto, ideal para aplicações que exigem controle preciso e uso de múltiplos periféricos. Ele inclui registradores como TRIS, LAT e PORT para controle das portas de entrada e saída:

  ## TRIS 
    Define a direção dos pinos de um PORT como entrada (1) ou saída (0).
    
  ## LAT
    Controla o estado lógico de um pino configurado como saída, útil para garantir estabilidade em operações de escrita.
    
  ## PORT
    Lê ou escreve diretamente o estado dos pinos, sendo a porta utilizada para comunicação com dispositivos externos.


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
