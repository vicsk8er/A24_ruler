################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/ADXL343.cpp \
../Core/Src/EventLogger.cpp \
../Core/Src/HTU21D.cpp \
../Core/Src/I2CHandler.cpp \
../Core/Src/VL53L0X.cpp \
../Core/Src/main.cpp 

C_SRCS += \
../Core/Src/fatfs_sd.c \
../Core/Src/stm32l0xx_hal_msp.c \
../Core/Src/stm32l0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32l0xx.c 

C_DEPS += \
./Core/Src/fatfs_sd.d \
./Core/Src/stm32l0xx_hal_msp.d \
./Core/Src/stm32l0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32l0xx.d 

OBJS += \
./Core/Src/ADXL343.o \
./Core/Src/EventLogger.o \
./Core/Src/HTU21D.o \
./Core/Src/I2CHandler.o \
./Core/Src/VL53L0X.o \
./Core/Src/fatfs_sd.o \
./Core/Src/main.o \
./Core/Src/stm32l0xx_hal_msp.o \
./Core/Src/stm32l0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32l0xx.o 

CPP_DEPS += \
./Core/Src/ADXL343.d \
./Core/Src/EventLogger.d \
./Core/Src/HTU21D.d \
./Core/Src/I2CHandler.d \
./Core/Src/VL53L0X.d \
./Core/Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0plus -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L053xx -c -I../Core/Inc -I/home/victorx1/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -I/home/victorx1/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I/home/victorx1/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -I/home/victorx1/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I/home/victorx1/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L053xx -c -I../Core/Inc -I/home/victorx1/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -I/home/victorx1/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I/home/victorx1/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -I/home/victorx1/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I/home/victorx1/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ADXL343.cyclo ./Core/Src/ADXL343.d ./Core/Src/ADXL343.o ./Core/Src/ADXL343.su ./Core/Src/EventLogger.cyclo ./Core/Src/EventLogger.d ./Core/Src/EventLogger.o ./Core/Src/EventLogger.su ./Core/Src/HTU21D.cyclo ./Core/Src/HTU21D.d ./Core/Src/HTU21D.o ./Core/Src/HTU21D.su ./Core/Src/I2CHandler.cyclo ./Core/Src/I2CHandler.d ./Core/Src/I2CHandler.o ./Core/Src/I2CHandler.su ./Core/Src/VL53L0X.cyclo ./Core/Src/VL53L0X.d ./Core/Src/VL53L0X.o ./Core/Src/VL53L0X.su ./Core/Src/fatfs_sd.cyclo ./Core/Src/fatfs_sd.d ./Core/Src/fatfs_sd.o ./Core/Src/fatfs_sd.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32l0xx_hal_msp.cyclo ./Core/Src/stm32l0xx_hal_msp.d ./Core/Src/stm32l0xx_hal_msp.o ./Core/Src/stm32l0xx_hal_msp.su ./Core/Src/stm32l0xx_it.cyclo ./Core/Src/stm32l0xx_it.d ./Core/Src/stm32l0xx_it.o ./Core/Src/stm32l0xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32l0xx.cyclo ./Core/Src/system_stm32l0xx.d ./Core/Src/system_stm32l0xx.o ./Core/Src/system_stm32l0xx.su

.PHONY: clean-Core-2f-Src

