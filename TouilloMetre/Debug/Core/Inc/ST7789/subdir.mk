################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/ST7789/fonts.c \
../Core/Inc/ST7789/st7789.c 

C_DEPS += \
./Core/Inc/ST7789/fonts.d \
./Core/Inc/ST7789/st7789.d 

OBJS += \
./Core/Inc/ST7789/fonts.o \
./Core/Inc/ST7789/st7789.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/ST7789/%.o Core/Inc/ST7789/%.su Core/Inc/ST7789/%.cyclo: ../Core/Inc/ST7789/%.c Core/Inc/ST7789/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L053xx -c -I../Core/Inc -I../Core/Inc/ST7789 -I/home/victorx1/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc -I/home/victorx1/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I/home/victorx1/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Device/ST/STM32L0xx/Include -I/home/victorx1/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Drivers/CMSIS/Include -I../FATFS/Target -I../FATFS/App -I/home/victorx1/STM32Cube/Repository/STM32Cube_FW_L0_V1.12.2/Middlewares/Third_Party/FatFs/src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-ST7789

clean-Core-2f-Inc-2f-ST7789:
	-$(RM) ./Core/Inc/ST7789/fonts.cyclo ./Core/Inc/ST7789/fonts.d ./Core/Inc/ST7789/fonts.o ./Core/Inc/ST7789/fonts.su ./Core/Inc/ST7789/st7789.cyclo ./Core/Inc/ST7789/st7789.d ./Core/Inc/ST7789/st7789.o ./Core/Inc/ST7789/st7789.su

.PHONY: clean-Core-2f-Inc-2f-ST7789

