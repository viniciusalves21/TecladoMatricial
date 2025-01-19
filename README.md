# Teclado Matricial 4x4 com LEDs e Buzzer para Raspberry Pi Pico (Kit BitDogLab)

Este projeto demonstra a implementação de um sistema de leitura de teclado matricial 4x4, controle de LEDs (Verde, Azul e Vermelho) e emissão de som com um buzzer, utilizando um Raspberry Pi Pico.

## Descrição

O código em C implementa a leitura de um teclado matricial 4x4, onde cada tecla pressionada executa uma ação específica:

*   **Teclas 'A', 'B', 'C':** Acendem os LEDs Vermelho, Azul e Verde, respectivamente.
*   **Tecla 'D':** Acende todos os LEDs simultaneamente.
*   **Tecla '#':** Emite um beep curto através do buzzer usando modulação por largura de pulso (PWM).
*   **Tecla '*':** Reinicia o Raspberry Pi Pico.
*   **Demais Teclas (0-9):** Imprime o valor da tecla no monitor serial.

## Como Usar

1.  **Clone o repositório:** `git clone https://github.com/viniciusalves21/TecladoMatricial`.
2.  **Compile o código:** Utilize o Pico SDK para compilar o código.
3.  **Carregue o código no Pico:** Conecte o Pico ao computador em modo BOOTSEL e copie o arquivo `.uf2` gerado.
4.  **Abra o monitor serial:** Utilize um monitor serial para visualizar a saída do programa.

## Código

O código principal contém as seguintes funções:

*   `init_pins()`: Inicializa os pinos do teclado, LEDs e buzzer. Configura os pinos das linhas do teclado como entradas com pull-down e os pinos das colunas como saídas. Configura o buzzer para usar PWM.
*   `read_keypad()`: Implementa a lógica de leitura do teclado matricial, retornando o caractere da tecla pressionada ou 0 se nenhuma tecla for pressionada. Utiliza a técnica de varredura de matriz para identificar a tecla.
*   `set_all_leds(bool state)`: Liga ou desliga todos os LEDs simultaneamente.
*   `beep_buzzer()`: Emite um beep curto usando PWM no buzzer.
*   `main()`: Função principal que inicializa o sistema, lê as teclas pressionadas e executa as ações correspondentes (acender LEDs, emitir beep ou reiniciar o Pico).

## Demonstração

[Link para o vídeo ensaio https://drive.google.com/file/d/1JMqDiaJGX9THvZJo-_wFFdM2akuZc41Y/view?usp=sharing]

## Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues e pull requests.


Este README fornece uma visão geral completa do projeto. O vídeo de demonstração oferece uma apresentação visual do sistema em funcionamento.
