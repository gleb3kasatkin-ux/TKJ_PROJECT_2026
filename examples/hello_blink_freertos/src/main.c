/**
 * SPDX-License-Identifier: BSD-3-Clause
 */
 //NOTE: THIS PROGRAM ONLY WORKS WITH PICOW

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "FreeRTOS.h"
#include "task.h"

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 1000
#endif

// Init LED backend
static int pico_led_init(void) {
    return cyw43_arch_init(); // for Pico W
}

// Set LED on/off
static void pico_set_led(bool on) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
}

// ---- FreeRTOS task ----
static void led_task(void *arg) {
    (void)arg;
    
    pico_led_init();

    // Wait until the USB is connected
    // Uncomment following while if there are problems with the USB.
    // while (!stdio_usb_connected()) {
    //    vTaskDelay(pdMS_TO_TICKS(10));
    //}

    for (;;) {
        pico_set_led(true);
        printf("Tack-FreeRTOS\n");
        vTaskDelay(pdMS_TO_TICKS(LED_DELAY_MS));
        pico_set_led(false);
        vTaskDelay(pdMS_TO_TICKS(LED_DELAY_MS));
    }
}

int main(void) {
    stdio_init_all();

    TaskHandle_t myTaskHandle = NULL;
   
    // Create the single blinky/printf task
    // (en) We create a task
    BaseType_t result =xTaskCreate(led_task,       // (en) Task function
                "led",          // (en) Name of the task 
                512,            // (en) Size of the stack for this task (in words). Generally 1024 or 2048
                NULL,           //(en) Arguments of the task 
                2,              // (en) Priority of this task
                &myTaskHandle); // (en) A handle to control the execution of this task

    if(result != pdPASS) {
        printf("Task create failed\n");
        return 0;
    }
    // Start the scheduler (never returns)
    vTaskStartScheduler();

}
