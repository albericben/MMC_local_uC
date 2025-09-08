################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 -Ooff --include_path="C:/Users/alber/workspace_ccstheia/inverter_basic" --include_path="C:/ti/C2000Ware_5_04_00_00" --include_path="C:/Users/alber/workspace_ccstheia/inverter_basic/device" --include_path="C:/ti/C2000Ware_5_04_00_00/driverlib/f28002x/driverlib" --include_path="C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/include" --define=DEBUG --define=RAM --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/alber/workspace_ccstheia/inverter_basic/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1228524897: ../inverter_basic.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs2020/ccs/utils/sysconfig_1.24.0/sysconfig_cli.bat" --script "C:/Users/alber/workspace_ccstheia/inverter_basic/inverter_basic.syscfg" -o "syscfg" -s "C:/ti/C2000Ware_5_04_00_00/.metadata/sdk.json" -d "F28002x" -p "48QFP" -r "F28002x_48QFP" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-1228524897 ../inverter_basic.syscfg
syscfg/board.h: build-1228524897
syscfg/board.cmd.genlibs: build-1228524897
syscfg/board.opt: build-1228524897
syscfg/board.json: build-1228524897
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
	"C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 -Ooff --include_path="C:/Users/alber/workspace_ccstheia/inverter_basic" --include_path="C:/ti/C2000Ware_5_04_00_00" --include_path="C:/Users/alber/workspace_ccstheia/inverter_basic/device" --include_path="C:/ti/C2000Ware_5_04_00_00/driverlib/f28002x/driverlib" --include_path="C:/ti/ccs2020/ccs/tools/compiler/ti-cgt-c2000_22.6.2.LTS/include" --define=DEBUG --define=RAM --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/alber/workspace_ccstheia/inverter_basic/CPU1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


