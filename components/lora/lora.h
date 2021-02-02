#include <stdbool.h>
#include <stdint.h>

/* Tx and Rx interrupt */
#define GPIO_INTR_LORA 33 

struct lora {
    // initialize the module to be ready to connect
    int8_t  (*init)(uint8_t pcie);

    // establish a connection with the server
    int8_t  (*connect)();

    // return true if connection is considered estavlished
    bool (*is_connected)();

    // send bytes through the interface
    int8_t  (*send)(const void* data, size_t len);

    // receive (blocking) on port
    int8_t (*recvon)(const void* rxdata, size_t len, uint16_t port);

    // Interrupt counter
    uint16_t n_interrupts;
};


void register_lora(struct lora* lora);
