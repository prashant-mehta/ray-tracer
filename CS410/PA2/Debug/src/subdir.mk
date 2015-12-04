################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/CreateTriangles.cpp \
../src/Face.cpp \
../src/Foo.cpp \
../src/MatrixOperations.cpp \
../src/ParseCameraModel.cpp \
../src/ParsePly.cpp \
../src/ParsePlyAttributes.cpp \
../src/Pixel.cpp \
../src/ProjectionMatrix.cpp \
../src/Silhouette.cpp \
../src/SphereIntersection.cpp \
../src/Transformation.cpp \
../src/TransformationMatrices.cpp \
../src/VectorOperations.cpp \
../src/Vertex.cpp \
../src/WritePly.cpp \
../src/WritePpm.cpp 

OBJS += \
./src/CreateTriangles.o \
./src/Face.o \
./src/Foo.o \
./src/MatrixOperations.o \
./src/ParseCameraModel.o \
./src/ParsePly.o \
./src/ParsePlyAttributes.o \
./src/Pixel.o \
./src/ProjectionMatrix.o \
./src/Silhouette.o \
./src/SphereIntersection.o \
./src/Transformation.o \
./src/TransformationMatrices.o \
./src/VectorOperations.o \
./src/Vertex.o \
./src/WritePly.o \
./src/WritePpm.o 

CPP_DEPS += \
./src/CreateTriangles.d \
./src/Face.d \
./src/Foo.d \
./src/MatrixOperations.d \
./src/ParseCameraModel.d \
./src/ParsePly.d \
./src/ParsePlyAttributes.d \
./src/Pixel.d \
./src/ProjectionMatrix.d \
./src/Silhouette.d \
./src/SphereIntersection.d \
./src/Transformation.d \
./src/TransformationMatrices.d \
./src/VectorOperations.d \
./src/Vertex.d \
./src/WritePly.d \
./src/WritePpm.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/prashantm/repo/CS410/PA2/include" -O3 -g3 -c -fmessage-length=0 -Wsign-compare -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


