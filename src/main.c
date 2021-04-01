#include <stdio.h>



#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#define PIN 10   //M5stick built in LED


void app_main(void) {
    gpio_pad_select_gpio(PIN);
    gpio_set_direction(PIN,GPIO_MODE_OUTPUT); //Tell the device to set this pin as output
    int ledOn = 0;
    while(1)
    {
        ledOn = !ledOn;
        gpio_set_level(PIN, ledOn);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}