################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../misis/system_stm32f4xx.c 

OBJS += \
./misis/system_stm32f4xx.o 

C_DEPS += \
./misis/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
misis/system_stm32f4xx.o: ../misis/system_stm32f4xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"misis/system_stm32f4xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

