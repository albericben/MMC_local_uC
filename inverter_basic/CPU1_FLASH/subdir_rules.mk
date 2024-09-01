################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 -Ooff --include_path="C:/Users/alber/Documents/MMC_local_uC/inverter_basic" --include_path="C:/ti/c2000/C2000Ware_5_01_00_00" --include_path="C:/Users/alber/Documents/MMC_local_uC/inverter_basic/device" --include_path="C:/ti/c2000/C2000Ware_5_01_00_00/driverlib/f28002x/driverlib" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=_FLASH --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/alber/Documents/MMC_local_uC/inverter_basic/CPU1_FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1228524897: ../inverter_basic.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1260/ccs/utils/sysconfig_1.19.0/sysconfig_cli.bat" --script "C:/Users/alber/Documents/MMC_local_uC/inverter_basic/inverter_basic.syscfg" -o "syscfg" -s "C:/ti/c2000/C2000Ware_5_01_00_00/.metadata/sdk.json" -d "F28002x" --package 80QFP --part F28002x_80QFP --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-1228524897 ../inverter_basic.syscfg
syscfg/board.h: build-1228524897
syscfg/board.cmd.genlibs: build-1228524897
syscfg/board.opt: build-1228524897
syscfg/pinmux.csv: build-1228524897
syscfg/epwm.dot: build-1228524897
syscfg/c2000ware_libraries.cmd.genlibs: build-1228524897
syscfg/c2000ware_libraries.opt: build-1228524897
syscfg/c2000ware_libraries.c: build-1228524897
syscfg/c2000ware_libraries.h: build-1228524897
syscfg/clocktree.h: build-1228524897
syscfg: build-1228524897

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 -Ooff --include_path="C:/Users/alber/Documents/MMC_local_uC/inverter_basic" --include_path="C:/ti/c2000/C2000Ware_5_01_00_00" --include_path="C:/Users/alber/Documents/MMC_local_uC/inverter_basic/device" --include_path="C:/ti/c2000/C2000Ware_5_01_00_00/driverlib/f28002x/driverlib" --include_path="C:/ti/ccs1260/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=_FLASH --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/alber/Documents/MMC_local_uC/inverter_basic/CPU1_FLASH/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


