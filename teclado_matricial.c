#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Definição dos pinos das linhas e colunas do teclado
static const uint ROW_PINS[4] = {8, 7, 6, 5};   // R1, R2, R3, R4
static const uint COL_PINS[4] = {4, 3, 2, 28};  // C1, C2, C3, C4

// Tabela de mapeamento das teclas
static const char KEYPAD[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Definição dos pinos dos LEDs
#define LED_GREEN   11
#define LED_BLUE    12
#define LED_RED     13

// Definição do pino do buzzer
#define BUZZER_PIN  21

// Frequência desejada para o buzzer em Hz
#define BUZZER_FREQ 2000.0f

// Inicializa todos os pinos necessários (teclado, LEDs, buzzer)
void init_pins(void) {
    stdio_init_all();

    // -- Teclado --
    // Configura pinos das linhas do teclado como entradas com pull-down
    for (int i = 0; i < 4; i++) {
        gpio_init(ROW_PINS[i]);
        gpio_set_dir(ROW_PINS[i], GPIO_IN);
        gpio_pull_down(ROW_PINS[i]);
    }

    // Configura pinos das colunas do teclado como saídas (inicialmente em nível baixo)
    for (int i = 0; i < 4; i++) {
        gpio_init(COL_PINS[i]);
        gpio_set_dir(COL_PINS[i], GPIO_OUT);
        gpio_put(COL_PINS[i], 0);
    }