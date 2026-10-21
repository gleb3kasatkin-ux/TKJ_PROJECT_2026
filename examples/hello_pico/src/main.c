
#include <stdio.h>
#include <pico/stdlib.h>


int main() {
    stdio_init_all();
    while (!stdio_usb_connected()){
        sleep_ms(10);
    }
    sleep_ms(200);
    printf("Hello World\n");
    int i = 0;
    while(1) {
        printf("Iteration %d\n",i);
        sleep_ms(3000);
        i++;
    }
    return 0;
}

