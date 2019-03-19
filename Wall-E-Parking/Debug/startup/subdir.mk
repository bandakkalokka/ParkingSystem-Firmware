################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../startup/startup_stm32.s 

OBJS += \
./startup/startup_stm32.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.s
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Assembler'
	@echo $(PWD)
	arm-none-eabi-as -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -I"/Users/Sara/Desktop/ENEL400_2/wallE/ParkingSystem-Firmware/Wall-E-Parking/HAL_Driver/Inc/Legacy" -I"/Users/Sara/Desktop/ENEL400_2/wallE/ParkingSystem-Firmware/Wall-E-Parking/inc" -I"/Users/Sara/Desktop/ENEL400_2/wallE/ParkingSystem-Firmware/Wall-E-Parking/CMSIS/device" -I"/Users/Sara/Desktop/ENEL400_2/wallE/ParkingSystem-Firmware/Wall-E-Parking/CMSIS/core" -I"/Users/Sara/Desktop/ENEL400_2/wallE/ParkingSystem-Firmware/Wall-E-Parking/HAL_Driver/Inc" -g -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


