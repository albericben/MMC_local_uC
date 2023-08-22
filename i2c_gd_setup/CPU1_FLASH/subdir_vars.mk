################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../28002x_generic_flash_lnk.cmd 

SYSCFG_SRCS += \
../c2000.syscfg 

LIB_SRCS += \
C:/ti/c2000/C2000Ware_5_00_00_00/driverlib/f28002x/driverlib/ccs/Debug/driverlib.lib 

C_SRCS += \
./syscfg/board.c \
./syscfg/c2000ware_libraries.c \
../i2cLib_polling.c \
../i2c_gd_setup.c 

GEN_FILES += \
./syscfg/board.c \
./syscfg/board.opt \
./syscfg/c2000ware_libraries.opt \
./syscfg/c2000ware_libraries.c 

GEN_MISC_DIRS += \
./syscfg/ 

C_DEPS += \
./syscfg/board.d \
./syscfg/c2000ware_libraries.d \
./i2cLib_polling.d \
./i2c_gd_setup.d 

GEN_OPTS += \
./syscfg/board.opt \
./syscfg/c2000ware_libraries.opt 

OBJS += \
./syscfg/board.obj \
./syscfg/c2000ware_libraries.obj \
./i2cLib_polling.obj \
./i2c_gd_setup.obj 

GEN_MISC_FILES += \
./syscfg/board.h \
./syscfg/board.cmd.genlibs \
./syscfg/pinmux.csv \
./syscfg/c2000ware_libraries.cmd.genlibs \
./syscfg/c2000ware_libraries.h \
./syscfg/clocktree.h 

GEN_MISC_DIRS__QUOTED += \
"syscfg\" 

OBJS__QUOTED += \
"syscfg\board.obj" \
"syscfg\c2000ware_libraries.obj" \
"i2cLib_polling.obj" \
"i2c_gd_setup.obj" 

GEN_MISC_FILES__QUOTED += \
"syscfg\board.h" \
"syscfg\board.cmd.genlibs" \
"syscfg\pinmux.csv" \
"syscfg\c2000ware_libraries.cmd.genlibs" \
"syscfg\c2000ware_libraries.h" \
"syscfg\clocktree.h" 

C_DEPS__QUOTED += \
"syscfg\board.d" \
"syscfg\c2000ware_libraries.d" \
"i2cLib_polling.d" \
"i2c_gd_setup.d" 

GEN_FILES__QUOTED += \
"syscfg\board.c" \
"syscfg\board.opt" \
"syscfg\c2000ware_libraries.opt" \
"syscfg\c2000ware_libraries.c" 

SYSCFG_SRCS__QUOTED += \
"../c2000.syscfg" 

C_SRCS__QUOTED += \
"./syscfg/board.c" \
"./syscfg/c2000ware_libraries.c" \
"../i2cLib_polling.c" \
"../i2c_gd_setup.c" 


