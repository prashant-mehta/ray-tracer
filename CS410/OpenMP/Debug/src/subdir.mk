################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Casting.cpp \
../src/CreateTriangles.cpp \
../src/Face.cpp \
../src/FaceProperties.cpp \
../src/Foo.cpp \
../src/LightSource.cpp \
../src/MatrixOperations.cpp \
../src/ParseCameraModel.cpp \
../src/ParseMaterials.cpp \
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
./src/Casting.o \
./src/CreateTriangles.o \
./src/Face.o \
./src/FaceProperties.o \
./src/Foo.o \
./src/LightSource.o \
./src/MatrixOperations.o \
./src/ParseCameraModel.o \
./src/ParseMaterials.o \
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
./src/Casting.d \
./src/CreateTriangles.d \
./src/Face.d \
./src/FaceProperties.d \
./src/Foo.d \
./src/LightSource.d \
./src/MatrixOperations.d \
./src/ParseCameraModel.d \
./src/ParseMaterials.d \
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
	g++ -std=c++0x -I"/home/prashantm/ray-tracer/CS410/PA4/include" -O3 -g3 -ftest-coverage -fprofile-arcs -c -fmessage-length=0 -Wsign-compare -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


