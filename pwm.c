#include "pwm.h"
#include "stm32f3xx.h"

void rcc_setup(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOCEN;  //  enable GPIOC -> PC8   AF -> TIM3_ch3

    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // enable TIM3 (16-bit timer)

}  

void pwm_ch_setup(void)
{
    GPIOC->MODER |= GPIO_MODER_MODER8_1; // PC8-> Alternative Function
    const uint32_t AF2 = 2U; //0010
    const uint32_t AFR8 = 0U; // 0-bit
    GPIOC->AFR[1] |= (AF2 << AFR8); // shifting in AFR High  // AF2 as alternative for GPIOC PC8
    GPIOC->OTYPER &= ~GPIO_OTYPER_OT_8;  // AF-> push pull  

}

void timer_setup(void)
{
    
    //TIM3->CCER |= TIM_CCER_CC3P; //CC3 channel configured as output: 1: OC3 active low
    //TIM3->CCMR1 &= ~(TIM_CCMR1_OC1M_0|TIM_CCMR1_OC1M_3); // reset all bits in OC1M

    //0110: PWM mode 1 - In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive.
    TIM3->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3PE; // + preload enable
    TIM3->CCER |= TIM_CCER_CC3E; //Capture/Compare  output enable chanel 3

    TIM3->PSC = 7200;
    TIM3->ARR = 10000;
    TIM3->CCR3 = 5000; //duty cycle 10%

    TIM3->EGR |= TIM_EGR_UG;          //Update generation
    TIM3->CR1 |= TIM_CR1_CEN;         //counter enable

}


