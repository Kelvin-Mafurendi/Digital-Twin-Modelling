// onewire_custom.h
#ifndef ONEWIRE_CUSTOM_H
#define ONEWIRE_CUSTOM_H

#include "F2837xD_device.h"
#include "F2837xD_gpio.h"

void onewire_init(uint32_t pin_number);
uint8_t onewire_reset(uint32_t pin_number);
void onewire_write_bit(uint32_t pin_number, uint8_t bit);
uint8_t onewire_read_bit(uint32_t pin_number);
void onewire_write_byte(uint32_t pin_number, uint8_t byte_val);
uint8_t onewire_read_byte(uint32_t pin_number);
float read_ds18b20_temperature(uint32_t pin_number);

#endif