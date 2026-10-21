#include <stdio.h>
#include <string.h>

#include <FreeRTOS.h>
#include <pico/stdlib.h>
#include <queue.h>
#include <task.h>



// (en) A task needs its own internal stack memory
#define STACKSIZE 512

// (en) Implementation of task function
void myTaskFxn(void * pvParameters) {
    
    // (en) The eternal life of a task
    while(1) {
        printf("My arguments are %d\n", (int)pvParameters);

        // (en) Politely sleeping for 4s
        vTaskDelay(4000 / portTICK_PERIOD_MS);
    }
}


int main() {
    stdio_init_all();
    while (!stdio_usb_connected()){
        sleep_ms(10);
    }
    sleep_ms(200);
    TaskHandle_t myTaskHandle = NULL;

    // (en) We create a task
    BaseType_t result = xTaskCreate(
        myTaskFxn,  // (en) Task function
        "MY_TASK",  // (en) Name of the task
        STACKSIZE,  // (en) Size of the stack for this task
        (void *) 127, // (en) Arguments of the task
        2,  // (en) Priority of this task
        &myTaskHandle // (en) A handle to control the execution of this task
    );
    if(result != pdPASS) {
        printf("Task create failed\n");
        return 0;
    }

    // (en) Greetings to the console
    printf("Hello world!\n");
    // Start the scheduler
    vTaskStartScheduler();
    return 0;


    
    return 0;
}

