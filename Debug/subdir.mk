################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Applications.c \
../dcMotor.c \
../gpio.c \
../interrupt.c \
../led.c \
../pushButton.c \
../sevenSeg.c \
../softwareDelay.c \
../timers.c 

OBJS += \
./Applications.o \
./dcMotor.o \
./gpio.o \
./interrupt.o \
./led.o \
./pushButton.o \
./sevenSeg.o \
./softwareDelay.o \
./timers.o 

C_DEPS += \
./Applications.d \
./dcMotor.d \
./gpio.d \
./interrupt.d \
./led.d \
./pushButton.d \
./sevenSeg.d \
./softwareDelay.d \
./timers.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


