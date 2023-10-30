################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-829409601: ../c2000.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs1250/ccs/utils/sysconfig_1.18.0/sysconfig_cli.bat" -s "C:/ti/c2000/C2000Ware_5_00_00_00/.metadata/sdk.json" -d "F28002x" --script "C:/Users/alber/workspace_v12/i2c_ex3_external_loopback/c2000.syscfg" -o "syscfg" --package 80QFP --part F28002x_80QFP --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-829409601 ../c2000.syscfg
syscfg/board.h: build-829409601
syscfg/board.cmd.genlibs: build-829409601
syscfg/board.opt: build-829409601
syscfg/pinmux.csv: build-829409601
syscfg/c2000ware_libraries.cmd.genlibs: build-829409601
syscfg/c2000ware_libraries.opt: build-829409601
syscfg/c2000ware_libraries.c: build-829409601
syscfg/c2000ware_libraries.h: build-829409601
syscfg/clocktree.h: build-829409601
syscfg/: build-829409601

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 -Ooff --include_path="C:/Users/alber/workspace_v12/i2c_ex3_external_loopback" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00" --include_path="C:/Users/alber/workspace_v12/i2c_ex3_external_loopback/device" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/driverlib/f28002x/driverlib" --include_path="C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=RAM --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="C:/Users/alber/workspace_v12/i2c_ex3_external_loopback/CPU1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --idiv_support=idiv0 --tmu_support=tmu0 -Ooff --include_path="C:/Users/alber/workspace_v12/i2c_ex3_external_loopback" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00" --include_path="C:/Users/alber/workspace_v12/i2c_ex3_external_loopback/device" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/driverlib/f28002x/driverlib" --include_path="C:/ti/ccs1250/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=RAM --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="C:/Users/alber/workspace_v12/i2c_ex3_external_loopback/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


