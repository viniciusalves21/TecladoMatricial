#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "pico/bootrom.h"


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

// Frequência desejada para o buzzer   em Hz
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

    // -- LEDs --
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_GREEN, 0);

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_put(LED_BLUE, 0);

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, 0);

    // -- Buzzer (via PWM) --
    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);

    uint32_t f_sys = clock_get_hz(clk_sys);  

    float divider = 64.0f;
    uint32_t top = (uint32_t)( (float)f_sys / (divider * BUZZER_FREQ) + 0.5f ) - 1;
    pwm_config config = pwm_get_default_config();

    pwm_config_set_clkdiv(&config, divider);

    pwm_config_set_wrap(&config, top);

    pwm_init(slice_num, &config, false);

    // Para começar, duty cycle = 0
    pwm_set_gpio_level(BUZZER_PIN, 0);
}

// Retorna a tecla pressionada ou 0 se nenhuma for pressionada
char read_keypad(void) {
    for (int col = 0; col < 4; col++) {
        // Coloca a coluna atual em nível alto
        gpio_put(COL_PINS[col], 1);

        // Verifica as linhas
        for (int row = 0; row < 4; row++) {
            if (gpio_get(ROW_PINS[row])) {
                sleep_ms(10);
                // Checa novamente para evitar flutuações
                if (gpio_get(ROW_PINS[row])) {
                    gpio_put(COL_PINS[col], 0);
                    return KEYPAD[row][col];
                }
            }
        }
        // Retorna a coluna para nível baixo
        gpio_put(COL_PINS[col], 0);
    }
    return 0;
}

// Liga ou desliga todos os LEDs (1 = liga, 0 = desliga)
void set_all_leds(bool state) {
    gpio_put(LED_GREEN, state);
    gpio_put(LED_BLUE, state);
    gpio_put(LED_RED, state);
}

// Emite um beep usando PWM por ~100ms
void beep_buzzer(void) {
    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);

    uint16_t top = pwm_hw->slice[slice_num].top;
    uint16_t level = top / 2;  // 50%

    // Ativa a saída PWM
    pwm_set_enabled(slice_num, true);

    // Define o duty cycle
    pwm_set_gpio_level(BUZZER_PIN, level);

    // Toca por 100 ms
    sleep_ms(100);

    // Desliga o PWM para silenciar
    pwm_set_enabled(slice_num, false);

    pwm_set_gpio_level(BUZZER_PIN, 0);
}

// Programa principal
int main() {
    init_pins();
    printf("Iniciando leitura do Teclado 4x4...\n");

    while (true) {
        // Lê a tecla pressionada
        char key = read_keypad();
        
        // Se houver tecla pressionada, faz o tratamento
        if (key != 0) {
            printf("Tecla pressionada: %c\n", key);

            // Desliga todos LEDs antes de acender somente o escolhido
            gpio_put(LED_GREEN, 0);
            gpio_put(LED_BLUE, 0);
            gpio_put(LED_RED, 0);

            switch (key) {
                case 'A':
                    // Acende LED vermelho
                    gpio_put(LED_RED, 1);
                    break;
                case 'B':
                    // Acende LED azul
                    gpio_put(LED_BLUE, 1);
                    break;
                case 'C':
                    // Acende LED verde
                    gpio_put(LED_GREEN, 1);
                    break;
                case 'D':
                    // Acende todos os LEDs
                    set_all_leds(true);
                    break;
                case '#':
                    // Emite um beep por PWM
                    beep_buzzer();
                    break;
                case '*':
                    reset_usb_boot(0,0);
                default:
                    break;
            }

            // Espera até a tecla ser solta para evitar repetição contínua
            while (read_keypad() != 0) {
                tight_loop_contents();
            }
        }

        // Pequena pausa
        sleep_ms(50);
    }
    return 0;
}
