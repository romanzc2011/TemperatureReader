#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uart.h"
#include "stm32f407xx.h"

char tx_buffer[BUFFER_SIZE];
volatile size_t tx_len;
volatile uint32_t tx_index;

/*
    TX logic with interrupts:
    1. Data shows up, get the length and a counter to keep up with index
    2. TXE is checked and if TRUE->send first byte
    3. Also enable the TXEIE
    4. After data is sent, TXE is empty,
    5. once 
*/

// --------------------------------------------------
// USART2 INIT
// --------------------------------------------------
void usart2_init(uint32_t baud, uint32_t pCLK)
{
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    USART2->CR1 |= USART_UE;
    USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);
    USART2->CR1 &= ~USART_M;
    set_uart_baudrate(USART2, pCLK, baud);

    USART2->CR1 |= USART_CR1_RXNEIE;

    NVIC_SetPriority(USART2_IRQn, 0);
    NVIC_EnableIRQ(USART2_IRQn);
}

// --------------------------------------------------
// COMPUTE BAUD RATE
// --------------------------------------------------
static uint16_t compute_uart_bdrate(uint32_t baud, uint32_t pCLK)
{
    return ((pCLK + (baud / 2U)) / baud);
}

// --------------------------------------------------
// SET USART BAUD RATE
// -------------------------------------------------- 
static void set_uart_baudrate(USART_TypeDef *USARTx, uint32_t baud, uint32_t pCLK)
{
    USARTx->BRR = compute_uart_bdrate(baud, pCLK);
}

// --------------------------------------------------
// USART2 TX
// --------------------------------------------------
void usart2_tx(char *tx_data)
{
    size_t len = strlen(tx_data);
    if (len > BUFFER_SIZE) {
        len = BUFFER_SIZE; // truncate to avoid overflowing tx_buffer
    }

    // Wait for any in-flight transmission to finish before reusing the shared buffer
    while (tx_index < tx_len) { }

    memcpy(tx_buffer, tx_data, len);
    tx_len = len;
    tx_index = 0;

    USART2->CR1 |= USART_CR1_TXEIE;
}

// --------------------------------------------------
// USART2 READ
// -------------------------------------------------- 
int usart2_read()
{
    USART2->CR1 &= ~USART_CR1_TXEIE;
}

void USART2_IRQHandler(void)
{
    if ((USART2->CR1 & USART_CR1_RXNEIE) && (USART2->SR & USART_SR_RXNE)) {
        (void)USART2->DR; // read to clear RXNE; RX handling not implemented yet
    }

    if ((USART2->CR1 & USART_CR1_TXEIE) && (USART2->SR & USART_SR_TXE)) {
        if (tx_index < tx_len) {
            USART2->DR = tx_buffer[tx_index];
            tx_index++;
        }
        else {
            USART2->CR1 &= ~USART_CR1_TXEIE;
        }
    }
}
