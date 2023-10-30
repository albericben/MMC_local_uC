//#############################################################################
//
// FILE:   i2cLib_FIFO_controller_target_interrupt.c
//
// TITLE:  C28x-I2C Library source file for FIFO interrupts
//! <h1> C28x-I2C Library source file for FIFO interrupts </h1>
//
//#############################################################################

#include "device/driverlib.h"
#include "device.h"
#include "i2cLib_polling.h"

#define MAX_7_BIT_ADDRESS 127U

uint16_t count = 0;

uint16_t I2C_TransmitTargetAddress_ControlBytes(struct I2CHandle *I2C_Params)
{
    uint16_t status;

    uint32_t base = I2C_Params->base;

    status = checkBusStatus(base);
    if(status)
    {
        return status;
    }

    I2C_disableFIFO(base);

    I2C_setConfig(base, (I2C_CONTROLLER_SEND_MODE));

    if((I2C_Params->TargetAddr) > MAX_7_BIT_ADDRESS)
    {
        //10-bit addressing
        I2C_setAddressMode(base, I2C_ADDR_MODE_10BITS);
    }

    // Setup target address
    I2C_setTargetAddress(base, I2C_Params->TargetAddr);

    I2C_setDataCount(base, (I2C_Params->NumOfAddrBytes));

    I2C_enableFIFO(base);

    int16_t i;

    for(i=0;i<=I2C_Params->NumOfAddrBytes-1;i++)
    {
//        if (count < 5) {
            uint16_t local = *(I2C_Params->pTX_MsgBuffer+i);
            I2C_putData(base, local);
//        }
    }

//    count++;

    I2C_sendStartCondition(base);

    return SUCCESS;
}

uint16_t I2C_ControllerTransmitter(struct I2CHandle *I2C_Params)
{
    uint16_t status;

    uint32_t base = I2C_Params->base;

    status = I2C_TransmitTargetAddress_ControlBytes(I2C_Params);

    if(status)
    {
        return status;
    }

    I2C_sendStopCondition(base);

    return SUCCESS;
}

uint16_t I2C_ControllerReceiver(struct I2CHandle *I2C_Params, uint16_t *dataOut)
{
    uint16_t status;
    uint32_t base = I2C_Params->base;
    uint16_t count1 = 0;

    status = I2C_TransmitTargetAddress_ControlBytes(I2C_Params);

    I2C_disableFIFO(base);

    I2C_setDataCount(base, 11);
    I2C_setConfig(base, (I2C_CONTROLLER_RECEIVE_MODE));

    for (count1 = 0; count1 < 11; count1++)
    {
        while(!(I2C_getStatus(base) & I2C_STS_RX_DATA_RDY));
        dataOut[count1] = I2C_getData(base);
    }

    I2C_sendStopCondition(base);

    if(status)
    {
        return status;
    }

    return SUCCESS;
}


uint16_t checkBusStatus(uint32_t base)
{

    if(I2C_isBusBusy(base))
    {
        return ERROR_BUS_BUSY;
    }

    if(I2C_getStopConditionStatus(base))
    {
        return ERROR_STOP_NOT_READY;
    }

    return SUCCESS;
}

// Original Version
//void I2C_GD_Setup(uint8_t devicesConfig)
//{
//    I2CB.base               = I2CB_BASE;
//    uint8_t i;
//
//    for (i = 0; i < devicesConfig; i++)
//    {
//        SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver
//
//        I2CB.TargetAddr         = I2CB_ADDRESS;
//        I2CB.NumOfAddrBytes     = 4;
//
//        if (i == 0)
//        {
//            I2CB.pTX_MsgBuffer      = &add1Data[0];
//
//            GPIO_writePin(ENA_PIN, 1);         // Enable 1 Pin ON
//            GPIO_writePin(ENB_PIN, 0);         // Enable 2 Pin OFF
//            GPIO_writePin(SIGA_PIN, 1);         // Signal 1 Pin ON
//            GPIO_writePin(RDY_PIN, 0);
//
//            SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver
//
//            status = I2C_ControllerTransmitter(&I2CB);
//
//            // Wait for I2CB to be complete transmission of data
//            while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);
//            SysCtl_delay(100); //Adding delay to correctly register commands in Gate Driver
//
//            I2CB.TargetAddr         = I2CB_ADDRESS_D1;
//        }
//        else if (i == 1)
//        {
//            I2CB.pTX_MsgBuffer      = &add2Data[0];
//
//            GPIO_writePin(ENA_PIN, 1);         // Enable 1 Pin ON
//            GPIO_writePin(ENB_PIN, 0);         // Enable 2 Pin OFF
//            GPIO_writePin(SIGA_PIN, 0);         // Signal 1 Pin OFF
//            GPIO_writePin(RDY_PIN, 0);
//
//            SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver
//
//            status = I2C_ControllerTransmitter(&I2CB);
//
//            // Wait for I2CB to be complete transmission of data
//            while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);
//            SysCtl_delay(100); //Adding delay to correctly register commands in Gate Driver
//
//            I2CB.TargetAddr         = I2CB_ADDRESS_D2;
//        }
//        else if (i == 2)
//        {
//            I2CB.pTX_MsgBuffer      = &add3Data[0];
//
//            GPIO_writePin(ENA_PIN, 0);         // Enable 1 Pin OFF
//            GPIO_writePin(ENB_PIN, 1);         // Enable 2 Pin ON
//            GPIO_writePin(SIGB_PIN, 1);         // Signal 2 Pin ON
//            GPIO_writePin(RDY_PIN, 0);
//
//            SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver
//
//            status = I2C_ControllerTransmitter(&I2CB);
//
//            // Wait for I2CB to be complete transmission of data
//            while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);
//            SysCtl_delay(100); //Adding delay to correctly register commands in Gate Driver
//
//            I2CB.TargetAddr         = I2CB_ADDRESS_D3;
//        }
//        else
//        {
//            I2CB.pTX_MsgBuffer      = &add4Data[0];
//
//            GPIO_writePin(ENA_PIN, 0);         // Enable 1 Pin OFF
//            GPIO_writePin(ENB_PIN, 1);         // Enable 2 Pin ON
//            GPIO_writePin(SIGB_PIN, 0);         // Signal 2 Pin OFF
//            GPIO_writePin(RDY_PIN, 0);
//
//            SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver
//
//            status = I2C_ControllerTransmitter(&I2CB);
//
//            // Wait for I2CB to be complete transmission of data
//            while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);
//            SysCtl_delay(100); //Adding delay to correctly register commands in Gate Driver
//
//            I2CB.TargetAddr         = I2CB_ADDRESS_D4;
//        }
//
//        GPIO_writePin(ENA_PIN, 0);
//        GPIO_writePin(ENB_PIN, 0);
//        GPIO_writePin(RDY_PIN, 0);          // low impedance
//
////        SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver
//
//        I2CB.NumOfAddrBytes     = 6;
//        I2CB.pTX_MsgBuffer      = &gateData[0];
//
////        SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver
//
//        status = I2C_ControllerTransmitter(&I2CB);
//
//        // Wait for I2CB to be complete transmission of data
//        while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);
//        SysCtl_delay(100); //Adding delay to correctly register commands in Gate Driver
//
//        I2CB.NumOfAddrBytes     = 3;
//        I2CB.pTX_MsgBuffer      = &safetestData[0];
//
//        SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver
//
//        status = I2C_ControllerTransmitter(&I2CB);
//
//        // Wait for I2CB to be complete transmission of data
//        while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);
//        SysCtl_delay(100); //Adding delay to correctly register commands in Gate Driver
//
//        I2CB.NumOfAddrBytes     = 2;
//        I2CB.pTX_MsgBuffer      = &desatimeData[0];
//
//        SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver
//
//        status = I2C_ControllerTransmitter(&I2CB);
//
//        // Wait for I2CB to be complete transmission of data
//        while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);
//        SysCtl_delay(100); //Adding delay to correctly register commands in Gate Driver
//
//
//        I2CB.NumOfAddrBytes     = 4;
//        I2CB.pTX_MsgBuffer      = &setOKData[0];
//
//        SysCtl_delay(1000); //Adding delay to correctly register commands in Gate Driver
//
//        status = I2C_ControllerTransmitter(&I2CB);
//
//        // Wait for I2CB to be complete transmission of data
//        while(I2C_getStatus(I2CB.base) & I2C_STS_BUS_BUSY);
//        SysCtl_delay(100); //Adding delay to correctly register commands in Gate Driver
//    }
//
////    GPIO_writePin(RDY_PIN, 1);          // high impedance
////
////    SysCtl_delay(10000); //Adding delay to correctly register commands in Gate Driver
////
////    GPIO_writePin(RDY_PIN, 0);          // low impedance
//
////    SysCtl_delay(10000); //Adding delay to correctly register commands in Gate Driver
//
//    GPIO_writePin(ENA_PIN, 1);
//    GPIO_writePin(ENB_PIN, 1);
//    GPIO_writePin(RDY_PIN, 1);          // high impedance
//
//}
