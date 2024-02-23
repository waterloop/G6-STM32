################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/mahir/Desktop/Waterloop/G6-STM32/Common/Src/can_driver.c 

OBJS += \
./Common/Src/can_driver.o 

C_DEPS += \
./Common/Src/can_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Common/Src/can_driver.o: C:/Users/mahir/Desktop/Waterloop/G6-STM32/Common/Src/can_driver.c Common/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mahir/Desktop/Waterloop/G6-STM32/Common/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Common-2f-Src

clean-Common-2f-Src:
	-$(RM) ./Common/Src/can_driver.cyclo ./Common/Src/can_driver.d ./Common/Src/can_driver.o ./Common/Src/can_driver.su

.PHONY: clean-Common-2f-Src

