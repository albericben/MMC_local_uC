//#############################################################################
//
// FILE:   epwm_ex2_updown_aq.c
//
// TITLE:  ePWM Action Qualifier Module - Using up/down count.
//
//! \addtogroup driver_example_list
//! <h1> ePWM Up Down Count Action Qualifier</h1>
//!
//! This example configures ePWM1, ePWM2, ePWM3 to produce a waveform with
//! independent modulation on ePWMxA and ePWMxB.
//!
//! The compare values CMPA and CMPB are modified within the ePWM's ISR.
//!
//! The TB counter is in up/down count mode for this example.
//!
//! View the ePWM1A/B(GPIO0 & GPIO1), ePWM2A/B(GPIO2 &GPIO3)
//! and ePWM3A/B(GPIO4 & GPIO5) waveforms on oscilloscope.
//
//#############################################################################
//
//
// $Copyright:
// Copyright (C) 2023 Texas Instruments Incorporated - http://www.ti.com/
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met:
// 
//   Redistributions of source code must retain the above copyright 
//   notice, this list of conditions and the following disclaimer.
// 
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the 
//   documentation and/or other materials provided with the   
//   distribution.
// 
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
//#############################################################################

//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"

//
// Defines
//
#define EPWM3_TIMER_TBPRD  20000US
#define EPWM3_MAX_CMPB     19000U
#define EPWM3_MIN_CMPB      1000U

#define EPWM_CMP_UP           1U
#define EPWM_CMP_DOWN         0U

#define OVER_TEMP_THRESH   0x07FF
#define TEMP_HYST_THRESH   OVER_TEMP_THRESH-0x00FF

#define FAN_ON_OFF_THRESH  0x07FF

typedef struct
{
    uint32_t epwmModule;
    uint16_t epwmCompADirection;
    uint16_t epwmCompBDirection;
    uint16_t epwmTimerIntCount;
    uint16_t epwmMaxCompA;
    uint16_t epwmMinCompA;
    uint16_t epwmMaxCompB;
    uint16_t epwmMinCompB;
}epwmInformation;

epwmInformation epwm2Info;
epwmInformation epwm3Info;

uint16_t adc_raw_ntc1;   // NTC1 PIN
uint16_t adc_raw_ntc2;   // NTC2 PIN
uint16_t adc_raw_iac1;   // G1_CUR PIN
uint16_t adc_raw_iac2;   // G2_CUR PIN
uint16_t adc_raw_fans;   // FAN_SENS PIN
uint16_t adc_raw_vdc1;   // DC1_LNK PIN
uint16_t adc_raw_vdc2;  // DC2_LNK PIN
uint16_t adc_raw_vac1;  // G1_VLT PIN
uint16_t adc_raw_vac2;  // G2_VLT PIN

void initEPWM();        // ADC Read Trigger
void initEPWM2(void);   // SIG A
void initEPWM3(void);   // SIG B

uint8_t over_temp_thresh = 0;

volatile uint16_t errorFlag = 0;
uint8_t txMsgSuccessful  = 1;
uint16_t txMsgData[4];

__interrupt void adcA1ISR(void);
__interrupt void epwm2ISR(void);
__interrupt void epwm3ISR(void);
__interrupt void gbl_flt_ISR(void);
__interrupt void gbl_enbl_ISR(void);
__interrupt void fanctrlISR(void);
__interrupt void myCAN0_0_ISR(void);
__interrupt void myCAN0_1_ISR(void);

void updateCompare(epwmInformation *epwmInfo);

//
// Main
//
void main(void)
{
    uint8_t tx_can_msg = 0;

    // Initialize device clock and peripherals
    Device_init();

    // Disable pin locks and enable internal pull ups.
    Device_initGPIO();

    // Initialize PIE and clear PIE registers. Disables CPU interrupts.
    Interrupt_initModule();

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    Interrupt_initVectorTable();

    txMsgData[0] = 0x12;
    txMsgData[1] = 0x34;
    txMsgData[2] = 0x56;
    txMsgData[3] = 0x78;

    // Assign the interrupt service routines to ePWM interrupts
    Interrupt_register(INT_EPWM3, &epwm2ISR);
    Interrupt_register(INT_EPWM4, &epwm3ISR);


    // Disable sync(Freeze clock to PWM as well)
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    // Configure GPIO0/1 , GPIO2/3 and GPIO4/5 as ePWM1A/1B, ePWM2A/2B and
    // ePWM3A/3B pins respectively
    // Configure EPWM Modules
    Board_init();

    initEPWM();
    initEPWM2();
    initEPWM3();

    // Enable sync and clock to PWM
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    // Enable ePWM interrupts
    Interrupt_enable(INT_EPWM3);
    Interrupt_enable(INT_EPWM4);

    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    EINT;
    ERTM;

    // Start ePWM7, enabling SOCB and putting the counter in up-count mode
    EPWM_enableADCTrigger(EPWM7_BASE, EPWM_SOC_B);
    EPWM_setTimeBaseCounterMode(EPWM7_BASE, EPWM_COUNTER_MODE_UP);

    // IDLE loop. Just sit and loop forever (optional):
    for(;;)
    {
        if(errorFlag)
        {
            GPIO_writePin(ENA_out, 0);
            GPIO_writePin(ENB_out, 0);
            asm("   ESTOP0");
        }


        if (tx_can_msg)
        {
            //
            // Transmit the message.
            //
            CAN_sendMessage(CANA_BASE, 1, 4, txMsgData);

            while(txMsgSuccessful == 1);

            txMsgData[0] += 0x01;
            txMsgData[1] += 0x01;
            txMsgData[2] += 0x01;
            txMsgData[3] += 0x01;

            //
            // Reset data if exceeds a byte
            //
            if(txMsgData[0] > 0xFF)
            {
                txMsgData[0] = 0;
            }
            if(txMsgData[1] > 0xFF)
            {
                txMsgData[1] = 0;
            }
            if(txMsgData[2] > 0xFF)
            {
                txMsgData[2] = 0;
            }
            if(txMsgData[3] > 0xFF)
            {
                txMsgData[3] = 0;
            }

            //
            // Update the flag for next message.
            //
            txMsgSuccessful  = 1;
        }
    }
}

//
// Function to configure ePWM7 to generate the SOC.
//
void initEPWM(void)
{
    //
    // Disable SOCA
    //
    EPWM_disableADCTrigger(EPWM7_BASE, EPWM_SOC_B);

    //
    // Configure the SOC to occur on the first up-count event
    //
    EPWM_setADCTriggerSource(EPWM7_BASE, EPWM_SOC_B, EPWM_SOC_TBCTR_U_CMPB);
    EPWM_setADCTriggerEventPrescale(EPWM7_BASE, EPWM_SOC_B, 1);

    //
    // Set the compare B value to 1000 and the period to 1999
    // Assuming ePWM clock is 100MHz, this would give 50kHz sampling
    // 50MHz ePWM clock would give 25kHz sampling, etc.
    // The sample rate can also be modulated by changing the ePWM period
    // directly (ensure that the compare A value is less than the period).
    //
    EPWM_setCounterCompareValue(EPWM7_BASE, EPWM_COUNTER_COMPARE_B, 6000);
    EPWM_setTimeBasePeriod(EPWM7_BASE, 11999);

    //
    // Set the local ePWM module clock divider to /1
    //
    EPWM_setClockPrescaler(EPWM7_BASE,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    //
    // Freeze the counter
    //
    EPWM_setTimeBaseCounterMode(EPWM7_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
}

//
// initEPWM2 - Configure ePWM2
//
void initEPWM2()
{
    //
    // Information this example uses to keep track of the direction the
    // CMPA/CMPB values are moving, the min and max allowed values and
    // a pointer to the correct ePWM registers
    //
    epwm2Info.epwmCompADirection = EPWM_CMP_UP;
    epwm2Info.epwmCompBDirection = EPWM_CMP_UP;
    epwm2Info.epwmTimerIntCount = 0U;
    epwm2Info.epwmModule = myEPWM3_BASE;
    epwm2Info.epwmMaxCompB = EPWM3_MAX_CMPB;
    epwm2Info.epwmMinCompB = EPWM3_MIN_CMPB;
}

//
// initEPWM3 - Configure ePWM3
//
void initEPWM3(void)
{
    //
    // Information this example uses to keep track of the direction the
    // CMPA/CMPB values are moving, the min and max allowed values and
    // a pointer to the correct ePWM registers
    //
    epwm3Info.epwmCompADirection = EPWM_CMP_UP;
    epwm3Info.epwmCompBDirection = EPWM_CMP_DOWN;
    epwm3Info.epwmTimerIntCount = 0U;
    epwm3Info.epwmModule = myEPWM4_BASE;
    epwm3Info.epwmMaxCompB = EPWM3_MAX_CMPB;
    epwm3Info.epwmMinCompB = EPWM3_MIN_CMPB;
}

//
// cpuTimer0ISR - Counter for CpuTimer0
//
__interrupt void fanctrlISR(void)
{
    // Low priority reads for fan control - could be moved to slower timer
    adc_raw_ntc1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);   // NTC1
    adc_raw_ntc2 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);   // NTC2
    adc_raw_fans = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER5);   // FAN_SENS

    if (adc_raw_ntc1 >= OVER_TEMP_THRESH && adc_raw_ntc2 >= OVER_TEMP_THRESH && over_temp_thresh == 0)
    {
        over_temp_thresh = 1;
        GPIO_writePin(FAN_ctrl_out, 0); // turn on fan
    }
    else if (over_temp_thresh == 1)
    {
        if (adc_raw_ntc1 >= TEMP_HYST_THRESH && adc_raw_ntc2 >= TEMP_HYST_THRESH)
        {
            if (adc_raw_fans < FAN_ON_OFF_THRESH)
            {
                GPIO_writePin(FAN_ctrl_out, 1); // turn off fan
                GPIO_writePin(ENA_out, 0);
                GPIO_writePin(ENB_out, 0);
                // TO DO: Write (CAN TX) fan fault message high
            }
            // Leave fan on
        }
        else
        {
            over_temp_thresh = 0;
            GPIO_writePin(FAN_ctrl_out, 1); // turn off fan
        }
    }
    else
    {
        if (adc_raw_fans >= FAN_ON_OFF_THRESH)
        {
            GPIO_writePin(FAN_ctrl_out, 1); // turn off fan
            GPIO_writePin(ENA_out, 0);
            GPIO_writePin(ENB_out, 0);
            // TO DO: Write (CAN TX) fan fault message high when was meant to be low
        }
    }

//    GPIO_togglePin(FAN_ctrl_out);

    //
    // Acknowledge this interrupt to receive more interrupts from group 1
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

//
// ADC A Interrupt 1 ISR
//
__interrupt void adcA1ISR(void)
{
    //
    // Store results
    //
    adc_raw_iac1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER2);   // G1_CUR
    adc_raw_iac2 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER3);   // G2_CUR
    adc_raw_vdc1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER7);   // DC1_LNK
    adc_raw_vdc2 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER10);  // DC2_LNK
    adc_raw_vac1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER11);  // G1_VLT
    adc_raw_vac2 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER15);  // G2_VLT

    //
    // Clear the interrupt flag
    //
    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    //
    // Check if overflow has occurred
    //
    if(true == ADC_getInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1))
    {
        ADC_clearInterruptOverflowStatus(ADCA_BASE, ADC_INT_NUMBER1);
        ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);
    }

    //
    // Acknowledge the interrupt
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

__interrupt void gbl_flt_ISR(void)
{
    // Write code to handle fault - STOP ALL GATE signaling
    GPIO_writePin(ENA_out, 0);
    GPIO_writePin(ENB_out, 0);

    // Acknowledge the interrupt
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

__interrupt void gbl_enbl_ISR(void)
{
    uint32_t enable_val;
    enable_val = GPIO_readPin(EN_in);

    GPIO_writePin(ENA_out, enable_val);
    GPIO_writePin(ENB_out, enable_val);

    // Acknowledge the interrupt
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

//
// epwm2ISR - ePWM 2 ISR
//
__interrupt void epwm2ISR(void)
{
    // Update the CMPA and CMPB values
    updateCompare(&epwm2Info);

    // Clear INT flag for this timer
    EPWM_clearEventTriggerInterruptFlag(myEPWM3_BASE);

    // Acknowledge interrupt group
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

//
// epwm3ISR - ePWM 3 ISR
//
__interrupt void epwm3ISR(void)
{
    // Update the CMPA and CMPB values
    updateCompare(&epwm3Info);

    // Clear INT flag for this timer
    EPWM_clearEventTriggerInterruptFlag(myEPWM4_BASE);

    // Acknowledge interrupt group
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

__interrupt void myCAN0_0_ISR(void)
{
    uint32_t status;
    uint16_t rxMsgData[4];

    status = CAN_getInterruptCause(CANA_BASE);

    if(status == CAN_INT_INT0ID_STATUS)
    {
        status = CAN_getStatus(CANA_BASE);

        if(((status  & ~(CAN_STATUS_RXOK)) != CAN_STATUS_LEC_MSK) &&
                   ((status  & ~(CAN_STATUS_RXOK)) != CAN_STATUS_LEC_NONE))
        {
            errorFlag = 1;
        }
        else if(((status  & ~(CAN_STATUS_RXOK)) != CAN_STATUS_LEC_MSK) &&
                   ((status  & ~(CAN_STATUS_RXOK)) != CAN_STATUS_LEC_NONE))
        {
            errorFlag = 1;
        }
    }
    else if(status == 1)
    {
        CAN_clearInterruptStatus(CANA_BASE, 1);

        errorFlag = 0;

        txMsgSuccessful  = 0;
    }
    else if(status == 2)
    {
        CAN_readMessage(CANA_BASE, 2, rxMsgData);

        CAN_clearInterruptStatus(CANA_BASE, 2);

        errorFlag = 0;
    }
    else
    {

    }

    CAN_clearGlobalInterruptStatus(CANA_BASE, CAN_GLOBAL_INT_CANINT0);

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

__interrupt void myCAN0_1_ISR(void)
{
    CAN_clearGlobalInterruptStatus(CANA_BASE, CAN_GLOBAL_INT_CANINT1);

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);
}

void updateCompare(epwmInformation *epwmInfo)
{
    uint16_t compBValue;

    compBValue = EPWM_getCounterCompareValue(epwmInfo->epwmModule,
                                             EPWM_COUNTER_COMPARE_B);

    //  Change the CMPB values every 10th interrupt.
    if(epwmInfo->epwmTimerIntCount == 10U)
    {
        epwmInfo->epwmTimerIntCount = 0U;

        if(epwmInfo->epwmCompBDirection == EPWM_CMP_UP)
        {
            if(compBValue < (epwmInfo->epwmMaxCompB))
            {
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_B,
                                            ++compBValue);
            }
            else
            {
                epwmInfo->epwmCompBDirection = EPWM_CMP_DOWN;
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_B,
                                            --compBValue);
            }
        }
        else
        {
            if(compBValue == (epwmInfo->epwmMinCompB))
            {
                epwmInfo->epwmCompBDirection = EPWM_CMP_UP;
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_B,
                                            ++compBValue);
            }
            else
            {
                EPWM_setCounterCompareValue(epwmInfo->epwmModule,
                                            EPWM_COUNTER_COMPARE_B,
                                            --compBValue);
            }
        }
    }
    else
    {
        epwmInfo->epwmTimerIntCount++;
    }
}
