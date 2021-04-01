#include <stdio.h>



#include "driver/gpio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"


#define PIN 10   //M5stick built in LED

xSemaphoreHandle mutexData;

void protectedWrite(char *message)
{
    printf(message);
}

void task1(void * params)
{
    while (true)
    {
        if(xSemaphoreTake(mutexData,1000/portTICK_PERIOD_MS))
        {
            protectedWrite("I'm task 1\n");
            xSemaphoreGive(mutexData);
        }
        else
        {
            printf("Could not get protected write\n");
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    

}

void task2(void * params)
{
    while (true)
    {
        if(xSemaphoreTake(mutexData,1000/portTICK_PERIOD_MS))
        {
            protectedWrite("I'm task 2\n");
            xSemaphoreGive(mutexData);
        }
        else
        {
            printf("Task2: Could not get protected write\n");
        }
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}


void app_main(void) 
{
    mutexData = xSemaphoreCreateMutex();
    xTaskCreate(&task1,"Task 1",2048,NULL,1,NULL);
    xTaskCreate(&task2,"Task 2",2048,NULL,1,NULL);
}