#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "lora.h"

struct lora *g_lora;


void gpio_33_isr_handler(void *args)
{
    g_lora->n_interrupts++;
}

void task_register_txrx_intr(void *pvParams)
{

    gpio_install_isr_service(0);
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_NEGEDGE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_down_en = false;
    io_conf.pull_up_en = false;
    io_conf.pin_bit_mask = (1ULL << GPIO_INTR_LORA);
    gpio_config(&io_conf);

    gpio_isr_handler_add(33, gpio_33_isr_handler, NULL);
    vTaskDelete(NULL);
}

int8_t init(uint8_t pcie) {
    printf("Stub initialization\n");
    xTaskCreate(task_register_txrx_intr, "Register LoRa Interrupt", 1024 * 2, NULL, 10, NULL);
    return 0;
}

int8_t connect() {
    printf("Stub connect\n");
    return 0;
}

bool is_connected() {
    printf("Stub is_connected\n");
    return true;
}

int8_t send(const void* data, size_t len) {
    printf("Stud send\n");
    return 1;
}

int8_t recvon(const void* rxdata, size_t  len, uint16_t port) {
    printf("Stub recvon\n");
    return 1;
}


void register_lora(struct lora *lora) {
    memset(lora, 0, sizeof(struct lora));
    lora->init = init;
    lora->connect = connect;
    lora->is_connected = is_connected;
    lora->send = send;
    lora->recvon = recvon;
    g_lora = lora;
}
