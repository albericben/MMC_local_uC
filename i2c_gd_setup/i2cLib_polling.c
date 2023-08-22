//#############################################################################
//
// FILE:   i2cLib_FIFO_controller_target_interrupt.c
//
// TITLE:  C28x-I2C Library source file for FIFO interrupts
//! <h1> C28x-I2C Library source file for FIFO interrupts </h1>
//
//#############################################################################

#include "driverlib.h"
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
