#include "stm32f3xx.h"

int i;

void gpioSet(void);

void ledToggle(void);
void myDelay(void);

int main()
{
    // we need to turn on the clock on specifig periferial register
    gpioSet();



    while(1)
    {
        ledToggle();
        myDelay();

    }
    return 0;


}


void gpioSet(void)
{
    // output on pin PC6 (FT-5v tolerant)
    
    RCC -> AHBENR |= RCC_AHBENR_GPIOCEN; // enable AHBENR per. where PC6 located
    __IO uint32_t tmpreg = RCC -> AHBENR & (~RCC_AHBENR_GPIOCEN);
    (void)tmpreg;
    GPIOC -> MODER |= GPIO_MODER_MODER6_0; // gen.purp output mode 01

}

void ledToggle(void)
{
    GPIOC -> ODR ^= GPIO_ODR_6;
}

void myDelay(void)
{
    for(i = 0; i<200000; i++)
    {

    }
}