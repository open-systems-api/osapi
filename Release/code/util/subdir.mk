################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/util/util.c 

OBJS += \
./code/util/util.o 

C_DEPS += \
./code/util/util.d 


# Each subdirectory must supply rules for building sources it contributes
code/util/%.o: ../code/util/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -DOS_LINUX -D_DEFAULT_SOURCE -I"../code" -I/usr/include -O3 -Wall -c -fmessage-length=0 -v -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


