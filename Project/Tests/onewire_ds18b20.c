// onewire_custom.c
#include "onewire_custom.h"
#include "F2837xD_device.h"

#define DELAY_US(x) \
    do { \
        volatile uint32_t delay_count = (uint32_t)(x * (DEVICE_SYSCLK_FREQ / 1000000.0 / 5.0)); \
        while(delay_count--) {} \
    } while(0)

// Set pin as output
static void set_pin_output(uint32_t pin_number) {
    GPIO_SetupPinMux(pin_number, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(pin_number, GPIO_OUTPUT, GPIO_PUSHPULL);
}

// Set pin as input
static void set_pin_input(uint32_t pin_number) {
    GPIO_SetupPinMux(pin_number, GPIO_MUX_CPU1, 0);
    GPIO_SetupPinOptions(pin_number, GPIO_INPUT, GPIO_PUSHPULL);
}

void onewire_init(uint32_t pin_number) {
    EALLOW;
    set_pin_output(pin_number);
    GPIO_WritePin(pin_number, 1); // Pull high initially
    EDIS;
}

uint8_t onewire_reset(uint32_t pin_number) {
    uint8_t presence;
    
    EALLOW;
    set_pin_output(pin_number);
    GPIO_WritePin(pin_number, 0); // Pull low
    EDIS;
    DELAY_US(480); // Reset pulse
    
    EALLOW;
    set_pin_input(pin_number);
    EDIS;
    DELAY_US(70); // Wait for presence pulse
    
    presence = !GPIO_ReadPin(pin_number); // Read presence (inverted)
    DELAY_US(410); // Complete the reset sequence
    
    return presence;
}

void onewire_write_bit(uint32_t pin_number, uint8_t bit) {
    EALLOW;
    set_pin_output(pin_number);
    GPIO_WritePin(pin_number, 0); // Start slot
    EDIS;
    
    if (bit) {
        DELAY_US(10); // Write '1' - short low pulse
        EALLOW;
        set_pin_input(pin_number); // Release line
        EDIS;
        DELAY_US(55); // Complete slot time
    } else {
        DELAY_US(65); // Write '0' - long low pulse
        EALLOW;
        set_pin_input(pin_number); // Release line
        EDIS;
    }
}

uint8_t onewire_read_bit(uint32_t pin_number) {
    uint8_t bit;
    
    EALLOW;
    set_pin_output(pin_number);
    GPIO_WritePin(pin_number, 0); // Start slot
    EDIS;
    DELAY_US(5);
    
    EALLOW;
    set_pin_input(pin_number);
    EDIS;
    DELAY_US(10);
    
    bit = GPIO_ReadPin(pin_number);
    DELAY_US(50); // Complete slot time
    
    return bit;
}

void onewire_write_byte(uint32_t pin_number, uint8_t byte_val) {
    for (int i = 0; i < 8; i++) {
        onewire_write_bit(pin_number, byte_val & 0x01);
        byte_val >>= 1;
    }
}

uint8_t onewire_read_byte(uint32_t pin_number) {
    uint8_t byte_val = 0;
    for (int i = 0; i < 8; i++) {
        byte_val >>= 1;
        if (onewire_read_bit(pin_number)) {
            byte_val |= 0x80;
        }
    }
    return byte_val;
}

float read_ds18b20_temperature(uint32_t pin_number) {
    uint8_t data[9];
    int16_t raw_temp;
    float temperature;
    
    // Reset and check presence
    if (!onewire_reset(pin_number)) {
        return -999.0; // Error code
    }
    
    // Skip ROM command (assuming single sensor)
    onewire_write_byte(pin_number, 0xCC);
    
    // Start temperature conversion
    onewire_write_byte(pin_number, 0x44);
    
    // Wait for conversion (you might want to poll instead)
    DELAY_US(750000); // 750ms delay
    
    // Reset again
    if (!onewire_reset(pin_number)) {
        return -999.0; // Error code
    }
    
    // Skip ROM and read scratchpad
    onewire_write_byte(pin_number, 0xCC);
    onewire_write_byte(pin_number, 0xBE);
    
    // Read 9 bytes of scratchpad
    for (int i = 0; i < 9; i++) {
        data[i] = onewire_read_byte(pin_number);
    }
    
    // Convert temperature
    raw_temp = (data[1] << 8) | data[0];
    temperature = (float)raw_temp / 16.0;
    
    return temperature;
}