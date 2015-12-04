################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../external/gtest/gtest-all.cc 

OBJS += \
./external/gtest/gtest-all.o 

CC_DEPS += \
./external/gtest/gtest-all.d 


# Each subdirectory must supply rules for building sources it contributes
external/gtest/%.o: ../external/gtest/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"../external" -O3 -g3 -c -fmessage-length=0 -Wsign-compare -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


