/*
 * PWM_I2C.c
 *
 *  Created on: Nov 17, 2021
 *      Author: mrem
 */

#include "PWM_I2C.h"

void set_PWM_freq(uint16_t freq)
{
	sleep_mode_on();
	uint8_t psc = round((double)INT_FREQUENCY/(MAX_VALUE * freq)) - 1;
	send_I2C_data(psc, 0xFE);
	uint8_t message[25];
	sprintf((char*)message, "Set frequency: %d\r\n", freq);
	HAL_UART_Transmit(&huart3, &message, strlen((char*)message), 50);
	sleep_mode_off();
}

void set_PWM_duty(uint8_t duty, uint8_t led)
{
	if((duty > 100) && (duty < 0) && (led < 0) && (led > 15))
	{
		return;
	}
	uint8_t led_controls[NUM_REG_BY_CHANNEL];
	uint16_t led_off = ((float)duty * MAX_VALUE / 100) - 1;
	led_controls[0] = 0x00;
	led_controls[1] = 0x00;	//because i don't use delay time before led on, and change duty only by led off
	led_controls[3] = led_off / 256;	//take 3rd digit with the led_off, because we have 12-bit PWM, but we have two 8-bit register for this
	led_controls[2] = led_off - (led_controls[3] * 256);	//take 1st and 2nd digit with the led_off, for LEDx_OFF_L
	for(uint8_t i = 0; i < NUM_REG_BY_CHANNEL; i++)
		send_I2C_data(led_controls[i], NUM2ADR(led) + i);
	uint8_t message[24];
	sprintf((char*)message, "Set Duty on LED%d: %d%%\r\n",led + 1, duty);
	HAL_UART_Transmit(&huart3, &message, strlen((char*)message), 50);
}

void send_I2C_data(uint8_t data, uint8_t adr)
{
	uint8_t Buffer[2];
	Buffer[0] = adr;
	Buffer[1] = data;
	HAL_I2C_Master_Transmit(&hi2c1, ADR, (uint8_t*)&Buffer, 2, 100);
}

void sleep_mode_on(void)
{
	send_I2C_data(0b00010000, 0x00);
	HAL_UART_Transmit(&huart3, "Sleep mode ON\r\n", 15, 50);
}

void sleep_mode_off(void)
{
	send_I2C_data(0b00000000, 0x00);
	HAL_UART_Transmit(&huart3, "Sleep mode OFF\r\n", 16, 50);
}

void state_all_PWM_channels(_Bool state)
{
	HAL_GPIO_WritePin(PWM_EN_GPIO_Port, PWM_EN_Pin, !state);
	if (state)
		HAL_UART_Transmit(&huart3, "All channels ENABLE\r\n", 21, 50);
	else
		HAL_UART_Transmit(&huart3, "All channels DISABLE\r\n", 22, 50);
}

