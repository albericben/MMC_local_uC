/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "board.h"

//*****************************************************************************
//
// Board Configurations
// Initializes the rest of the modules. 
// Call this function in your application if you wish to do all module 
// initialization.
// If you wish to not use some of the initializations, instead of the 
// Board_init use the individual Module_inits
//
//*****************************************************************************
void Board_init()
{
	EALLOW;

	PinMux_init();
	INPUTXBAR_init();
	SYNC_init();
	ASYSCTL_init();
	ADC_init();
	CAN_init();
	CPUTIMER_init();
	EPWM_init();
	GPIO_init();
	XINT_init();
	INTERRUPT_init();

	EDIS;
}

//*****************************************************************************
//
// PINMUX Configurations
//
//*****************************************************************************
void PinMux_init()
{
	//
	// PinMux for modules assigned to CPU1
	//
	
	//
	// ANALOG -> myANALOGPinMux0 Pinmux
	//
	// Analog PinMux for A0/C15
	GPIO_setPinConfig(GPIO_231_GPIO231);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(231, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A1
	GPIO_setPinConfig(GPIO_232_GPIO232);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(232, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A10/C10
	GPIO_setPinConfig(GPIO_230_GPIO230);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(230, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A11/C0
	GPIO_setPinConfig(GPIO_237_GPIO237);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(237, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A15/C7
	GPIO_setPinConfig(GPIO_233_GPIO233);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(233, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A2/C9
	GPIO_setPinConfig(GPIO_224_GPIO224);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(224, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A3/C5/VDAC
	GPIO_setPinConfig(GPIO_242_GPIO242);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(242, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A5/C2
	GPIO_setPinConfig(GPIO_244_GPIO244);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(244, GPIO_ANALOG_ENABLED);
	// Analog PinMux for A7/C3
	GPIO_setPinConfig(GPIO_245_GPIO245);
	// AIO -> Analog mode selected
	GPIO_setAnalogMode(245, GPIO_ANALOG_ENABLED);
	//
	// CANA -> myCAN0 Pinmux
	//
	GPIO_setPinConfig(myCAN0_CANRX_PIN_CONFIG);
	GPIO_setPadConfig(myCAN0_CANRX_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(myCAN0_CANRX_GPIO, GPIO_QUAL_ASYNC);

	GPIO_setPinConfig(myCAN0_CANTX_PIN_CONFIG);
	GPIO_setPadConfig(myCAN0_CANTX_GPIO, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(myCAN0_CANTX_GPIO, GPIO_QUAL_ASYNC);

	//
	// EPWM4 -> myEPWM4 Pinmux
	//
	GPIO_setPinConfig(myEPWM4_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM4_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM4_EPWMB_GPIO, GPIO_QUAL_SYNC);

	//
	// EPWM3 -> myEPWM3 Pinmux
	//
	GPIO_setPinConfig(myEPWM3_EPWMB_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM3_EPWMB_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM3_EPWMB_GPIO, GPIO_QUAL_SYNC);

	//
	// EPWM5 -> myEPWM5 Pinmux
	//
	GPIO_setPinConfig(myEPWM5_EPWMA_PIN_CONFIG);
	GPIO_setPadConfig(myEPWM5_EPWMA_GPIO, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(myEPWM5_EPWMA_GPIO, GPIO_QUAL_SYNC);

	// GPIO0 -> CSIG2_in Pinmux
	GPIO_setPinConfig(GPIO_0_GPIO0);
	// GPIO1 -> CSIG1_in Pinmux
	GPIO_setPinConfig(GPIO_1_GPIO1);
	// GPIO4 -> FLTN_in Pinmux
	GPIO_setPinConfig(GPIO_4_GPIO4);
	// GPIO6 -> ENB_out Pinmux
	GPIO_setPinConfig(GPIO_6_GPIO6);
	// GPIO12 -> GSYNC_in Pinmux
	GPIO_setPinConfig(GPIO_12_GPIO12);
	// GPIO24 -> RDY_out Pinmux
	GPIO_setPinConfig(GPIO_24_GPIO24);
	// GPIO32 -> ENA_out Pinmux
	GPIO_setPinConfig(GPIO_32_GPIO32);
	// GPIO33 -> EN_in Pinmux
	GPIO_setPinConfig(GPIO_33_GPIO33);

}

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
void ADC_init(){
	myADC0_init();
}

void myADC0_init(){
	//
	// ADC Initialization: Write ADC configurations and power up the ADC
	//
	// Configures the ADC module's offset trim
	//
	ADC_setOffsetTrimAll(ADC_REFERENCE_INTERNAL,ADC_REFERENCE_3_3V);
	//
	// Configures the analog-to-digital converter module prescaler.
	//
	ADC_setPrescaler(myADC0_BASE, ADC_CLK_DIV_2_0);
	//
	// Sets the timing of the end-of-conversion pulse
	//
	ADC_setInterruptPulseMode(myADC0_BASE, ADC_PULSE_END_OF_CONV);
	//
	// Powers up the analog-to-digital converter core.
	//
	ADC_enableConverter(myADC0_BASE);
	//
	// Delay for 1ms to allow ADC time to power up
	//
	DEVICE_DELAY_US(5000);
	//
	// SOC Configuration: Setup ADC EPWM channel and trigger settings
	//
	// Disables SOC burst mode.
	//
	ADC_disableBurstMode(myADC0_BASE);
	//
	// Sets the priority mode of the SOCs.
	//
	ADC_setSOCPriority(myADC0_BASE, ADC_PRI_ALL_ROUND_ROBIN);
	//
	// Start of Conversion 0 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 0
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN0
	//	 	Sample Window	: 8 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN0, 8U);
	ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER0, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 1 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 1
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN1
	//	 	Sample Window	: 8 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN1, 8U);
	ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER1, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 2 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 2
	//	  	Trigger			: ADC_TRIGGER_EPWM7_SOCB
	//	  	Channel			: ADC_CH_ADCIN2
	//	 	Sample Window	: 8 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER2, ADC_TRIGGER_EPWM7_SOCB, ADC_CH_ADCIN2, 8U);
	ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER2, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 3 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 3
	//	  	Trigger			: ADC_TRIGGER_EPWM7_SOCB
	//	  	Channel			: ADC_CH_ADCIN3
	//	 	Sample Window	: 8 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER3, ADC_TRIGGER_EPWM7_SOCB, ADC_CH_ADCIN3, 8U);
	ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER3, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 5 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 5
	//	  	Trigger			: ADC_TRIGGER_SW_ONLY
	//	  	Channel			: ADC_CH_ADCIN5
	//	 	Sample Window	: 8 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER5, ADC_TRIGGER_SW_ONLY, ADC_CH_ADCIN5, 8U);
	ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER5, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 7 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 7
	//	  	Trigger			: ADC_TRIGGER_EPWM7_SOCB
	//	  	Channel			: ADC_CH_ADCIN7
	//	 	Sample Window	: 8 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER7, ADC_TRIGGER_EPWM7_SOCB, ADC_CH_ADCIN7, 8U);
	ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER7, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 10 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 10
	//	  	Trigger			: ADC_TRIGGER_EPWM7_SOCB
	//	  	Channel			: ADC_CH_ADCIN10
	//	 	Sample Window	: 8 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER10, ADC_TRIGGER_EPWM7_SOCB, ADC_CH_ADCIN10, 8U);
	ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER10, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 11 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 11
	//	  	Trigger			: ADC_TRIGGER_EPWM7_SOCB
	//	  	Channel			: ADC_CH_ADCIN11
	//	 	Sample Window	: 8 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER11, ADC_TRIGGER_EPWM7_SOCB, ADC_CH_ADCIN11, 8U);
	ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER11, ADC_INT_SOC_TRIGGER_NONE);
	//
	// Start of Conversion 15 Configuration
	//
	//
	// Configures a start-of-conversion (SOC) in the ADC and its interrupt SOC trigger.
	// 	  	SOC number		: 15
	//	  	Trigger			: ADC_TRIGGER_EPWM7_SOCB
	//	  	Channel			: ADC_CH_ADCIN15
	//	 	Sample Window	: 8 SYSCLK cycles
	//		Interrupt Trigger: ADC_INT_SOC_TRIGGER_NONE
	//
	ADC_setupSOC(myADC0_BASE, ADC_SOC_NUMBER15, ADC_TRIGGER_EPWM7_SOCB, ADC_CH_ADCIN15, 8U);
	ADC_setInterruptSOCTrigger(myADC0_BASE, ADC_SOC_NUMBER15, ADC_INT_SOC_TRIGGER_NONE);
	//
	// ADC Interrupt 1 Configuration
	// 		Source	: ADC_SOC_NUMBER15
	// 		Interrupt Source: enabled
	// 		Continuous Mode	: disabled
	//
	//
	ADC_setInterruptSource(myADC0_BASE, ADC_INT_NUMBER1, ADC_SOC_NUMBER15);
	ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);
	ADC_disableContinuousMode(myADC0_BASE, ADC_INT_NUMBER1);
	ADC_enableInterrupt(myADC0_BASE, ADC_INT_NUMBER1);
}

//*****************************************************************************
//
// ASYSCTL Configurations
//
//*****************************************************************************
void ASYSCTL_init(){
	//
	// asysctl initialization
	//
	// Disables the temperature sensor output to the ADC.
	//
	ASysCtl_disableTemperatureSensor();
	//
	// Set the analog voltage reference selection to internal.
	//
	ASysCtl_setAnalogReferenceInternal( ASYSCTL_VREFHIA | ASYSCTL_VREFHIC );
	//
	// Set the internal analog voltage reference selection to 1.65V.
	//
	ASysCtl_setAnalogReference1P65( ASYSCTL_VREFHIA | ASYSCTL_VREFHIC );
}

//*****************************************************************************
//
// CAN Configurations
//
//*****************************************************************************
void CAN_init(){
	myCAN0_init();
}

void myCAN0_init(){
	CAN_initModule(myCAN0_BASE);
	//
	// Refer to the Driver Library User Guide for information on how to set
	// tighter timing control. Additionally, consult the device data sheet
	// for more information about the CAN module clocking.
	//
	CAN_setBitTiming(myCAN0_BASE, 7, 0, 15, 7, 3);
	//
	// Enable CAN Interrupts
	//
	CAN_enableInterrupt(myCAN0_BASE, CAN_INT_IE0);
	CAN_enableGlobalInterrupt(myCAN0_BASE, CAN_GLOBAL_INT_CANINT0);
	//
	// Initialize the transmit message object used for sending CAN messages.
	// Message Object Parameters:
	//      Message Object ID Number: 1
	//      Message Identifier: 357913941
	//      Message Frame: CAN_MSG_FRAME_EXT
	//      Message Type: CAN_MSG_OBJ_TYPE_TX
	//      Message ID Mask: 0
	//      Message Object Flags: CAN_MSG_OBJ_TX_INT_ENABLE
	//      Message Data Length: 4 Bytes
	//
	CAN_setupMessageObject(myCAN0_BASE, 1, myCAN0_MessageObj1_ID, CAN_MSG_FRAME_EXT,CAN_MSG_OBJ_TYPE_TX, 0, CAN_MSG_OBJ_TX_INT_ENABLE,4);
	//
	// Initialize the transmit message object used for sending CAN messages.
	// Message Object Parameters:
	//      Message Object ID Number: 2
	//      Message Identifier: 357913941
	//      Message Frame: CAN_MSG_FRAME_EXT
	//      Message Type: CAN_MSG_OBJ_TYPE_RX
	//      Message ID Mask: 0
	//      Message Object Flags: CAN_MSG_OBJ_RX_INT_ENABLE
	//      Message Data Length: 0 Bytes
	//
	CAN_setupMessageObject(myCAN0_BASE, 2, myCAN0_MessageObj2_ID, CAN_MSG_FRAME_EXT,CAN_MSG_OBJ_TYPE_RX, 0, CAN_MSG_OBJ_RX_INT_ENABLE,0);
	CAN_setInterruptMux(myCAN0_BASE, 0);
	//
	// Start CAN module operations
	//
	CAN_startModule(myCAN0_BASE);
}

//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
void CPUTIMER_init(){
	myCPUTIMER0_init();
}

void myCPUTIMER0_init(){
	CPUTimer_setEmulationMode(myCPUTIMER0_BASE, CPUTIMER_EMULATIONMODE_STOPAFTERNEXTDECREMENT);
	CPUTimer_setPreScaler(myCPUTIMER0_BASE, 0U);
	CPUTimer_setPeriod(myCPUTIMER0_BASE, 10000U);
	CPUTimer_enableInterrupt(myCPUTIMER0_BASE);
	CPUTimer_stopTimer(myCPUTIMER0_BASE);

	CPUTimer_reloadTimerCounter(myCPUTIMER0_BASE);
	CPUTimer_startTimer(myCPUTIMER0_BASE);
}

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
void EPWM_init(){
    EPWM_setClockPrescaler(myEPWM4_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(myEPWM4_BASE, 10000);	
    EPWM_enableGlobalLoadRegisters(myEPWM4_BASE, EPWM_GL_REGISTER_TBPRD_TBPRDHR);	
    EPWM_setTimeBaseCounter(myEPWM4_BASE, 0);	
    EPWM_setTimeBaseCounterMode(myEPWM4_BASE, EPWM_COUNTER_MODE_UP);	
    EPWM_disablePhaseShiftLoad(myEPWM4_BASE);	
    EPWM_setPhaseShift(myEPWM4_BASE, 0);	
    EPWM_setSyncInPulseSource(myEPWM4_BASE, EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM4);	
    EPWM_setCounterCompareValue(myEPWM4_BASE, EPWM_COUNTER_COMPARE_A, 0);	
    EPWM_disableCounterCompareShadowLoadMode(myEPWM4_BASE, EPWM_COUNTER_COMPARE_A);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM4_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(myEPWM4_BASE, EPWM_COUNTER_COMPARE_B, 1000);	
    EPWM_enableGlobalLoadRegisters(myEPWM4_BASE, EPWM_GL_REGISTER_CMPB_CMPBHR);	
    EPWM_disableCounterCompareShadowLoadMode(myEPWM4_BASE, EPWM_COUNTER_COMPARE_B);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM4_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setupEPWMLinks(myEPWM4_BASE, EPWM_LINK_WITH_EPWM_4, EPWM_LINK_COMP_B);	
    EPWM_enableGlobalLoadRegisters(myEPWM4_BASE, EPWM_GL_REGISTER_AQCSFRC);	
    EPWM_setActionQualifierContSWForceShadowMode(myEPWM4_BASE, EPWM_AQ_SW_IMMEDIATE_LOAD);	
    EPWM_setActionQualifierT1TriggerSource(myEPWM4_BASE, EPWM_AQ_TRIGGER_EVENT_TRIG_DCB_1);	
    EPWM_setActionQualifierT2TriggerSource(myEPWM4_BASE, EPWM_AQ_TRIGGER_EVENT_TRIG_DCB_1);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_enableGlobalLoadRegisters(myEPWM4_BASE, EPWM_GL_REGISTER_AQCTLB_AQCTLB2);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM4_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(myEPWM4_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(myEPWM4_BASE);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(myEPWM4_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(myEPWM4_BASE);	
    EPWM_enableInterrupt(myEPWM4_BASE);	
    EPWM_setInterruptSource(myEPWM4_BASE, EPWM_INT_TBCTR_ZERO);	
    EPWM_setInterruptEventCount(myEPWM4_BASE, 3);	
    EPWM_setClockPrescaler(myEPWM3_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(myEPWM3_BASE, 8000);	
    EPWM_enableGlobalLoadRegisters(myEPWM3_BASE, EPWM_GL_REGISTER_TBPRD_TBPRDHR);	
    EPWM_setTimeBaseCounter(myEPWM3_BASE, 0);	
    EPWM_setTimeBaseCounterMode(myEPWM3_BASE, EPWM_COUNTER_MODE_UP);	
    EPWM_disablePhaseShiftLoad(myEPWM3_BASE);	
    EPWM_setPhaseShift(myEPWM3_BASE, 0);	
    EPWM_setSyncInPulseSource(myEPWM3_BASE, EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM4);	
    EPWM_setCounterCompareValue(myEPWM3_BASE, EPWM_COUNTER_COMPARE_A, 0);	
    EPWM_disableCounterCompareShadowLoadMode(myEPWM3_BASE, EPWM_COUNTER_COMPARE_A);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM3_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(myEPWM3_BASE, EPWM_COUNTER_COMPARE_B, 1000);	
    EPWM_enableGlobalLoadRegisters(myEPWM3_BASE, EPWM_GL_REGISTER_CMPB_CMPBHR);	
    EPWM_disableCounterCompareShadowLoadMode(myEPWM3_BASE, EPWM_COUNTER_COMPARE_B);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM3_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setupEPWMLinks(myEPWM3_BASE, EPWM_LINK_WITH_EPWM_4, EPWM_LINK_COMP_B);	
    EPWM_enableGlobalLoadRegisters(myEPWM3_BASE, EPWM_GL_REGISTER_AQCSFRC);	
    EPWM_setActionQualifierContSWForceShadowMode(myEPWM3_BASE, EPWM_AQ_SW_IMMEDIATE_LOAD);	
    EPWM_setActionQualifierT1TriggerSource(myEPWM3_BASE, EPWM_AQ_TRIGGER_EVENT_TRIG_DCB_1);	
    EPWM_setActionQualifierT2TriggerSource(myEPWM3_BASE, EPWM_AQ_TRIGGER_EVENT_TRIG_DCB_1);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_enableGlobalLoadRegisters(myEPWM3_BASE, EPWM_GL_REGISTER_AQCTLB_AQCTLB2);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM3_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(myEPWM3_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(myEPWM3_BASE);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(myEPWM3_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(myEPWM3_BASE);	
    EPWM_enableInterrupt(myEPWM3_BASE);	
    EPWM_setInterruptSource(myEPWM3_BASE, EPWM_INT_TBCTR_ZERO);	
    EPWM_setInterruptEventCount(myEPWM3_BASE, 3);	
    EPWM_setClockPrescaler(myEPWM5_BASE, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);	
    EPWM_setTimeBasePeriod(myEPWM5_BASE, 20000);	
    EPWM_enableGlobalLoadRegisters(myEPWM5_BASE, EPWM_GL_REGISTER_TBPRD_TBPRDHR);	
    EPWM_setTimeBaseCounter(myEPWM5_BASE, 0);	
    EPWM_setTimeBaseCounterMode(myEPWM5_BASE, EPWM_COUNTER_MODE_UP);	
    EPWM_disablePhaseShiftLoad(myEPWM5_BASE);	
    EPWM_setPhaseShift(myEPWM5_BASE, 0);	
    EPWM_setSyncInPulseSource(myEPWM5_BASE, EPWM_SYNC_IN_PULSE_SRC_SYNCOUT_EPWM4);	
    EPWM_setCounterCompareValue(myEPWM5_BASE, EPWM_COUNTER_COMPARE_A, 10000);	
    EPWM_enableGlobalLoadRegisters(myEPWM5_BASE, EPWM_GL_REGISTER_CMPA_CMPAHR);	
    EPWM_disableCounterCompareShadowLoadMode(myEPWM5_BASE, EPWM_COUNTER_COMPARE_A);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM5_BASE, EPWM_COUNTER_COMPARE_A, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setCounterCompareValue(myEPWM5_BASE, EPWM_COUNTER_COMPARE_B, 0);	
    EPWM_disableCounterCompareShadowLoadMode(myEPWM5_BASE, EPWM_COUNTER_COMPARE_B);	
    EPWM_setCounterCompareShadowLoadMode(myEPWM5_BASE, EPWM_COUNTER_COMPARE_B, EPWM_COMP_LOAD_ON_CNTR_ZERO);	
    EPWM_setupEPWMLinks(myEPWM5_BASE, EPWM_LINK_WITH_EPWM_4, EPWM_LINK_COMP_B);	
    EPWM_enableGlobalLoadRegisters(myEPWM5_BASE, EPWM_GL_REGISTER_AQCSFRC);	
    EPWM_setActionQualifierContSWForceShadowMode(myEPWM5_BASE, EPWM_AQ_SW_IMMEDIATE_LOAD);	
    EPWM_enableGlobalLoadRegisters(myEPWM5_BASE, EPWM_GL_REGISTER_AQCTLA_AQCTLA2);	
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_LOW, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_HIGH, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_A, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_enableGlobalLoadRegisters(myEPWM5_BASE, EPWM_GL_REGISTER_AQCTLB_AQCTLB2);	
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);	
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_PERIOD);	
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);	
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);	
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);	
    EPWM_setActionQualifierAction(myEPWM5_BASE, EPWM_AQ_OUTPUT_B, EPWM_AQ_OUTPUT_NO_CHANGE, EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPB);	
    EPWM_setRisingEdgeDelayCountShadowLoadMode(myEPWM5_BASE, EPWM_RED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableRisingEdgeDelayCountShadowLoadMode(myEPWM5_BASE);	
    EPWM_setFallingEdgeDelayCountShadowLoadMode(myEPWM5_BASE, EPWM_FED_LOAD_ON_CNTR_ZERO);	
    EPWM_disableFallingEdgeDelayCountShadowLoadMode(myEPWM5_BASE);	
    EPWM_enableInterrupt(myEPWM5_BASE);	
    EPWM_setInterruptSource(myEPWM5_BASE, EPWM_INT_TBCTR_ZERO);	
    EPWM_setInterruptEventCount(myEPWM5_BASE, 3);	
}

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(){
	CSIG2_in_init();
	CSIG1_in_init();
	FLTN_in_init();
	ENB_out_init();
	GSYNC_in_init();
	RDY_out_init();
	ENA_out_init();
	EN_in_init();
}

void CSIG2_in_init(){
	GPIO_setPadConfig(CSIG2_in, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(CSIG2_in, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(CSIG2_in, GPIO_DIR_MODE_IN);
}
void CSIG1_in_init(){
	GPIO_setPadConfig(CSIG1_in, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(CSIG1_in, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(CSIG1_in, GPIO_DIR_MODE_IN);
}
void FLTN_in_init(){
	GPIO_setPadConfig(FLTN_in, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(FLTN_in, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(FLTN_in, GPIO_DIR_MODE_IN);
}
void ENB_out_init(){
	GPIO_setPadConfig(ENB_out, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(ENB_out, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(ENB_out, GPIO_DIR_MODE_OUT);
}
void GSYNC_in_init(){
	GPIO_setPadConfig(GSYNC_in, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(GSYNC_in, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(GSYNC_in, GPIO_DIR_MODE_IN);
}
void RDY_out_init(){
	GPIO_setPadConfig(RDY_out, GPIO_PIN_TYPE_OD);
	GPIO_setQualificationMode(RDY_out, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(RDY_out, GPIO_DIR_MODE_OUT);
}
void ENA_out_init(){
	GPIO_setPadConfig(ENA_out, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(ENA_out, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(ENA_out, GPIO_DIR_MODE_OUT);
}
void EN_in_init(){
	GPIO_setPadConfig(EN_in, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
	GPIO_setQualificationMode(EN_in, GPIO_QUAL_SYNC);
	GPIO_setDirectionMode(EN_in, GPIO_DIR_MODE_IN);
}

//*****************************************************************************
//
// INPUTXBAR Configurations
//
//*****************************************************************************
void INPUTXBAR_init(){
	myINPUTXBARINPUT0_init();
	myINPUTXBARINPUT1_init();
}

void myINPUTXBARINPUT0_init(){
	XBAR_setInputPin(INPUTXBAR_BASE, myINPUTXBARINPUT0_INPUT, myINPUTXBARINPUT0_SOURCE);
}
void myINPUTXBARINPUT1_init(){
	XBAR_setInputPin(INPUTXBAR_BASE, myINPUTXBARINPUT1_INPUT, myINPUTXBARINPUT1_SOURCE);
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){
	
	// Interrupt Setings for INT_myADC0_1
	Interrupt_register(INT_myADC0_1, &adcA1ISR);
	Interrupt_enable(INT_myADC0_1);
	
	// Interrupt Setings for INT_myCAN0_0
	Interrupt_register(INT_myCAN0_0, &myCAN0_0_ISR);
	Interrupt_enable(INT_myCAN0_0);
	
	// Interrupt Setings for INT_myCAN0_1
	Interrupt_register(INT_myCAN0_1, &myCAN0_1_ISR);
	Interrupt_enable(INT_myCAN0_1);
	
	// Interrupt Setings for INT_myCPUTIMER0
	Interrupt_register(INT_myCPUTIMER0, &fanctrlISR);
	Interrupt_enable(INT_myCPUTIMER0);
	
	// Interrupt Setings for INT_FLTN_in_XINT
	Interrupt_register(INT_FLTN_in_XINT, &gbl_flt_ISR);
	Interrupt_enable(INT_FLTN_in_XINT);
	
	// Interrupt Setings for INT_EN_in_XINT
	Interrupt_register(INT_EN_in_XINT, &gbl_enbl_ISR);
	Interrupt_enable(INT_EN_in_XINT);
}
//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************
void SYNC_init(){
	SysCtl_setSyncOutputConfig(SYSCTL_SYNC_OUT_SRC_EPWM1SYNCOUT);
	//
	// SOCA
	//
	SysCtl_enableExtADCSOCSource(0);
	//
	// SOCB
	//
	SysCtl_enableExtADCSOCSource(0);
}
//*****************************************************************************
//
// XINT Configurations
//
//*****************************************************************************
void XINT_init(){
	FLTN_in_XINT_init();
	EN_in_XINT_init();
}

void FLTN_in_XINT_init(){
	GPIO_setInterruptType(FLTN_in_XINT, GPIO_INT_TYPE_FALLING_EDGE);
	GPIO_setInterruptPin(FLTN_in, FLTN_in_XINT);
	GPIO_enableInterrupt(FLTN_in_XINT);
}
void EN_in_XINT_init(){
	GPIO_setInterruptType(EN_in_XINT, GPIO_INT_TYPE_BOTH_EDGES);
	GPIO_setInterruptPin(EN_in, EN_in_XINT);
	GPIO_enableInterrupt(EN_in_XINT);
}

