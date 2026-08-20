#include "gpio.h"
#include "stm32f407xx.h"

void gpio_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    
    // GPIOA SET
    GPIOA->MODER |= GPIOA_MODER_ALT;
    GPIOA->OSPEEDR |= GPIOA_SPEED;

    // GPIOD SET
    GPIOD->MODER &= ~GPIOD_MODER_CLEAR;
    GPIOD->MODER |= GPIOD_MODER_LED;

    // Config the ALT functions for TX and RX
    GPIOA->AFR[0] &= ~(0xF << (4 * GPIO_PA2));
    GPIOA->AFR[0] |= (0x7 << (4 * GPIO_PA2));

    GPIOA->AFR[0] &= ~(0xF << (4 * GPIO_PA3));
    GPIOA->AFR[0] |= (0x7 << (4 * GPIO_PA3));
}