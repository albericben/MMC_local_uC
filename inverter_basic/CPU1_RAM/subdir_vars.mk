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
./syscfg/board.c \
./syscfg/c2000ware_libraries.c 

GEN_FILES += \
./syscfg/board.c \
./syscfg/board.opt \
./syscfg/c2000ware_libraries.opt \
./syscfg/c2000ware_libraries.c 

GEN_MISC_DIRS += \
./syscfg 

C_DEPS += \
./inverter_basic.d \
./syscfg/board.d \
./syscfg/c2000ware_libraries.d 

GEN_OPTS += \
./syscfg/board.opt \
./syscfg/c2000ware_libraries.opt 

OBJS += \
./inverter_basic.obj \
./syscfg/board.obj \
./syscfg/c2000ware_libraries.obj 

GEN_MISC_FILES += \
./syscfg/board.h \
./syscfg/board.cmd.genlibs \
./syscfg/pinmux.csv \
./syscfg/epwm.dot \
./syscfg/c2000ware_libraries.cmd.genlibs \
./syscfg/c2000ware_libraries.h \
./syscfg/clocktree.h 

GEN_MISC_DIRS__QUOTED += \
"syscfg" 

OBJS__QUOTED += \
"inverter_basic.obj" \
"syscfg\board.obj" \
"syscfg\c2000ware_libraries.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\board.h" \
"syscfg\board.cmd.genlibs" \
"syscfg\pinmux.csv" \
"syscfg\epwm.dot" \
"syscfg\c2000ware_libraries.cmd.genlibs" \
"syscfg\c2000ware_libraries.h" \
"syscfg\clocktree.h" 

C_DEPS__QUOTED += \
"inverter_basic.d" \
"syscfg\board.d" \
"syscfg\c2000ware_libraries.d" 

GEN_FILES__QUOTED += \
"syscfg\board.c" \
"syscfg\board.opt" \
"syscfg\c2000ware_libraries.opt" \
"syscfg\c2000ware_libraries.c" 

C_SRCS__QUOTED += \
"../inverter_basic.c" \
"./syscfg/board.c" \
"./syscfg/c2000ware_libraries.c" 

SYSCFG_SRCS__QUOTED += \
"../inverter_basic.syscfg" 


