################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/clock/posix/clock_posix.c 

OBJS += \
./code/clock/posix/clock_posix.o 

C_DEPS += \
./code/clock/posix/clock_posix.d 


# Each subdirectory must supply rules for building sources it contributes
code/clock/posix/%.o: ../code/clock/posix/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -DOS_LINUX -I/usr/include -I"${OSAPI_DIR}/code" -O3 -Wall -Wconversion -c -fmessage-length=0 -fvisibility=hidden -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


