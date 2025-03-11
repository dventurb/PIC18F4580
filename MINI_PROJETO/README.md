# Mini Projeto - Simulação de um Ar-Condicionado 

O projeto simula o funcionamento de um Ar-Condicionado implementado no PIC18F4580. O projeto deve envolver os conceitos abordados na disciplina, incluindo Timers, Conversor Analógico-Digital (ADC) e Comunicação Serial (USART).

## Características


**Simulação do Sensor de Temperatura (ADC)**


O potenciômetro representa o sensor de temperatura, utilizando o Conversor Analógico-Digital (ADC) para simular a temperatura ambiente.


**Exibição da Temperatura Ambiente**


O potenciômetro simula um sensor de temperatura indicando o valor da temparatura ambiente, sendo um valor de 0ºC até 50ºC e exibido no Display de 7 segmentos com 1 casa decimal (ex.: 23.5).


**Modos de Operação & Modos de Controlo**


O Ar-Condicionado tem em 2 modos de controlo sendo o Modo Automatico, ajustando a temperatura com base na temperatura ambiente, e o Modo Manual, sendo a temperatura do AC ajustada pelo utilizador. Além disso, o sistema tem 3 modos de operação, sendo o +ARREFECIMENTO ligando o respetivo LED e ativando a vetoinha, o -ARREFECIMENTO ligando o respetivo LED, e o AQUECIMENTO ligando também o seu LED.


**Utilização do Timer**


O projeto utiliza o Timer 0 para controlar a leitura do valor do potenciômetro a cada 10 segundos.


**Comunicação Serial (USART)**


Os comandos para controlo do Ar-Condicionado são enviados por UART, além do valor da temperatura do AC sendo enviada periodicamente. 

**Utilização de Componentes Externos**


O projeto ainda utiliza uma Vetoinha ligada Externamente e ativada por meio de um transistor, e ainda um Buzzer representando os receção das ordens do utilizador.




