/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */
#include <mbed.h>
 #include <iostream>

 #define BLINKING_RATE 500ms
UnbufferedSerial pc(USBTX, USBRX,2400);

void parse_hex(uint32_t hex, float r, float g, float b) {
    r = (hex >> 16) & 0xFF;
    g = (hex >> 8) & 0xFF;
    b = hex & 0xFF;
}

void calculate_pwm_duty_cycle(uint8_t r, uint8_t g, uint8_t b, uint16_t& pr, uint16_t& pg, uint16_t& pb) {
    pr = r * 1 / 255;
    pr = 1-(float)pr;
    pg = g * 1 / 255;
    pg = 1-(float)pg;
    pb = b * 1 / 255;
    pb = 1-(float)pb;

}

int main() {
    PwmOut ledR(LED1);
    PwmOut ledG(LED2);
    PwmOut ledB(LED3);
    
    string hex; 
    cout << 'ingresar HEX sin el #';
    cin >> hex;

    uint32_t rgbValue = std::stoul(hex,nullptr,16);

    float r, g, b;
    parse_hex(rgbValue, r, g, b);

    uint16_t pr, pg, pb;
    calculate_pwm_duty_cycle(r, g, b, pr, pg, pb);

    ledR.write(pr);
    ledG.write(pg);
    ledB.write(pb);
}

