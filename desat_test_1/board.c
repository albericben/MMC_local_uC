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
    CPUTIMER_init();
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
    // GPIO4 -> FLTN_in Pinmux
    GPIO_setPinConfig(GPIO_4_GPIO4);
    // GPIO32 -> ENA_out Pinmux
    GPIO_setPinConfig(GPIO_32_GPIO32);
    // GPIO7 -> SIGA_out Pinmux
    GPIO_setPinConfig(GPIO_7_GPIO7);

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
    CPUTimer_setPeriod(myCPUTIMER0_BASE, 600U);
    CPUTimer_enableInterrupt(myCPUTIMER0_BASE);
    CPUTimer_stopTimer(myCPUTIMER0_BASE);

    CPUTimer_reloadTimerCounter(myCPUTIMER0_BASE);
    CPUTimer_startTimer(myCPUTIMER0_BASE);
}
//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
void GPIO_init(){
    FLTN_in_init();
    SIGA_out_init();
    ENA_out_init();
}

void FLTN_in_init(){
    GPIO_setPadConfig(FLTN_in, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(FLTN_in, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(FLTN_in, GPIO_DIR_MODE_IN);
}
void SIGA_out_init(){
    GPIO_writePin(SIGA_out, 0);
    GPIO_setPadConfig(SIGA_out, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(SIGA_out, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(SIGA_out, GPIO_DIR_MODE_OUT);
}
void ENA_out_init(){
    GPIO_writePin(ENA_out, 0);
    GPIO_setPadConfig(ENA_out, GPIO_PIN_TYPE_STD | GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(ENA_out, GPIO_QUAL_SYNC);
    GPIO_setDirectionMode(ENA_out, GPIO_DIR_MODE_OUT);
}

//*****************************************************************************
//
// INPUTXBAR Configurations
//
//*****************************************************************************
void INPUTXBAR_init(){
    myINPUTXBARINPUT0_init();
}

void myINPUTXBARINPUT0_init(){
    XBAR_setInputPin(INPUTXBAR_BASE, myINPUTXBARINPUT0_INPUT, myINPUTXBARINPUT0_SOURCE);
}

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************
void INTERRUPT_init(){

    // Interrupt Setings for INT_myCPUTIMER0
    Interrupt_register(INT_myCPUTIMER0, &fanctrlISR);
    Interrupt_enable(INT_myCPUTIMER0);

    // Interrupt Setings for INT_FLTN_in_XINT
    Interrupt_register(INT_FLTN_in_XINT, &gbl_flt_ISR);
    Interrupt_enable(INT_FLTN_in_XINT);
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
}

void FLTN_in_XINT_init(){
    GPIO_setInterruptType(FLTN_in_XINT, GPIO_INT_TYPE_FALLING_EDGE);
    GPIO_setInterruptPin(FLTN_in, FLTN_in_XINT);
    GPIO_enableInterrupt(FLTN_in_XINT);
}

