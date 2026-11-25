/*
 * max7219.h
 *
 *  Created on: Nov 23, 2026
 *      Author: Ashot
 */

#ifndef INC_MAX7219_H_
#define INC_MAX7219_H_

#include "main.h"

void MAX7219_Write(uint8_t reg, uint8_t data);
void MAX7219_Init(void);
void MAX7219_Clear(void);
void MAX7219_Show(uint8_t picture[8]);

#endif /* INC_MAX7219_H_ */
