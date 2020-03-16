################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../user/main.c \
../user/stm32f4xx_it.c 

OBJS += \
./user/main.o \
./user/stm32f4xx_it.o 

C_DEPS += \
./user/main.d \
./user/stm32f4xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
user/main.o: ../user/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"user/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
user/stm32f4xx_it.o: ../user/stm32f4xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"user/stm32f4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

