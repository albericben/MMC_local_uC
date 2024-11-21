//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"


volatile uint16_t errorFlag = 0;
volatile uint16_t intCount = 0;

__interrupt void adcA1ISR(void);
__interrupt void gbl_flt_ISR(void);
__interrupt void fanctrlISR(void);

//
// Main
//
void main(void)
{
    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();

    // Disable sync(Freeze clock to PWM as well)
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    Board_init();

    // Enable sync and clock to PWM
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    GPIO_writePin(ENA_out, 1);

    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    EINT;
    ERTM;

    // IDLE loop. Just sit and loop forever (optional):
    for(;;)
    {

        if(errorFlag)
        {
            GPIO_writePin(ENA_out, 0);
            GPIO_writePin(SIGA_out, 0);
            asm("   ESTOP0");
        }
    }
}

//
// cpuTimer0ISR - Counter for CpuTimer0
//
__interrupt void fanctrlISR(void)
{
    if (intCount == 10000)
    {
        intCount = 0;
        GPIO_writePin(SIGA_out, 1);
    }
    else
    {
        intCount++;
        GPIO_writePin(SIGA_out, 0);
    }
    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

__interrupt void gbl_flt_ISR(void)
{
    // Write code to handle fault - STOP ALL GATE signaling
    GPIO_writePin(ENA_out, 0);
    GPIO_writePin(SIGA_out, 0);

    // Acknowledge the interrupt
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
