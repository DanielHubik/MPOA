################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 71
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := "$(GNU_Make_Install_DirEnv)/rm" -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include Sources/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include MQXLITE/psp/cortex_m/subdir.mk
-include MQXLITE/psp/cortex_m/core/M0/subdir.mk
-include MQXLITE/kernel/subdir.mk
-include MQXLITE/config/subdir.mk
-include Generated_Code/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
XSFK_KL25Z.elf \

EXECUTABLES_QUOTED += \
"XSFK_KL25Z.elf" \

EXECUTABLES_OS_FORMAT += \
XSFK_KL25Z.elf \

SECONDARY_FLASH += \
XSFK_KL25Z.hex \

SECONDARY_FLASH_QUOTED += \
"XSFK_KL25Z.hex" \

SECONDARY_FLASH_OS_FORMAT += \
XSFK_KL25Z.hex \

SECONDARY_SIZE += \
XSFK_KL25Z.siz \

SECONDARY_SIZE_QUOTED += \
"XSFK_KL25Z.siz" \

SECONDARY_SIZE_OS_FORMAT += \
XSFK_KL25Z.siz \


# All Target
all: warning-messages explicit-dependencies XSFK_KL25Z.elf secondary-outputs

# Tool invocations
XSFK_KL25Z.elf: $(OBJS) $(USER_OBJS) ../Project_Settings/Linker_Files/ProcessorExpert.ld
	@echo 'Building target: $@'
	@echo 'Executing target #72 $@'
	@echo 'Invoking: ARM Ltd Windows GCC C Linker'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc"  $(USER_OBJS_QUOTED)  @"XSFK_KL25Z.args" -o"XSFK_KL25Z.elf"
	@echo 'Finished building target: $@'
	@echo ' '

XSFK_KL25Z.hex: XSFK_KL25Z.elf
	@echo 'Executing target #73 $@'
	@echo 'Invoking: ARM Ltd Windows GNU Create Flash Image'
	"$(ARMSourceryDirEnv)/arm-none-eabi-objcopy"  -O srec XSFK_KL25Z.elf "XSFK_KL25Z.hex"
	@echo 'Finished building: $@'
	@echo ' '

XSFK_KL25Z.siz: XSFK_KL25Z.elf
	@echo 'Executing target #74 $@'
	@echo 'Invoking: ARM Ltd Windows GNU Print Size'
	"$(ARMSourceryDirEnv)/arm-none-eabi-size"  --format=berkeley XSFK_KL25Z.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S_DEPS_QUOTED) $(SECONDARY_FLASH_QUOTED) "./*/*.o" "./*/*/*.o" "./*/*/*/*/*/*.o" "./*/*/*/*.o"  "./*/*/*/*/*/*.d"  $(ASM_DEPS_QUOTED) $(SECONDARY_SIZE_QUOTED) $(ASM_UPPER_DEPS_QUOTED) $(SX_DEPS_QUOTED) $(EXECUTABLES_QUOTED) "./*/*.d" "./*/*/*.d" "./*/*/*/*.d"  $(ProjDirPath)/FLASH_EU/XSFK_KL25Z.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: ../Project_Settings/Linker_Files/ProcessorExpert.ld XSFK_KL25Z.elf XSFK_KL25Z.elf 

warning-messages: 

