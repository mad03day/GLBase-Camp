/*
 * PWM_I2C.h
 *
 *  Created on: Nov 17, 2021
 *      Author: mrem
 */
#include <math.h>
#include <string.h>
#include "main.h"

#define ADR 0x80
#define INT_FREQUENCY 25000000
#define MAX_VALUE 4096
#define NUM2ADR(num) (num)*4+6
#define NUM_REG_BY_CHANNEL 4	//number of registers for setting duty cycle in one led channel
#define ENABLE 1
#define DISABLE 0

#ifndef INC_PWM_I2C_H_
#define INC_PWM_I2C_H_

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart3;

void set_PWM_freq(uint16_t freq);
void set_PWM_duty(uint8_t duty, uint8_t led);
void send_I2C_data(uint8_t data, uint8_t adr);
void sleep_mode_on(void);
void sleep_mode_off(void);
void state_all_PWM_channels(_Bool state);

#endif /* INC_PWM_I2C_H_ */
