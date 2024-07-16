################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../280023_RAM_lnk.cmd 

SYSCFG_SRCS += \
../inverter_basic.syscfg 

LIB_SRCS += \
C:/ti/c2000/C2000Ware_5_01_00_00/driverlib/f28002x/driverlib/ccs/Debug/driverlib.lib 

C_SRCS += \
../inverter_basic.c \
./syscfg/board.c 

GEN_FILES += \
./syscfg/board.c 

GEN_MISC_DIRS += \
./syscfg 

C_DEPS += \
./inverter_basic.d \
./syscfg/board.d 

OBJS += \
./inverter_basic.obj \
./syscfg/board.obj 

GEN_MISC_FILES += \
./syscfg/board.h \
./syscfg/pinmux.csv \
./syscfg/epwm.dot \
./syscfg/adc.dot \
./syscfg/clocktree.h 

GEN_MISC_DIRS__QUOTED += \
"syscfg" 

OBJS__QUOTED += \
"inverter_basic.obj" \
"syscfg\board.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\board.h" \
"syscfg\pinmux.csv" \
"syscfg\epwm.dot" \
"syscfg\adc.dot" \
"syscfg\clocktree.h" 

C_DEPS__QUOTED += \
"inverter_basic.d" \
"syscfg\board.d" 

GEN_FILES__QUOTED += \
"syscfg\board.c" 

C_SRCS__QUOTED += \
"../inverter_basic.c" \
"./syscfg/board.c" 

SYSCFG_SRCS__QUOTED += \
"../inverter_basic.syscfg" 


