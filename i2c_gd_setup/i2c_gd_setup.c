//#############################################################################
//
// FILE:   i2c_gd_setup.c
//
// TITLE:  I2C controller communication with gate driver using polling
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

#include "i2cLib_polling.h"

//
// Defines
//
#define I2CB_ADDRESS      0x0D
#define I2CB_ADDRESS_D1   0x1A
#define I2CB_ADDRESS_D2   0x1B
#define I2CB_ADDRESS_D3   0x1C
#define I2CB_ADDRESS_D4   0x1D
#define I2CB_ADDRESS_GRP  0x20

#define ENA_PIN     32
#define ENB_PIN     6
#define SIGA_PIN    7
#define SIGB_PIN    5
#define RDY_PIN     24
#define FLTN_PIN    4

//
// Globals
//
uint16_t status = 0;

struct I2CHandle I2CB;

//
// Function Prototypes
//
uint16_t status;

void I2C_GPIO_init(void);
void I2Cinit(void);
void I2C_GD_Setup(uint8_t devicesConfig);
void I2C_Read_Status(uint8_t devicesConfig);
void toggleSignal(void);

uint16_t gds_data[24];
uint16_t *stat_data = gds_data;

//
// Main
//
void main(void)
{
    //
    // Disable pin locks and enable internal pullups.
    //
    Device_initGPIO();

    I2C_GPIO_init();

    //
    // Initialize device clock and peripherals
    //
    Device_init();

    I2Cinit();

    SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver

    I2C_GD_Setup(3);    // Setup up to 4 Gate drivers


//    toggleSignal();
//    Read loop forever
    I2C_Read_Status(1);
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

void I2C_GPIO_init(void)
{
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

    GPIO_setPadConfig(FLTN_PIN, GPIO_PIN_TYPE_OD);    // Enable standard output on fault Pin (4)
    GPIO_setPinConfig(GPIO_4_GPIO4);
    GPIO_setDirectionMode(FLTN_PIN, GPIO_DIR_MODE_OUT);

    GPIO_writePin(RDY_PIN, 0); //
    GPIO_writePin(FLTN_PIN, 1);

    // I2CB pins (SDAB / SCLB)
    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SDAB, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SDAB, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SDAB, GPIO_QUAL_ASYNC);

    GPIO_setDirectionMode(DEVICE_GPIO_PIN_SCLB, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(DEVICE_GPIO_PIN_SCLB, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(DEVICE_GPIO_PIN_SCLB, GPIO_QUAL_ASYNC);

    GPIO_setPinConfig(DEVICE_GPIO_CFG_SDAB);
    GPIO_setPinConfig(DEVICE_GPIO_CFG_SCLB);
}

void I2Cinit(void)
{
    //I2CB initialization
    I2C_disableModule(I2CB_BASE);
    I2C_initController(I2CB_BASE, DEVICE_SYSCLK_FREQ, 20000, I2C_DUTYCYCLE_50);
    I2C_setConfig(I2CB_BASE, I2C_CONTROLLER_SEND_MODE);
    I2C_setTargetAddress(I2CB_BASE, I2CB_ADDRESS);
    I2C_disableLoopback(I2CB_BASE);
    I2C_setBitCount(I2CB_BASE, I2C_BITCOUNT_8);
    I2C_setDataCount(I2CB_BASE, 2);
    I2C_setAddressMode(I2CB_BASE, I2C_ADDR_MODE_7BITS);
    I2C_setEmulationMode(I2CB_BASE, I2C_EMULATION_FREE_RUN);
    I2C_enableModule(I2CB_BASE);
}

void I2C_GD_Setup(uint8_t devicesConfig)
{
    I2CB.base               = I2CB_BASE;
    uint8_t i;

    for (i = 0; i < devicesConfig; i++)
    {
        SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver

        I2CB.TargetAddr         = I2CB_ADDRESS;
        I2CB.NumOfAddrBytes     = 4;

        if (i == 0)
        {
            I2CB.pTX_MsgBuffer      = &add1Data[0];

            GPIO_writePin(ENA_PIN, 1);         // Enable 1 Pin ON
            GPIO_writePin(ENB_PIN, 0);         // Enable 2 Pin OFF
            GPIO_writePin(SIGA_PIN, 1);         // Signal 1 Pin ON
            GPIO_writePin(RDY_PIN, 0);

            SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver

            status = I2C_ControllerTransmitter(&I2CB);

            // Wait for I2CB to be complete transmission of data
            while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);
            SysCtl_delay(100); //Adding delay to correctly register commands in Gate Driver
        }
        else if (i == 1)
        {
            I2CB.pTX_MsgBuffer      = &add2Data[0];

            GPIO_writePin(ENA_PIN, 1);         // Enable 1 Pin ON
            GPIO_writePin(ENB_PIN, 0);         // Enable 2 Pin OFF
            GPIO_writePin(SIGA_PIN, 0);         // Signal 1 Pin OFF
            GPIO_writePin(RDY_PIN, 0);

            SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver

            status = I2C_ControllerTransmitter(&I2CB);

            // Wait for I2CB to be complete transmission of data
            while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);
            SysCtl_delay(100); //Adding delay to correctly register commands in Gate Driver
        }
        else if (i == 2)
        {
            I2CB.pTX_MsgBuffer      = &add3Data[0];

            GPIO_writePin(ENA_PIN, 0);         // Enable 1 Pin OFF
            GPIO_writePin(ENB_PIN, 1);         // Enable 2 Pin ON
            GPIO_writePin(SIGB_PIN, 1);         // Signal 2 Pin ON
            GPIO_writePin(RDY_PIN, 0);

            SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver

            status = I2C_ControllerTransmitter(&I2CB);

            // Wait for I2CB to be complete transmission of data
            while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);
            SysCtl_delay(100); //Adding delay to correctly register commands in Gate Driver
        }
        else
        {
            I2CB.pTX_MsgBuffer      = &add4Data[0];

            GPIO_writePin(ENA_PIN, 0);         // Enable 1 Pin OFF
            GPIO_writePin(ENB_PIN, 1);         // Enable 2 Pin ON
            GPIO_writePin(SIGB_PIN, 0);         // Signal 2 Pin OFF
            GPIO_writePin(RDY_PIN, 0);

            SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver

            status = I2C_ControllerTransmitter(&I2CB);

            // Wait for I2CB to be complete transmission of data
            while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);
            SysCtl_delay(100); //Adding delay to correctly register commands in Gate Driver
        }


    }

    GPIO_writePin(ENA_PIN, 0);
    GPIO_writePin(ENB_PIN, 0);
    GPIO_writePin(RDY_PIN, 0);          // low impedance

    I2CB.TargetAddr         = I2CB_ADDRESS_GRP;
    I2CB.NumOfAddrBytes     = 6;
    I2CB.pTX_MsgBuffer      = &gateData[0];

    SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver

    status = I2C_ControllerTransmitter(&I2CB);

    // Wait for I2CB to be complete transmission of data
    while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);
    SysCtl_delay(100); //Adding delay to correctly register commands in Gate Driver

    I2CB.NumOfAddrBytes     = 3;
    I2CB.pTX_MsgBuffer      = &safetestData[0];

    status = I2C_ControllerTransmitter(&I2CB);

    // Wait for I2CB to be complete transmission of data
    while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);
    SysCtl_delay(100); //Adding delay to correctly register commands in Gate Driver

    I2CB.NumOfAddrBytes     = 2;
    I2CB.pTX_MsgBuffer      = &desatimeData[0];

    SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver

    status = I2C_ControllerTransmitter(&I2CB);

//     Wait for I2CB to be complete transmission of data
    while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);
    SysCtl_delay(100); //Adding delay to correctly register commands in Gate Driver
//
    I2CB.NumOfAddrBytes     = 4;
    I2CB.pTX_MsgBuffer      = &setOKData[0];

    SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver

    status = I2C_ControllerTransmitter(&I2CB);

    // Wait for I2CB to be complete transmission of data
    while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);
    SysCtl_delay(100); //Adding delay to correctly register commands in Gate Driver

    GPIO_writePin(ENA_PIN, 1);
    GPIO_writePin(ENB_PIN, 1);
    GPIO_writePin(RDY_PIN, 1);          // high impedance

}

void toggleSignal(void)
{
    unsigned long count = 0;
    while (1)
    {
        if (count == 100000)
        {
            GPIO_togglePin(SIGA_PIN);         // Signal 1 Pin ON
            count = 0;
        }
        count++;
    }

}

void I2C_Read_Status(uint8_t devicesConfig)
{
    bool toggle = true;
    I2CB.NumOfAddrBytes   = 1;
    I2CB.pTX_MsgBuffer  = &statusData[0];

    while (1) {
        if (toggle)
        {
            I2CB.TargetAddr         = I2CB_ADDRESS_D3;
            toggle = false;
        }
        else
        {
            I2CB.TargetAddr         = I2CB_ADDRESS_D4;
            toggle = true;
        }

        status = I2C_ControllerReceiver(&I2CB, stat_data);
        while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);

        SysCtl_delay(10000);
    }
}

//
// End of File
//


