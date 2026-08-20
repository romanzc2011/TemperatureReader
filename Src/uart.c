#include "uart.h"
#include "stm32f407xx.h"

// --------------------------------------------------
// USART2 INIT
// --------------------------------------------------
void usart2_init(uint32_t baud, uint32_t pCLK)
{
    RCC->APB1ENR |= USART2ENR;
    USART2->CR1 |= USART_UE;
    USART2->CR1 |= USART_CR1_TE;
    USART2->CR1 |= USART_CR1_RE;
    USART2->CR1 &= ~USART_M;
    set_uart_baudrate(USART2, baud, pCLK);
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
// --------------------------------------------------
void usart2_write(int ch)
{
    // Check if TX is empty first, then send data
    if (USART2->SR & USART_SR_TXE) {

    }
}

// --------------------------------------------------
// USART2 READ
// -------------------------------------------------- 
int usart2_read()
{

}

void USART2_IRQHandler()
{
    while(USART2->SR == USART_SR_TXE) {

    }
}
