#include <stdio.h>



#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"



#define PIN 10   //M5stick built in LED

xQueueHandle queue;  /*declare queue handle*/

void taskProducer(void * params)
{
    /*Producer puts up to three items on the queue*/
    int counter = 0;
    while (true)
    {
        /* code */
      counter++;
      printf("The producer counter is %d\n",counter);
      long success = xQueueSend(queue,&counter,1000/portTICK_PERIOD_MS); /*send to hue handle the address of the counter and timeout of 1000 ms* return success*/
      if(success)
      {
          printf("Successfully added item to the queue\n");
      }
      else
      {
          printf("failed to add Item to the queue\n");
      }
      vTaskDelay(2000/portTICK_PERIOD_MS);
    }
    
}

void taskConsumer(void * params)
{
    int receivedInt = 0;
    while (true)
    {
     xQueueReceive(queue, &receivedInt,5000/portTICK_PERIOD_MS);   /*queue we are receiving from, the address fo memory tto store in, size of what to store*/
     printf("Consumer got %d from queue\n",receivedInt);   
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
    queue = xQueueCreate(3,sizeof(int));   /* three items on the queueu of size integer*/
    xTaskCreate( &taskProducer, /* Pointer to the function that implements the task. */
                "Count by two",/* Text name for the task. This is to facilitate debugging only. */
                2048, /* Stack depth - how much memory to use for this task*/
                NULL, /* This example does not use the task parameter. */
                1, /* This task will run at priority 1.  Higher is more higher priority */
                NULL ); /* Task Handler to refer to task later. This example does not use the task handle. */
    xTaskCreate(&taskConsumer,"Count By three",2048, NULL,2,NULL);  /*HThis is the task call on one line */
    xTaskCreatePinnedToCore(&blinkLed,"Blinky blink",1000,NULL,3,NULL,1); /* Blink the LED highest priority pinned to second core */
}