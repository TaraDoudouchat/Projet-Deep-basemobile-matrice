/*
 * WS2812B.h
 *
 *  Created on: 3 mai 2016
 *      Author: Nirgal
 */

#ifndef BSP_MATRIXLED_WS2812B_H_
#define BSP_MATRIXLED_WS2812B_H_

#include "config.h"

#if USE_MATRIX_LED
#if !(defined LED_MATRIX_PORT_DATA) || !defined(LED_MATRIX_PIN_DATA)
	#define LED_MATRIX_PORT_DATA	GPIOB
	#define LED_MATRIX_PIN_DATA		GPIO_PIN_13
#endif

#define COLOR_BLUE	0x0000FF
#define COLOR_RED	0x00FF00
#define COLOR_GREEN	0xFF0000
#define COLOR_BLACK	0x000000

#define MATRIX_SIZE 256
#define MATRIX_LINE_NUMBER 16
#define MATRIX_LINE_SIZE 8

void LED_MATRIX_init(void);

void LED_MATRIX_demo(void);

//@pre pixels est un tableau de 64 cases maximum... (size est le nombre de cases)
void LED_MATRIX_display(uint32_t * pixels, uint16_t size);


void LED_MATRIX_display_only_one_pixel(uint32_t pixel, uint8_t rank, uint16_t size);
void LED_MATRIX_display_full(uint32_t pixel, uint16_t size);
void LED_MATRIX_send_pixel(uint32_t pixel);
void LED_MATRIX_reset(void);

void LED_MATRIX_Test_XM(uint8_t offset);
void LED_MATRIX_CHIFFRE_XM(uint16_t * font_tab, uint8_t caract, uint32_t color);

#endif
#endif /* BSP_MATRIXLED_WS2812B_H_ */
