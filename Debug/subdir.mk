################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../binder_main.cpp \
../test_client.cpp \
../test_client2.cpp \
../test_server.cpp 

OBJS += \
./binder_main.o \
./test_client.o \
./test_client2.o \
./test_server.o 

CPP_DEPS += \
./binder_main.d \
./test_client.d \
./test_client2.d \
./test_server.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


