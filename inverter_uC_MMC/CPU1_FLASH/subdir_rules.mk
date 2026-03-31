################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 -Ooff --include_path="C:/Users/alber/Documents/MMC_local_uC/inverter_uC_MMC" --include_path="C:/ti/C2000Ware_5_04_00_00" --include_path="C:/Users/alber/Documents/MMC_local_uC/inverter_uC_MMC/device" --include_path="/driverlib/f28002x/driverlib" --include_path="C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/include" --include_path="C:/ti/C2000Ware_5_04_00_00/driverlib/f28002x/driverlib" --define=DEBUG --define=_FLASH --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/alber/Documents/MMC_local_uC/inverter_uC_MMC/CPU1_FLASH/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-633334687: ../inverter_uC_MMC.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs2020/ccs/utils/sysconfig_1.24.0/sysconfig_cli.bat" --script "C:/Users/alber/Documents/MMC_local_uC/inverter_uC_MMC/inverter_uC_MMC.syscfg" -o "syscfg" -s "C:/ti/C2000Ware_5_04_00_00/.metadata/sdk.json" -d "F28002x" -p "48QFP" -r "F28002x_48QFP" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-633334687 ../inverter_uC_MMC.syscfg
syscfg/board.h: build-633334687
syscfg/board.cmd.genlibs: build-633334687
syscfg/board.opt: build-633334687
syscfg/board.json: build-633334687
syscfg/pinmux.csv: build-633334687
syscfg/epwm.dot: build-633334687
syscfg/adc.dot: build-633334687
syscfg/c2000ware_libraries.cmd.genlibs: build-633334687
syscfg/c2000ware_libraries.opt: build-633334687
syscfg/c2000ware_libraries.c: build-633334687
syscfg/c2000ware_libraries.h: build-633334687
syscfg/clocktree.h: build-633334687
syscfg: build-633334687

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 -Ooff --include_path="C:/Users/alber/Documents/MMC_local_uC/inverter_uC_MMC" --include_path="C:/ti/C2000Ware_5_04_00_00" --include_path="C:/Users/alber/Documents/MMC_local_uC/inverter_uC_MMC/device" --include_path="/driverlib/f28002x/driverlib" --include_path="C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/include" --include_path="C:/ti/C2000Ware_5_04_00_00/driverlib/f28002x/driverlib" --define=DEBUG --define=_FLASH --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/alber/Documents/MMC_local_uC/inverter_uC_MMC/CPU1_FLASH/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


