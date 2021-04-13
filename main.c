

/**
 * main.c
 */
#include <include.h>

void Timer(void);
void Timer0IntHandler(void);

int main(void)
{
    SysCtlClockSet( SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN );
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_3);
    Timer();


    while (1)
    {
        //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
        //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);

    }

}

void Timer(void)
{
    // Cai dat gpio:timer, timer mode.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    // tinh toan tao tre
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()/3);

    // cho phep ngat
    IntEnable(INT_TIMER0A); // chon ngat timer
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT); //
    IntMasterEnable(); // cho phep ngat toan bo

    TimerEnable(TIMER0_BASE, TIMER_A); // cho phep tao timer

    TimerIntRegister(TIMER0_BASE, TIMER_A, &Timer0IntHandler);

}
void Timer0IntHandler(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2))
        {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
        }
    else
        {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 2);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 8);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4);
        }
}
