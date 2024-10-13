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

    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();
    Interrupt_register(INT_EPWM3, &epwm2ISR);
    Interrupt_register(INT_EPWM4, &epwm3ISR);

    txMsgData[0] = 0x12;
    txMsgData[1] = 0x34;
    txMsgData[2] = 0x56;
    txMsgData[3] = 0x78;

    // Disable sync(Freeze clock to PWM as well)
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

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

    EPWM_setCounterCompareValue(EPWM7_BASE, EPWM_COUNTER_COMPARE_B, 6000);
    EPWM_setTimeBasePeriod(EPWM7_BASE, 11999);

    EPWM_setClockPrescaler(EPWM7_BASE,
                           EPWM_CLOCK_DIVIDER_1,
                           EPWM_HSCLOCK_DIVIDER_1);

    EPWM_setTimeBaseCounterMode(EPWM7_BASE, EPWM_COUNTER_MODE_STOP_FREEZE);
}

//
// initEPWM2 - Configure ePWM2
//
void initEPWM2()
{
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
    // Controller code to update PWM

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
    // Controller code to update PWM

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
