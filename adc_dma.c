#include "stm32f3xx.h"
#include "adc_dma.h"

void gpio_setup(void) //pin PA0
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // ABH enabling and GPIO A enabling
    __IO uint32_t tmpreg = RCC->AHBENR & (~RCC_AHBENR_GPIOAEN); //
    (void)tmpreg;
    GPIOA->MODER |= GPIO_MODER_MODER0; // 11: Analog mode - for ADC1
}



void adc_setup(void) // ADC1 and 2 
{
    // ADC 12 enabled in RCC main.c
    
    ADC12_COMMON->CCR |= ADC12_CCR_CKMODE_0; // 0b01 // Set ADC clock
    ADC1->CFGR |= ADC_CFGR_CONT; // continuous mode
    ADC1->CFGR |= ADC_CFGR_DMAEN; // DMA enable
    ADC1->CR |= ADC_CR_ADCAL; // start ADC calibration cycle
    
    while (ADC1->CR & ADC_CR_ADCAL); // wait for calibration to complete
    
    ADC1->CR |= ADC_CR_ADEN; // enable the ADC.
    while (!(ADC1->ISR & ADC_ISR_ADRDY)); // check if enabled

    // Select ADC Channels
    ADC1->SQR1 |= ADC_SQR1_SQ1_1; //(1 << 6); CHECK!

    // Set sampling time for regular group 1
    ADC1->SMPR1 |= (0b000 << 3); // 0b000 -> 1.5 clock cycles, shortest available sampling time

    // Regular sequence settings
    ADC1->SQR1 |= (0b0000 << 0); // One conversion in the regular sequence

    ADC12_COMMON->CCR |= ADC_CCR_DUAL_1 | ADC_CCR_DUAL_2; //00110: Regular simultaneous mode only
  


    // DMA mode
    ADC12_COMMON->CCR |= (0 << 13); // 0 -> One Shot; 1 -> Circular  ADC_CCR_DMACFG


    // DMA mode for 12-bit resolution
    ADC12_COMMON->CCR |= ADC_CCR_MDMA_1; // (0b10 << 14); CHEcK!

    ADC1->CR |= ADC_CR_ADSTART; //start conversion

    ADC1->CR |= ADC_CR_ADSTART; //start conversion

    ADC1->CR |= ADC_CR_ADSTART; //start conversion
    ADC1->CR |= ADC_CR_ADSTART; //start conversion
    ADC1->CR |= ADC_CR_ADSTART; //start conversion
    ADC1->CR |= ADC_CR_ADSTART; //start conversion
    ADC1->CR |= ADC_CR_ADSTART; //start conversion
  


}

void dma_setup(void) // DAM1
{
    // DMA1 enabled in RCC main.c

}

