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

#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************

//
// ANALOG -> myANALOGPinMux0 Pinmux
//

//
// CANA -> myCAN0 Pinmux
//
//
// CANA_RX - GPIO Settings
//
#define GPIO_PIN_CANA_RX 3
#define myCAN0_CANRX_GPIO 3
#define myCAN0_CANRX_PIN_CONFIG GPIO_3_CANA_RX
//
// CANA_TX - GPIO Settings
//
#define GPIO_PIN_CANA_TX 2
#define myCAN0_CANTX_GPIO 2
#define myCAN0_CANTX_PIN_CONFIG GPIO_2_CANA_TX

//
// EPWM4 -> myEPWM4 Pinmux
//
//
// EPWM4_B - GPIO Settings
//
#define GPIO_PIN_EPWM4_B 7
#define myEPWM4_EPWMB_GPIO 7
#define myEPWM4_EPWMB_PIN_CONFIG GPIO_7_EPWM4_B

//
// EPWM3 -> myEPWM3 Pinmux
//
//
// EPWM3_B - GPIO Settings
//
#define GPIO_PIN_EPWM3_B 5
#define myEPWM3_EPWMB_GPIO 5
#define myEPWM3_EPWMB_PIN_CONFIG GPIO_5_EPWM3_B

//
// EPWM5 -> myEPWM5 Pinmux
//
//
// EPWM5_A - GPIO Settings
//
#define GPIO_PIN_EPWM5_A 16
#define myEPWM5_EPWMA_GPIO 16
#define myEPWM5_EPWMA_PIN_CONFIG GPIO_16_EPWM5_A
//
// GPIO0 - GPIO Settings
//
#define CSIG2_in_GPIO_PIN_CONFIG GPIO_0_GPIO0
//
// GPIO1 - GPIO Settings
//
#define CSIG1_in_GPIO_PIN_CONFIG GPIO_1_GPIO1
//
// GPIO4 - GPIO Settings
//
#define FLTN_in_GPIO_PIN_CONFIG GPIO_4_GPIO4
//
// GPIO6 - GPIO Settings
//
#define ENB_out_GPIO_PIN_CONFIG GPIO_6_GPIO6
//
// GPIO12 - GPIO Settings
//
#define GSYNC_in_GPIO_PIN_CONFIG GPIO_12_GPIO12
//
// GPIO24 - GPIO Settings
//
#define RDY_out_GPIO_PIN_CONFIG GPIO_24_GPIO24
//
// GPIO32 - GPIO Settings
//
#define ENA_out_GPIO_PIN_CONFIG GPIO_32_GPIO32
//
// GPIO33 - GPIO Settings
//
#define EN_in_GPIO_PIN_CONFIG GPIO_33_GPIO33

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
#define myADC0_BASE ADCA_BASE
#define myADC0_RESULT_BASE ADCARESULT_BASE
#define myADC0_SOC0 ADC_SOC_NUMBER0
#define myADC0_FORCE_SOC0 ADC_FORCE_SOC0
#define myADC0_SAMPLE_WINDOW_SOC0 80
#define myADC0_TRIGGER_SOURCE_SOC0 ADC_TRIGGER_SW_ONLY
#define myADC0_CHANNEL_SOC0 ADC_CH_ADCIN0
#define myADC0_SOC1 ADC_SOC_NUMBER1
#define myADC0_FORCE_SOC1 ADC_FORCE_SOC1
#define myADC0_SAMPLE_WINDOW_SOC1 80
#define myADC0_TRIGGER_SOURCE_SOC1 ADC_TRIGGER_SW_ONLY
#define myADC0_CHANNEL_SOC1 ADC_CH_ADCIN1
#define myADC0_SOC2 ADC_SOC_NUMBER2
#define myADC0_FORCE_SOC2 ADC_FORCE_SOC2
#define myADC0_SAMPLE_WINDOW_SOC2 80
#define myADC0_TRIGGER_SOURCE_SOC2 ADC_TRIGGER_EPWM7_SOCB
#define myADC0_CHANNEL_SOC2 ADC_CH_ADCIN2
#define myADC0_SOC3 ADC_SOC_NUMBER3
#define myADC0_FORCE_SOC3 ADC_FORCE_SOC3
#define myADC0_SAMPLE_WINDOW_SOC3 80
#define myADC0_TRIGGER_SOURCE_SOC3 ADC_TRIGGER_EPWM7_SOCB
#define myADC0_CHANNEL_SOC3 ADC_CH_ADCIN3
#define myADC0_SOC5 ADC_SOC_NUMBER5
#define myADC0_FORCE_SOC5 ADC_FORCE_SOC5
#define myADC0_SAMPLE_WINDOW_SOC5 80
#define myADC0_TRIGGER_SOURCE_SOC5 ADC_TRIGGER_SW_ONLY
#define myADC0_CHANNEL_SOC5 ADC_CH_ADCIN5
#define myADC0_SOC7 ADC_SOC_NUMBER7
#define myADC0_FORCE_SOC7 ADC_FORCE_SOC7
#define myADC0_SAMPLE_WINDOW_SOC7 80
#define myADC0_TRIGGER_SOURCE_SOC7 ADC_TRIGGER_EPWM7_SOCB
#define myADC0_CHANNEL_SOC7 ADC_CH_ADCIN7
#define myADC0_SOC10 ADC_SOC_NUMBER10
#define myADC0_FORCE_SOC10 ADC_FORCE_SOC10
#define myADC0_SAMPLE_WINDOW_SOC10 80
#define myADC0_TRIGGER_SOURCE_SOC10 ADC_TRIGGER_EPWM7_SOCB
#define myADC0_CHANNEL_SOC10 ADC_CH_ADCIN10
#define myADC0_SOC11 ADC_SOC_NUMBER11
#define myADC0_FORCE_SOC11 ADC_FORCE_SOC11
#define myADC0_SAMPLE_WINDOW_SOC11 80
#define myADC0_TRIGGER_SOURCE_SOC11 ADC_TRIGGER_EPWM7_SOCB
#define myADC0_CHANNEL_SOC11 ADC_CH_ADCIN11
#define myADC0_SOC15 ADC_SOC_NUMBER15
#define myADC0_FORCE_SOC15 ADC_FORCE_SOC15
#define myADC0_SAMPLE_WINDOW_SOC15 80
#define myADC0_TRIGGER_SOURCE_SOC15 ADC_TRIGGER_EPWM7_SOCB
#define myADC0_CHANNEL_SOC15 ADC_CH_ADCIN15
void myADC0_init();


//*****************************************************************************
//
// ASYSCTL Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// CAN Configurations
//
//*****************************************************************************
#define myCAN0_BASE CANA_BASE

#define myCAN0_MessageObj1_ID 357913941
#define myCAN0_MessageObj2_ID 1
void myCAN0_init();


//*****************************************************************************
//
// CPUTIMER Configurations
//
//*****************************************************************************
#define myCPUTIMER0_BASE CPUTIMER0_BASE
void myCPUTIMER0_init();

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
#define myEPWM4_BASE EPWM4_BASE
#define myEPWM4_TBPRD 10000
#define myEPWM4_COUNTER_MODE EPWM_COUNTER_MODE_UP
#define myEPWM4_TBPHS 0
#define myEPWM4_CMPA 0
#define myEPWM4_CMPB 1000
#define myEPWM4_CMPC 0
#define myEPWM4_CMPD 0
#define myEPWM4_DBRED 0
#define myEPWM4_DBFED 0
#define myEPWM4_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM4_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM4_INTERRUPT_SOURCE EPWM_INT_TBCTR_ZERO
#define myEPWM3_BASE EPWM3_BASE
#define myEPWM3_TBPRD 8000
#define myEPWM3_COUNTER_MODE EPWM_COUNTER_MODE_UP
#define myEPWM3_TBPHS 0
#define myEPWM3_CMPA 0
#define myEPWM3_CMPB 1000
#define myEPWM3_CMPC 0
#define myEPWM3_CMPD 0
#define myEPWM3_DBRED 0
#define myEPWM3_DBFED 0
#define myEPWM3_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM3_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM3_INTERRUPT_SOURCE EPWM_INT_TBCTR_ZERO
#define myEPWM5_BASE EPWM5_BASE
#define myEPWM5_TBPRD 20000
#define myEPWM5_COUNTER_MODE EPWM_COUNTER_MODE_UP
#define myEPWM5_TBPHS 0
#define myEPWM5_CMPA 10000
#define myEPWM5_CMPB 0
#define myEPWM5_CMPC 0
#define myEPWM5_CMPD 0
#define myEPWM5_DBRED 0
#define myEPWM5_DBFED 0
#define myEPWM5_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM5_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM5_INTERRUPT_SOURCE EPWM_INT_TBCTR_ZERO

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define CSIG2_in 0
void CSIG2_in_init();
#define CSIG1_in 1
void CSIG1_in_init();
#define FLTN_in 4
void FLTN_in_init();
#define ENB_out 6
void ENB_out_init();
#define GSYNC_in 12
void GSYNC_in_init();
#define RDY_out 24
void RDY_out_init();
#define ENA_out 32
void ENA_out_init();
#define EN_in 33
void EN_in_init();

//*****************************************************************************
//
// INPUTXBAR Configurations
//
//*****************************************************************************
#define myINPUTXBARINPUT0_SOURCE 4
#define myINPUTXBARINPUT0_INPUT XBAR_INPUT4
void myINPUTXBARINPUT0_init();
#define myINPUTXBARINPUT1_SOURCE 33
#define myINPUTXBARINPUT1_INPUT XBAR_INPUT5
void myINPUTXBARINPUT1_init();

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_myADC0_1
#define INT_myADC0_1 INT_ADCA1
#define INT_myADC0_1_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void adcA1ISR(void);

// Interrupt Settings for INT_myCAN0_0
#define INT_myCAN0_0 INT_CANA0
#define INT_myCAN0_0_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP9
extern __interrupt void myCAN0_0_ISR(void);

// Interrupt Settings for INT_myCAN0_1
#define INT_myCAN0_1 INT_CANA1
#define INT_myCAN0_1_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP9
extern __interrupt void myCAN0_1_ISR(void);

// Interrupt Settings for INT_myCPUTIMER0
#define INT_myCPUTIMER0 INT_TIMER0
#define INT_myCPUTIMER0_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void fanctrlISR(void);

// Interrupt Settings for INT_FLTN_in_XINT
#define INT_FLTN_in_XINT INT_XINT1
#define INT_FLTN_in_XINT_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void gbl_flt_ISR(void);

// Interrupt Settings for INT_EN_in_XINT
#define INT_EN_in_XINT INT_XINT2
#define INT_EN_in_XINT_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void gbl_enbl_ISR(void);

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// XINT Configurations
//
//*****************************************************************************
#define FLTN_in_XINT GPIO_INT_XINT1
#define FLTN_in_XINT_TYPE GPIO_INT_TYPE_FALLING_EDGE
void FLTN_in_XINT_init();
#define EN_in_XINT GPIO_INT_XINT2
#define EN_in_XINT_TYPE GPIO_INT_TYPE_BOTH_EDGES
void EN_in_XINT_init();

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	ADC_init();
void	ASYSCTL_init();
void	CAN_init();
void	CPUTIMER_init();
void	EPWM_init();
void	GPIO_init();
void	INPUTXBAR_init();
void	INTERRUPT_init();
void	SYNC_init();
void	XINT_init();
void	PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
