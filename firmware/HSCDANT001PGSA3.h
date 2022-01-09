/*
 * HSCDANT001PGSA3.h
 *
 *  Created on: Jan 3, 2022
 *      Author: mgoodwin
 */

#ifndef HSCDANT001PGSA3_H_
#define HSCDANT001PGSA3_H_

#include <Arduino.h>
#include <SPI.h>
#include <stdint.h>

#define CS_PIN 51

typedef struct {
	uint16_t x;
	int16_t	y;
	int16_t	z;
} DATA;

#endif /* HSCDANT001PGSA3_H_ */
