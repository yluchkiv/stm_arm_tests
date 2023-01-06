#include "stm32f3xx.h"
#include "pwm.h"

int i;

void gpioSet(void);
void buttonPin(void);
void ledToggle(void);
void myDelay(void);
void ledBright(void);
void ledDark(void);

int main()
{
    // we need to turn on the clock on specifig periferial register
    gpioSet();
    buttonPin();

    rcc_setup();
    pwm_ch_setup();
    timer_setup();

    while(1)
    {
       
       
       


        if(GPIOC -> IDR & GPIO_IDR_9) //GPIO_IDR_9 = 0x00000200U // NOT PRESSED
        {
            ledDark();
        }
        else if (!(GPIOC -> IDR & GPIO_IDR_9))   // PRESSED
        {

            //ledToggle();
            //myDelay();
            ledBright();

        }
        else // ERROR
        {

        }

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

void buttonPin(void)
{
    // PC9 as an input button, pull-up tha will be grounded by external button
    // no need to start RCC for AHBENR as it is already strated
    // begin with MODER = 00 for Input
    GPIOC -> PUPDR |= GPIO_PUPDR_PUPDR9_0; // pull -up mode
    //GPIOC -> PUPDR |= GPIO_PUPDR_PUPDR9_1; // pull -down mode
}
void ledBright(void)
{
    GPIOC -> ODR |= GPIO_ODR_6;
}

void ledDark(void)
{
    GPIOC -> ODR = ~GPIO_ODR_6; // bad solution
}