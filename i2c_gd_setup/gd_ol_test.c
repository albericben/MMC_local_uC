//#############################################################################
//
// FILE:   GATE_TST.c
//
// TITLE:  Gate driver signal testing for PCB with open-loop control
//
//!
//! This program runs I2CB module as controller to communicate with 1ED3830MU12M gate driver
//! configuration This program uses polling (not FIFO interrupts)
//!
//! \b External \b Connections on launchpad should be made as shown below \n
//!  --------------------------------
//!    Signal   |  I2CA   |  I2CB
//!  --------------------------------
//!     SCL     | DEVICE_GPIO_PIN_SCLA   |  DEVICE_GPIO_PIN_SCLB
//!     SDA     | DEVICE_GPIO_PIN_SDAA   |  DEVICE_GPIO_PIN_SDAB
//!  --------------------------------
//!
//! \b Watch \b Variables in memory window\n
//!  - \b I2CA_TXdata
//!  - \b I2CA_RXdata
//!  - \b I2CB_TXdata
//!  - \b I2CB_RXdata
//!    stream for error checking
//!
//#############################################################################
//
// Included Files
//
#include "device/driverlib.h"
#include "device.h"

//
// Global Definitions
//
#define ENA_PIN     32
#define ENB_PIN     6
#define SIGA_PIN    7
#define SIGB_PIN    5
#define RDY_PIN     24
#define FLTN_PIN    4

//
// Main
//
void main(void)
{
    uint32_t flt_val;
    uint8_t fault_count;
    unsigned long count = 0;

    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    SysCtl_delay(1000000); //Adding delay to correctly register commands in Gate Driver

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver

    GPIO_setPadConfig(SIGA_PIN, GPIO_PIN_TYPE_STD);    // Enable standard output on Signal A Pin (7)
    GPIO_setPinConfig(GPIO_7_GPIO7);
    GPIO_setDirectionMode(SIGA_PIN, GPIO_DIR_MODE_OUT);

    GPIO_setPadConfig(SIGB_PIN, GPIO_PIN_TYPE_STD);    // Enable standard output on Signal B Pin (5)
    GPIO_setPinConfig(GPIO_5_GPIO5);
    GPIO_setDirectionMode(SIGB_PIN, GPIO_DIR_MODE_OUT);

    GPIO_setPadConfig(ENA_PIN, GPIO_PIN_TYPE_STD);    // Enable enable A pin as output (32)
    GPIO_setPinConfig(GPIO_32_GPIO32);
    GPIO_setDirectionMode(ENA_PIN, GPIO_DIR_MODE_OUT);

    GPIO_setPadConfig(ENB_PIN, GPIO_PIN_TYPE_STD);    // Enable enable B pin as output (6)
    GPIO_setPinConfig(GPIO_6_GPIO6);
    GPIO_setDirectionMode(ENB_PIN, GPIO_DIR_MODE_OUT);

    GPIO_setPadConfig(RDY_PIN, GPIO_PIN_TYPE_OD);    // Enable open drain on RDY Pin (24)
    GPIO_setPinConfig(GPIO_24_GPIO24);
    GPIO_setDirectionMode(RDY_PIN, GPIO_DIR_MODE_OUT);

    GPIO_setPadConfig(FLTN_PIN, GPIO_PIN_TYPE_PULLUP);    // Enable standard output on fault Pin (4)
    GPIO_setPinConfig(GPIO_4_GPIO4);
    GPIO_setDirectionMode(FLTN_PIN, GPIO_DIR_MODE_IN);

    GPIO_writePin(SIGA_PIN, 1);         // Signal 1 Pin ON
    GPIO_writePin(SIGB_PIN, 1);         // Signal 2 Pin OFF
    GPIO_writePin(RDY_PIN, 1);         // Signal 2 Pin OFF

    SysCtl_delay(1000000); //Adding delay to correctly register commands in Gate Driver

    // GD_TST();    // Setup up to 4 Gate drivers
    GPIO_writePin(ENA_PIN, 0);         // Enable 1 Pin OFF
    GPIO_writePin(ENB_PIN, 0);         // Enable 2 Pin OFF
    GPIO_writePin(SIGA_PIN, 1);         // Signal 1 Pin ON
    GPIO_writePin(SIGB_PIN, 0);         // Signal 2 Pin OFF

    SysCtl_delay(1000000); //Adding delay to correctly register commands in Gate Driver

    while(1)
        {
            // Enable gate driver oscillation
            GPIO_writePin(RDY_PIN, 1);
            GPIO_writePin(ENA_PIN, 1);         // Enable 1 Pin ON
            GPIO_writePin(ENB_PIN, 1);         // Enable 2 Pin ON

            // Toggle Signals
            count = 0;
            while (1)
            {
                flt_val = GPIO_readPin(FLTN_PIN);

                if (flt_val == 0)
                {
                    flt_val = 0;
                    break;
                }
                else if (count == 100000)
                {
                    GPIO_togglePin(SIGA_PIN);   // Signal 1 Pin toggle
                    GPIO_togglePin(SIGB_PIN);   // Signal 2 Pin toggle
                    count = 0;
                }
                count++;
            }

            // Disable gate drivers after FLT failure
            GPIO_writePin(ENA_PIN, 0);         // Enable 1 Pin OFF
            GPIO_writePin(ENB_PIN, 0);         // Enable 2 Pin OFF
            GPIO_writePin(RDY_PIN, 0);

            fault_count = 0;
            while (1)
            {
                if (count == 10000)
                {
                    GPIO_togglePin(SIGA_PIN);   // Signal 1 Pin toggle
                    GPIO_togglePin(SIGB_PIN);   // Signal 2 Pin toggle
                    count = 0;
                    fault_count++;
                }

                if (fault_count >= 20)
                {
                    GPIO_writePin(SIGA_PIN, 1);   // Signal 1 Pin toggle
                    GPIO_writePin(SIGB_PIN, 1);   // Signal 2 Pin toggle
                    break;
                }
                count++;
            }

            // Delay for RYDC power cycle to reset gate driver
            SysCtl_delay(1000);

            GPIO_writePin(RDY_PIN, 1);
        }
}

//
// pass condition
//
void
pass(void)
{
    asm("   ESTOP0");
    for(;;);
}

//
// fail condition
//
void fail(void)
{
    asm("   ESTOP0");
    for(;;);
}

//
// End of File
//


