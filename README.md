# Teclado Matricial 4x4 com LEDs e Buzzer para Raspberry Pi Pico (Kit BitDogLab)

Este projeto implementa um teclado matricial 4x4 com controle de LEDs e um buzzer usando um Raspberry Pi Pico. O código em C fornece a leitura das teclas pressionadas, o acendimento de LEDs específicos para as teclas 'A', 'B', 'C' e 'D', o acendimento de todos os LEDs com a tecla 'D' e a emissão de um beep com a tecla '#'.

## Funcionalidades

*   **Leitura de Teclado Matricial 4x4:** Detecta qual tecla do teclado matricial 4x4 foi pressionada.
*   **Controle de LEDs:** Acende LEDs específicos (Verde, Azul, Vermelho) correspondentes às teclas 'A', 'B' e 'C'. A tecla 'D' acende todos os LEDs.
*   **Buzzer:** Emite um beep usando PWM quando a tecla '#' é pressionada.
*   **Anti-Bounce:** Implementa um pequeno delay para evitar leituras múltiplas devido a flutuações mecânicas das teclas.
