################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/Events.c" \
"../Sources/FSL_utils.c" \
"../Sources/main.c" \
"../Sources/mqx_tasks.c" \
"../Sources/sa_mtb.c" \
"../Sources/tasks_func.c" \
"../Sources/user_tasks.c" \

C_SRCS += \
../Sources/Events.c \
../Sources/FSL_utils.c \
../Sources/main.c \
../Sources/mqx_tasks.c \
../Sources/sa_mtb.c \
../Sources/tasks_func.c \
../Sources/user_tasks.c \

OBJS += \
./Sources/Events.o \
./Sources/FSL_utils.o \
./Sources/main.o \
./Sources/mqx_tasks.o \
./Sources/sa_mtb.o \
./Sources/tasks_func.o \
./Sources/user_tasks.o \

OBJS_QUOTED += \
"./Sources/Events.o" \
"./Sources/FSL_utils.o" \
"./Sources/main.o" \
"./Sources/mqx_tasks.o" \
"./Sources/sa_mtb.o" \
"./Sources/tasks_func.o" \
"./Sources/user_tasks.o" \

C_DEPS += \
./Sources/Events.d \
./Sources/FSL_utils.d \
./Sources/main.d \
./Sources/mqx_tasks.d \
./Sources/sa_mtb.d \
./Sources/tasks_func.d \
./Sources/user_tasks.d \

OBJS_OS_FORMAT += \
./Sources/Events.o \
./Sources/FSL_utils.o \
./Sources/main.o \
./Sources/mqx_tasks.o \
./Sources/sa_mtb.o \
./Sources/tasks_func.o \
./Sources/user_tasks.o \

C_DEPS_QUOTED += \
"./Sources/Events.d" \
"./Sources/FSL_utils.d" \
"./Sources/main.d" \
"./Sources/mqx_tasks.d" \
"./Sources/sa_mtb.d" \
"./Sources/tasks_func.d" \
"./Sources/user_tasks.d" \


# Each subdirectory must supply rules for building sources it contributes
Sources/Events.o: ../Sources/Events.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/Events.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/Events.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/FSL_utils.o: ../Sources/FSL_utils.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/FSL_utils.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/FSL_utils.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mqx_tasks.o: ../Sources/mqx_tasks.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/mqx_tasks.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mqx_tasks.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/tasks_func.o: ../Sources/tasks_func.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/tasks_func.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/tasks_func.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/user_tasks.o: ../Sources/user_tasks.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/user_tasks.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/user_tasks.o"
	@echo 'Finished building: $<'
	@echo ' '


