################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/common/common.c 

OBJS += \
./code/common/common.o 

C_DEPS += \
./code/common/common.d 


# Each subdirectory must supply rules for building sources it contributes
code/common/%.o: ../code/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -DOS_LINUX -D_DEFAULT_SOURCE -I"../code" -I/usr/include -O3 -Wall -c -fmessage-length=0 -fvisibility=hidden -v -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

