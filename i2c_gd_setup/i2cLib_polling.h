//#############################################################################
//
// FILE:   i2cLib_FIFO_controller_target_interrupt.h
//
// TITLE:  C28x-I2C Library header file for FIFO interrupts
//
//#############################################################################

#ifndef I2CLIB_FIFO_POLL_H
#define I2CLIB_FIFO_POLL_H

#include "device.h"

//
// Error messages for read and write functions
//
#define ERROR_BUS_BUSY              0x1000
#define ERROR_NACK_RECEIVED         0x2000
#define ERROR_ARBITRATION_LOST      0x3000
#define ERROR_STOP_NOT_READY        0x5555
#define SUCCESS                     0x0000

#define MAX_BUFFER_SIZE             64
#define I2C_FIFO_LEVEL              16

#define MAX_7_BIT_ADDRESS 127U
#define MAX_10_BIT_ADDRESS 1023U

#define MAX_I2C_IN_NETWORK 20


//
// Typedefs
//
struct I2CHandle
{
    uint32_t base;
    uint16_t TargetAddr;                  // target address tied to the message.
//    uint32_t *pControlAddr;
    uint16_t NumOfAddrBytes;
    uint16_t *pTX_MsgBuffer;             // Pointer to TX message buffer
//    uint16_t *pRX_MsgBuffer;             // Pointer to RX message buffer
//    uint16_t NumOfDataBytes;             // Number of valid bytes in message.
//    struct I2CHandle *currentHandlePtr;

//    uint16_t numofSixteenByte;
//    uint16_t remainingBytes;
};

uint16_t I2C_TransmitTargetAddress_ControlBytes(struct I2CHandle *I2C_Params);

uint16_t I2C_ControllerTransmitter(struct I2CHandle *I2C_Params);
uint16_t I2C_ControllerReceiver(struct I2CHandle *I2C_Params, uint16_t *dataOut);

static uint16_t add1Data[4]         = {0x00, 0x1A, 0x20, 0x01};
static uint16_t add2Data[4]         = {0x00, 0x1B, 0x20, 0x01};
static uint16_t add3Data[4]         = {0x00, 0x1C, 0x20, 0x01};
static uint16_t add4Data[4]         = {0x00, 0x1D, 0x20, 0x01};
static uint16_t gateData[6]        = {0x05, 0x00, 0x05, 0x00, 0x00, 0x0C};
static uint16_t safetestData[3]    = {0x0B, 0x0F, 0x20};   // Desat 1 off
static uint16_t safeimpData[3]     = {0x0B, 0x0F, 0x00};   // Desat 1 on
static uint16_t desatimeData[2]    = {0x12, 0x01};
static uint16_t setOKData[4]       = {0x1A, 0x22, 0x0C, 0x01};
static uint16_t statusData[1]      = {0x26};

uint16_t checkBusStatus(uint32_t base);

extern uint16_t status;

extern struct I2CHandle *currentTargetPtr;

#endif


