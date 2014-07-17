################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../test/procedure/server_functions.c 

OBJS += \
./test/procedure/server_functions.o 

C_DEPS += \
./test/procedure/server_functions.d 


# Each subdirectory must supply rules for building sources it contributes
test/procedure/%.o: ../test/procedure/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


