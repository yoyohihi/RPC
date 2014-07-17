################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../RPCLib/ClientSocket.cpp \
../RPCLib/Security.cpp \
../RPCLib/ServerSocket.cpp \
../RPCLib/Socket.cpp \
../RPCLib/SocketManager.cpp \
../RPCLib/Util.cpp \
../RPCLib/binder.cpp \
../RPCLib/rpc_api.cpp \
../RPCLib/rpc_argType.cpp 

OBJS += \
./RPCLib/ClientSocket.o \
./RPCLib/Security.o \
./RPCLib/ServerSocket.o \
./RPCLib/Socket.o \
./RPCLib/SocketManager.o \
./RPCLib/Util.o \
./RPCLib/binder.o \
./RPCLib/rpc_api.o \
./RPCLib/rpc_argType.o 

CPP_DEPS += \
./RPCLib/ClientSocket.d \
./RPCLib/Security.d \
./RPCLib/ServerSocket.d \
./RPCLib/Socket.d \
./RPCLib/SocketManager.d \
./RPCLib/Util.d \
./RPCLib/binder.d \
./RPCLib/rpc_api.d \
./RPCLib/rpc_argType.d 


# Each subdirectory must supply rules for building sources it contributes
RPCLib/%.o: ../RPCLib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


