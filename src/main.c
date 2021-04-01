#include <stdio.h>



#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#define PIN 10   //M5stick built in LED


static TaskHandle_t rHandler = NULL;

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


void sender(void * params)
{
    while (true)
    {
        xTaskNotify(rHandler, /*THe task handler*/
                    1,   /*data we are sending*/
                    eSetValueWithOverwrite); /*Notify Action  this one overwrites the data*/
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    
}

void receiver(void * params)
{
    uint data;
    while (true)
    {
        xTaskNotifyWait(0,0,&data,portMAX_DELAY);
        printf("Received:  %d\n",data);
    }
    
}


void app_main(void) 
{
    xTaskCreate(&receiver,"reciever",2048,NULL,2,&rHandler);
    xTaskCreate(&sender,"sender",2048,NULL,2,NULL);
}