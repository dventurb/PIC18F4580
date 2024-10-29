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
- [Visão Geral](#Geral)
- [Projetos](#Projetos)

# Resumo

Este repositório reúne scripts em C desenvolvidos para o microcontrolador PIC18F4580 como parte dos projetos e exercícios práticos da disciplina de Microcontroladores do curso. 
Os projetos incluem configurações e operações com diversos periféricos, além de aplicações básicas e intermediárias de controle e automação.

## Conteúdo

  ### Controle de LEDs
    Scripts para controle de LEDs individuais e sequenciais, explorando modos de acionamento, PWM e temporizações.

  ### Display de 7 Segmentos
        Códigos para exibir valores em displays de 7 segmentos, incluindo contagem, controle de múltiplos dígitos e configuração dos segmentos.

   ### Comunicação Serial (USART, SPI, I2C)
        Implementações de comunicação serial com o PIC18F4580, possibilitando integração com sensores, outros microcontroladores e dispositivos externos.

  ### Temporizadores e Interrupções
        Uso de temporizadores e configurações de interrupções para controle preciso de eventos e automação de tarefas.
        
  ### Sensores e Atuadores
        Exemplos de interface com sensores e controle de atuadores básicos, aplicando conceitos de controle digital.

# Ferramentas

Os projetos foram desenvolvidos no MPLAB X IDE, disponível para Windows, macOS e Linux. [Download MPLAB X IDE](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)



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

   ## Controle de LEDs e displays de 7 segmentos
   ## Configuração de temporizadores e interrupções
   ## Comunicação serial e interface com sensores
