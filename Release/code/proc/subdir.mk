################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/proc/proc_linux.c \
../code/proc/proc_posix.c 

OBJS += \
./code/proc/proc_linux.o \
./code/proc/proc_posix.o 

C_DEPS += \
./code/proc/proc_linux.d \
./code/proc/proc_posix.d 


# Each subdirectory must supply rules for building sources it contributes
code/proc/%.o: ../code/proc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -std=c11 -DOS_LINUX -D_DEFAULT_SOURCE -I"../code" -I/usr/include -O3 -Wall -c -fmessage-length=0 -v -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

