#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"

#include "snes_controller.h"

//source for the protocol https://fpgalover.com/ip-cores/snes-controller-core
#define LATCH_TIME_US 12
#define DATA_CYCLES 16
#define NUM_BUTTONS 16
#define END_WAIT_TIME_US 12
#define CLK_HALF_CYCLE_US 6

static uint8_t latch;
static uint8_t data;
static uint8_t clk;

/**
 * 
 */
void snes_controller_init(int latch_pin, int data_pin, int clk_pin)
{
    latch = latch_pin;
    gpio_init(latch);
    gpio_set_dir(latch, GPIO_OUT);
    gpio_put(latch, false);

    clk = clk_pin;
    gpio_init(clk);
    gpio_set_dir(clk, GPIO_OUT);
    gpio_put(latch, true);

    data = data_pin;
    gpio_init(data);
    gpio_set_dir(data, GPIO_IN);
}

/**
 * Gets button states. Blocking call
 * Last 4 buttons read are garbage, ignore.
 */
void snes_get_buttons(uint8_t * buttons)
{
    /* latch high for 16 microseconds*/
    gpio_put(latch, true);
    busy_wait_us(LATCH_TIME_US);
    gpio_put(latch, false);

    for(int i = 0; i < DATA_CYCLES; i++)
    {
        //CLK
        gpio_put(clk, true);
        busy_wait_us(CLK_HALF_CYCLE_US);
        gpio_put(clk, false);

        //read data into array and invert it (because 1 = not pushed)
        buttons[i] = (uint8_t) !gpio_get(data);
        //finish CLK cycle
        busy_wait_us(CLK_HALF_CYCLE_US);
    }
    gpio_put(clk, true);
    busy_wait_us(END_WAIT_TIME_US);

    //clear last 4 inputs since they are unused
    for(int i = 1; i < 5; i++)
    {
        buttons[NUM_BUTTONS - i] = 0;
    }

}
