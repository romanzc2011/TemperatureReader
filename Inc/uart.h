#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "stm32f407xx.h"

#define USART2ENR         (1UL << 17)
#define SYS_FREQ          16000000UL
#define APB1_CLK          SYS_FREQ
#define USART_UE          (1UL << 13)
#define USART_M           (1UL << 12)
#define BAUD_RATE         9600

void usart2_init(uint32_t baud, uint32_t pCLK);
static void set_uart_baudrate(USART_TypeDef *USARTx, uint32_t pCLK, uint32_t baud);
static uint16_t compute_uart_bdrate(uint32_t baud, uint32_t pCLK);
void usart2_write(int ch);
int usart2_read();

#endif