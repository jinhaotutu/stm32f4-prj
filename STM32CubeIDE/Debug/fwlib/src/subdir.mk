################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fwlib/src/misc.c \
../fwlib/src/stm32f4xx_adc.c \
../fwlib/src/stm32f4xx_can.c \
../fwlib/src/stm32f4xx_cec.c \
../fwlib/src/stm32f4xx_crc.c \
../fwlib/src/stm32f4xx_dac.c \
../fwlib/src/stm32f4xx_dcmi.c \
../fwlib/src/stm32f4xx_dma.c \
../fwlib/src/stm32f4xx_dsi.c \
../fwlib/src/stm32f4xx_exti.c \
../fwlib/src/stm32f4xx_flash.c \
../fwlib/src/stm32f4xx_fsmc.c \
../fwlib/src/stm32f4xx_gpio.c \
../fwlib/src/stm32f4xx_hash.c \
../fwlib/src/stm32f4xx_i2c.c \
../fwlib/src/stm32f4xx_iwdg.c \
../fwlib/src/stm32f4xx_lptim.c \
../fwlib/src/stm32f4xx_ltdc.c \
../fwlib/src/stm32f4xx_pwr.c \
../fwlib/src/stm32f4xx_qspi.c \
../fwlib/src/stm32f4xx_rcc.c \
../fwlib/src/stm32f4xx_rng.c \
../fwlib/src/stm32f4xx_rtc.c \
../fwlib/src/stm32f4xx_sai.c \
../fwlib/src/stm32f4xx_sdio.c \
../fwlib/src/stm32f4xx_spdifrx.c \
../fwlib/src/stm32f4xx_spi.c \
../fwlib/src/stm32f4xx_syscfg.c \
../fwlib/src/stm32f4xx_tim.c \
../fwlib/src/stm32f4xx_usart.c \
../fwlib/src/stm32f4xx_wwdg.c 

OBJS += \
./fwlib/src/misc.o \
./fwlib/src/stm32f4xx_adc.o \
./fwlib/src/stm32f4xx_can.o \
./fwlib/src/stm32f4xx_cec.o \
./fwlib/src/stm32f4xx_crc.o \
./fwlib/src/stm32f4xx_dac.o \
./fwlib/src/stm32f4xx_dcmi.o \
./fwlib/src/stm32f4xx_dma.o \
./fwlib/src/stm32f4xx_dsi.o \
./fwlib/src/stm32f4xx_exti.o \
./fwlib/src/stm32f4xx_flash.o \
./fwlib/src/stm32f4xx_fsmc.o \
./fwlib/src/stm32f4xx_gpio.o \
./fwlib/src/stm32f4xx_hash.o \
./fwlib/src/stm32f4xx_i2c.o \
./fwlib/src/stm32f4xx_iwdg.o \
./fwlib/src/stm32f4xx_lptim.o \
./fwlib/src/stm32f4xx_ltdc.o \
./fwlib/src/stm32f4xx_pwr.o \
./fwlib/src/stm32f4xx_qspi.o \
./fwlib/src/stm32f4xx_rcc.o \
./fwlib/src/stm32f4xx_rng.o \
./fwlib/src/stm32f4xx_rtc.o \
./fwlib/src/stm32f4xx_sai.o \
./fwlib/src/stm32f4xx_sdio.o \
./fwlib/src/stm32f4xx_spdifrx.o \
./fwlib/src/stm32f4xx_spi.o \
./fwlib/src/stm32f4xx_syscfg.o \
./fwlib/src/stm32f4xx_tim.o \
./fwlib/src/stm32f4xx_usart.o \
./fwlib/src/stm32f4xx_wwdg.o 

C_DEPS += \
./fwlib/src/misc.d \
./fwlib/src/stm32f4xx_adc.d \
./fwlib/src/stm32f4xx_can.d \
./fwlib/src/stm32f4xx_cec.d \
./fwlib/src/stm32f4xx_crc.d \
./fwlib/src/stm32f4xx_dac.d \
./fwlib/src/stm32f4xx_dcmi.d \
./fwlib/src/stm32f4xx_dma.d \
./fwlib/src/stm32f4xx_dsi.d \
./fwlib/src/stm32f4xx_exti.d \
./fwlib/src/stm32f4xx_flash.d \
./fwlib/src/stm32f4xx_fsmc.d \
./fwlib/src/stm32f4xx_gpio.d \
./fwlib/src/stm32f4xx_hash.d \
./fwlib/src/stm32f4xx_i2c.d \
./fwlib/src/stm32f4xx_iwdg.d \
./fwlib/src/stm32f4xx_lptim.d \
./fwlib/src/stm32f4xx_ltdc.d \
./fwlib/src/stm32f4xx_pwr.d \
./fwlib/src/stm32f4xx_qspi.d \
./fwlib/src/stm32f4xx_rcc.d \
./fwlib/src/stm32f4xx_rng.d \
./fwlib/src/stm32f4xx_rtc.d \
./fwlib/src/stm32f4xx_sai.d \
./fwlib/src/stm32f4xx_sdio.d \
./fwlib/src/stm32f4xx_spdifrx.d \
./fwlib/src/stm32f4xx_spi.d \
./fwlib/src/stm32f4xx_syscfg.d \
./fwlib/src/stm32f4xx_tim.d \
./fwlib/src/stm32f4xx_usart.d \
./fwlib/src/stm32f4xx_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
fwlib/src/misc.o: ../fwlib/src/misc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/misc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_adc.o: ../fwlib/src/stm32f4xx_adc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_adc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_can.o: ../fwlib/src/stm32f4xx_can.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_can.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_cec.o: ../fwlib/src/stm32f4xx_cec.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_cec.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_crc.o: ../fwlib/src/stm32f4xx_crc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_crc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_dac.o: ../fwlib/src/stm32f4xx_dac.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_dac.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_dcmi.o: ../fwlib/src/stm32f4xx_dcmi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_dcmi.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_dma.o: ../fwlib/src/stm32f4xx_dma.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_dma.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_dsi.o: ../fwlib/src/stm32f4xx_dsi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_dsi.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_exti.o: ../fwlib/src/stm32f4xx_exti.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_exti.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_flash.o: ../fwlib/src/stm32f4xx_flash.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_flash.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_fsmc.o: ../fwlib/src/stm32f4xx_fsmc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_fsmc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_gpio.o: ../fwlib/src/stm32f4xx_gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_gpio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_hash.o: ../fwlib/src/stm32f4xx_hash.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_hash.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_i2c.o: ../fwlib/src/stm32f4xx_i2c.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_i2c.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_iwdg.o: ../fwlib/src/stm32f4xx_iwdg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_iwdg.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_lptim.o: ../fwlib/src/stm32f4xx_lptim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_lptim.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_ltdc.o: ../fwlib/src/stm32f4xx_ltdc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_ltdc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_pwr.o: ../fwlib/src/stm32f4xx_pwr.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_pwr.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_qspi.o: ../fwlib/src/stm32f4xx_qspi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_qspi.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_rcc.o: ../fwlib/src/stm32f4xx_rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_rcc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_rng.o: ../fwlib/src/stm32f4xx_rng.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_rng.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_rtc.o: ../fwlib/src/stm32f4xx_rtc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_rtc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_sai.o: ../fwlib/src/stm32f4xx_sai.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_sai.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_sdio.o: ../fwlib/src/stm32f4xx_sdio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_sdio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_spdifrx.o: ../fwlib/src/stm32f4xx_spdifrx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_spdifrx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_spi.o: ../fwlib/src/stm32f4xx_spi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_spi.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_syscfg.o: ../fwlib/src/stm32f4xx_syscfg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_syscfg.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_tim.o: ../fwlib/src/stm32f4xx_tim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_tim.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_usart.o: ../fwlib/src/stm32f4xx_usart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_usart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_wwdg.o: ../fwlib/src/stm32f4xx_wwdg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/fwlib/inc" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/misis" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/sys" -I"D:/data/my_prj/stm32f4-prj/STM32CubeIDE/user" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_wwdg.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

