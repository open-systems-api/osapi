################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/sec/sec.c \
../code/sec/sec_identity.c 

OBJS += \
./code/sec/sec.o \
./code/sec/sec_identity.o 

C_DEPS += \
./code/sec/sec.d \
./code/sec/sec_identity.d 


# Each subdirectory must supply rules for building sources it contributes
code/sec/%.o: ../code/sec/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -DOS_LINUX -I/usr/include -I"${OSAPI_DIR}/code" -O2 -Wall -Wconversion -c -fmessage-length=0 -fvisibility=hidden -fno-short-enums -fPIC -fstack-protector-all -Wformat=2 -Wformat-security -Wstrict-overflow -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


