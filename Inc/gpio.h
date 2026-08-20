/*
 * PA4 - USART2_CK
 *
 * USART registers:
 * 	Status      - USART_SR
 * 	Data        - USART_DR
 * 	Baud rate   - USART_BRR
 * 	Control 1   - USART_CR1 : has the TX, RX etc bits to set
 * 
 * TXE: [Transmit data register empty]: 
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "stm32f407xx.h"

#define GPIO_PA2                2  // For TX
#define GPIO_PA3                3  // For RX
#define GPIOA_MODER_ALT         ((1U << (2U * GPIO_PA2 + 1U)) | \
                                (1U << (2U * GPIO_PA3 + 1U)))

#define GPIOA_MODER_CLEAR       ((3U << (2U * GPIO_PA2)) | \
                                (3U << (2U * GPIO_PA3)))

#define GPIOA_SPEED             ((3U << (2U * GPIO_PA2)) | \
                                (3U << (2U * GPIO_PA3)))

#define LED_GREEN    		    12 	// GREEN
#define LED_ORANGE   		    13	// ORANGE
#define LED_RED    		        14	// RED
#define LED_BLUE			    15  // BLUE

// GPIOD LED PINS
#define GPIOD_MODER_LED         ((1U << (2U * LED_BLUE)) | \
                                (1U << (2U * LED_GREEN)) | \
                                (1U << (2U * LED_ORANGE)) | \
                                (1U << (2U * LED_RED)))

#define GPIOD_MODER_CLEAR       ((3U << (2U * LED_BLUE)) | \
                                (3U << (2U * LED_GREEN)) | \
                                (3U << (2U * LED_ORANGE)) | \
                                (3U << (2U * LED_RED)))

// Set both GPIOA and GPIOD
void gpio_init();
int __io_putchar(int ch);

#endif