################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/AllTests.cpp 

OBJS += \
./test/AllTests.o 

CPP_DEPS += \
./test/AllTests.d 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -I"/home/prashantm/ray-tracer/CS410/OpenMP/external" -I"/home/prashantm/ray-tracer/CS410/OpenMP/include" -I"/home/prashantm/ray-tracer/CS410/OpenMP/src" -O3 -c -fmessage-length=0 -Wsign-compare -std=c++11 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


