################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/CarMove.c \
../APP/Eyes.c \
../APP/LineFollower.c \
../APP/ModesHandler.c 

OBJS += \
./APP/CarMove.o \
./APP/Eyes.o \
./APP/LineFollower.o \
./APP/ModesHandler.o 

C_DEPS += \
./APP/CarMove.d \
./APP/Eyes.d \
./APP/LineFollower.d \
./APP/ModesHandler.d 


# Each subdirectory must supply rules for building sources it contributes
APP/%.o: ../APP/%.c APP/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


