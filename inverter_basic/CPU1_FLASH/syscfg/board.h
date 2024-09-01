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
// GPIO4 - GPIO Settings
//
#define FLTN_in_GPIO_PIN_CONFIG GPIO_4_GPIO4
//
// GPIO6 - GPIO Settings
//
#define ENB_out_GPIO_PIN_CONFIG GPIO_6_GPIO6
//
// GPIO24 - GPIO Settings
//
#define RDY_out_GPIO_PIN_CONFIG GPIO_24_GPIO24
//
// GPIO32 - GPIO Settings
//
#define ENA_out_GPIO_PIN_CONFIG GPIO_32_GPIO32

//*****************************************************************************
//
// ASYSCTL Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
#define myEPWM4_BASE EPWM4_BASE
#define myEPWM4_TBPRD 20000
#define myEPWM4_COUNTER_MODE EPWM_COUNTER_MODE_UP
#define myEPWM4_TBPHS 0
#define myEPWM4_CMPA 0
#define myEPWM4_CMPB 10000
#define myEPWM4_CMPC 0
#define myEPWM4_CMPD 0
#define myEPWM4_DBRED 0
#define myEPWM4_DBFED 0
#define myEPWM4_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM4_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM4_INTERRUPT_SOURCE EPWM_INT_TBCTR_ZERO
#define myEPWM3_BASE EPWM3_BASE
#define myEPWM3_TBPRD 20000
#define myEPWM3_COUNTER_MODE EPWM_COUNTER_MODE_UP
#define myEPWM3_TBPHS 0
#define myEPWM3_CMPA 0
#define myEPWM3_CMPB 10000
#define myEPWM3_CMPC 0
#define myEPWM3_CMPD 0
#define myEPWM3_DBRED 0
#define myEPWM3_DBFED 0
#define myEPWM3_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM3_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define myEPWM3_INTERRUPT_SOURCE EPWM_INT_TBCTR_ZERO

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define FLTN_in 4
void FLTN_in_init();
#define ENB_out 6
void ENB_out_init();
#define RDY_out 24
void RDY_out_init();
#define ENA_out 32
void ENA_out_init();

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

// Interrupt Settings for INT_FLTN_in_XINT
#define INT_FLTN_in_XINT INT_XINT1
#define INT_FLTN_in_XINT_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void gbl_flt_ISR(void);

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

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	ASYSCTL_init();
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
