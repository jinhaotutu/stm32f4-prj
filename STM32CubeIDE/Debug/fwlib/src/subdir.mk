################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/misc.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_adc.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_can.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_crc.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_dac.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_dcmi.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_dma.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_exti.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_flash.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_fsmc.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_gpio.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_hash.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_i2c.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_iwdg.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_pwr.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_rcc.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_rtc.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_sdio.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_spi.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_syscfg.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_tim.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_usart.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_wwdg.c 

OBJS += \
./fwlib/src/misc.o \
./fwlib/src/stm32f4xx_adc.o \
./fwlib/src/stm32f4xx_can.o \
./fwlib/src/stm32f4xx_crc.o \
./fwlib/src/stm32f4xx_dac.o \
./fwlib/src/stm32f4xx_dcmi.o \
./fwlib/src/stm32f4xx_dma.o \
./fwlib/src/stm32f4xx_exti.o \
./fwlib/src/stm32f4xx_flash.o \
./fwlib/src/stm32f4xx_fsmc.o \
./fwlib/src/stm32f4xx_gpio.o \
./fwlib/src/stm32f4xx_hash.o \
./fwlib/src/stm32f4xx_i2c.o \
./fwlib/src/stm32f4xx_iwdg.o \
./fwlib/src/stm32f4xx_pwr.o \
./fwlib/src/stm32f4xx_rcc.o \
./fwlib/src/stm32f4xx_rtc.o \
./fwlib/src/stm32f4xx_sdio.o \
./fwlib/src/stm32f4xx_spi.o \
./fwlib/src/stm32f4xx_syscfg.o \
./fwlib/src/stm32f4xx_tim.o \
./fwlib/src/stm32f4xx_usart.o \
./fwlib/src/stm32f4xx_wwdg.o 

C_DEPS += \
./fwlib/src/misc.d \
./fwlib/src/stm32f4xx_adc.d \
./fwlib/src/stm32f4xx_can.d \
./fwlib/src/stm32f4xx_crc.d \
./fwlib/src/stm32f4xx_dac.d \
./fwlib/src/stm32f4xx_dcmi.d \
./fwlib/src/stm32f4xx_dma.d \
./fwlib/src/stm32f4xx_exti.d \
./fwlib/src/stm32f4xx_flash.d \
./fwlib/src/stm32f4xx_fsmc.d \
./fwlib/src/stm32f4xx_gpio.d \
./fwlib/src/stm32f4xx_hash.d \
./fwlib/src/stm32f4xx_i2c.d \
./fwlib/src/stm32f4xx_iwdg.d \
./fwlib/src/stm32f4xx_pwr.d \
./fwlib/src/stm32f4xx_rcc.d \
./fwlib/src/stm32f4xx_rtc.d \
./fwlib/src/stm32f4xx_sdio.d \
./fwlib/src/stm32f4xx_spi.d \
./fwlib/src/stm32f4xx_syscfg.d \
./fwlib/src/stm32f4xx_tim.d \
./fwlib/src/stm32f4xx_usart.d \
./fwlib/src/stm32f4xx_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
fwlib/src/misc.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/misc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/misc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_adc.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_adc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_adc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_can.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_can.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_can.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_crc.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_crc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_crc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_dac.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_dac.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_dac.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_dcmi.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_dcmi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_dcmi.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_dma.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_dma.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_dma.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_exti.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_exti.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_exti.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_flash.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_flash.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_flash.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_fsmc.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_fsmc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_fsmc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_gpio.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_gpio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_hash.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_hash.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_hash.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_i2c.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_i2c.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_i2c.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_iwdg.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_iwdg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_iwdg.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_pwr.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_pwr.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_pwr.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_rcc.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_rcc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_rcc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_rtc.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_rtc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_rtc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_sdio.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_sdio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_sdio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_spi.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_spi.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_spi.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_syscfg.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_syscfg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_syscfg.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_tim.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_tim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_tim.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_usart.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_usart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_usart.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
fwlib/src/stm32f4xx_wwdg.o: /home/share/samba/tuya/my_prj/stm32f4-prj/fwlib/src/stm32f4xx_wwdg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"fwlib/src/stm32f4xx_wwdg.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

