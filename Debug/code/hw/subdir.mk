################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/hw/hw.c 

OBJS += \
./code/hw/hw.o 

C_DEPS += \
./code/hw/hw.d 


# Each subdirectory must supply rules for building sources it contributes
code/hw/%.o: ../code/hw/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -DOS_LINUX -I"../code" -I/usr/include -O3 -g -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

