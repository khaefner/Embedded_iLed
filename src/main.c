#include <stdio.h>



#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#define PIN 10   //M5stick built in LED

void countByTwo(void * params)
{
    int counter = 0;
    while (true)
    {
        /* code */
      counter=counter+2;
      printf("The current 2 count is %d\n",counter);
      vTaskDelay(2000/portTICK_PERIOD_MS);
    }
    
}

void countByThree(void * params)
{
    int counter = 0;
    while (true)
    {
        /* code */
     counter = counter +3;
     printf("The current 3 count is %d\n",counter);   
     vTaskDelay(3000/portTICK_PERIOD_MS);
    }
    
}

void blinkLed()
{
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



void app_main(void) {
    xTaskCreate( &countByTwo, /* Pointer to the function that implements the task. */
                "Count by two",/* Text name for the task. This is to facilitate debugging only. */
                2048, /* Stack depth - how much memory to use for this task*/
                NULL, /* This example does not use the task parameter. */
                1, /* This task will run at priority 1.  Higher is more higher priority */
                NULL ); /* Task Handler to refer to task later. This example does not use the task handle. */
    xTaskCreate(&countByThree,"Count By three",2048, NULL,2,NULL);  /*HThis is the task call on one line */
    xTaskCreatePinnedToCore(&blinkLed,"Blinky blink",1000,NULL,3,NULL,1); /* Blink the LED highest priority pinned to second core */
}