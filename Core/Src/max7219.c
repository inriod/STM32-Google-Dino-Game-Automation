/*
 * max7219.c
 *
 *  Created on: Nov 23, 2026
 *      Author: Ashot
 */
#include "max7219.h"

extern SPI_HandleTypeDef hspi1;

void MAX7219_Write(uint8_t reg, uint8_t data)
{
	uint8_t bytes[2];
	bytes[0] = reg;
	bytes[1] = data;

	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, bytes, 2, 10);
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}

void MAX7219_Init(void)
{
	MAX7219_Write(0x09, 0x00); // no digit decoding (we use a matrix)
	MAX7219_Write(0x0A, 0x03); // brightness 0..15
	MAX7219_Write(0x0B, 0x07); // use all 8 rows
	MAX7219_Write(0x0C, 0x01); // wake up
	MAX7219_Write(0x0F, 0x00); // display test off
	MAX7219_Clear();
}

void MAX7219_Clear(void)
{
	uint8_t row;
	for (row = 1; row <= 8; row++)
	{
		MAX7219_Write(row, 0x00);
	}
}

void MAX7219_Show(uint8_t picture[8])
{
	uint8_t row;
	for (row = 0; row < 8; row++)
	{
		MAX7219_Write(row + 1, picture[row]);
	}
}
