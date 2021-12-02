/*
 * SST25VF016B.h
 *
 *  Created on: Dec 1, 2021
 *      Author: mrem
 */
#include "main.h"

#ifndef INC_SST25VF016B_H_
#define INC_SST25VF016B_H_

#define WREN 0x06
#define BYTE_PROGRAM 0x02
#define READ 0x03
#define CHER 0x60	//Chip-Erase

void sst25vf016b_write(SPI_HandleTypeDef* hspi, uint32_t adr, uint8_t data);
uint8_t sst25vf016b_read(SPI_HandleTypeDef* hspi, uint32_t adr);
void sst25vf016b_erase(SPI_HandleTypeDef* hspi);

#endif /* INC_SST25VF016B_H_ */
