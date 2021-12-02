/*
 * SST25VF016B.c
 *
 *  Created on: Dec 1, 2021
 *      Author: mrem
 */
#include "SST25VF016B.h"

void sst25vf016b_write(SPI_HandleTypeDef* hspi, uint32_t adr, uint8_t data)
{
	uint8_t Buffer[2];
	Buffer[0] = WREN;
	HAL_GPIO_WritePin(GPIOD, CS_Pin, RESET);
	HAL_SPI_Transmit(hspi, Buffer, 1, 5);
	HAL_GPIO_WritePin(GPIOD, CS_Pin, SET);

	uint8_t buffer[5];
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, RESET);
	//HAL_Delay(10);
	buffer[0] = BYTE_PROGRAM;
	buffer[1] = (adr >> 16) & 0xFF;
	buffer[2] = (adr >> 8) & 0xFF;
	buffer[3] = (adr >> 0) & 0xFF;
	buffer[4] = data;
	HAL_SPI_Transmit(hspi, buffer, 5, 10);
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, SET);
}

uint8_t sst25vf016b_read(SPI_HandleTypeDef* hspi, uint32_t adr)
{
	uint8_t BufferTx[4];
	uint8_t value;
	BufferTx[0] = READ;
	BufferTx[1] = (adr >> 16) & 0xFF;
	BufferTx[2] = (adr >> 8) & 0xFF;
	BufferTx[3] = (adr >> 0) & 0xFF;
	HAL_GPIO_WritePin(GPIOD, CS_Pin, RESET);
	HAL_SPI_Transmit(hspi, BufferTx, 4, 10);
	HAL_SPI_Receive(hspi, &value, 1, 5);
	HAL_GPIO_WritePin(GPIOD, CS_Pin, SET);
	return value;
}

void sst25vf016b_erase(SPI_HandleTypeDef* hspi)
{
	uint8_t buffer = WREN;
	HAL_GPIO_WritePin(GPIOD, CS_Pin, RESET);
	HAL_SPI_Transmit(hspi, &buffer, 1, 5);
	HAL_GPIO_WritePin(GPIOD, CS_Pin, SET);
	buffer = CHER;
	HAL_GPIO_WritePin(GPIOD, CS_Pin, RESET);
	HAL_SPI_Transmit(hspi, &buffer, 1, 5);
	HAL_GPIO_WritePin(GPIOD, CS_Pin, SET);
}





