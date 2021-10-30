#include <stdlib.h>
#include <stdio.h>
#include "pico/stdlib.h"

#include "snes_controller.h"

int main()
{
    //debugging led
    stdio_init_all();
    //TODO
    //SNES connections.
    const uint8_t latch_pin = 17; // output GPIO22
    const uint8_t data_pin = 3;  // input GPIO5
    const uint8_t clk_pin = 16;   // output GPIO21

    uint8_t buttons[NUM_BUTTONS];
    snes_controller_init(latch_pin, data_pin, clk_pin);
    while (true)
    {
        snes_get_buttons(buttons);
        for (int i = 0; i < NUM_BUTTONS; i++)
        {
            printf("BUTTON %d: value: %d\n", i, buttons[i]);
        }
        busy_wait_ms(2000);
    }
}