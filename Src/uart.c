#include <stdio.h>
#include "uart.h"
#include "stm32f407xx.h"

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
    set_uart_baudrate(USART2, baud, pCLK);

    USART2->CR1 |= USART_CR1_RXNEIE;
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
static void set_uart_baudrate(USART_TypeDef *USARTx, uint32_t pCLK, uint32_t baud)
{
    USARTx->BRR = compute_uart_bdrate(baud, pCLK);
}

// --------------------------------------------------
// USART2 WRITE
// ------------------------------- x-------------------
void usart2_write(void)
{
    // Check if TX is empty first, then send data
    if (USART2->SR & USART_SR_TXE) {
        USART2->CR1 |= USART_CR1_TXEIE;

        // Set the IRQ Handler to highest priority
        NVIC_SetPriority(USART2_IRQn, 0);
        NVIC_EnableIRQ(USART2_IRQn);
    }
}

// --------------------------------------------------
// USART2 CALLBACK
// -------------------------------------------------- 
void usart2_callback(USART_TypeDef *USARTx, uint32_t index, char *buffer)
{
    USART2->DR = buffer[index];
    index++;
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
    if (USART2->SR & USART_SR_TXE) {
        usart2_callback(USART2, tx_index, tx_buffer);
    }
    else {
        USART2->CR1 &= ~USART_CR1_TXEIE;
    }
}
