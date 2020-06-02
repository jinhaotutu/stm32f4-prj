################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/share/samba/tuya/my_prj/stm32f4-prj/sys/sys_cfg.c \
/home/share/samba/tuya/my_prj/stm32f4-prj/sys/sys_delay.c 

OBJS += \
./sys/sys_cfg.o \
./sys/sys_delay.o 

C_DEPS += \
./sys/sys_cfg.d \
./sys/sys_delay.d 


# Each subdirectory must supply rules for building sources it contributes
sys/sys_cfg.o: /home/share/samba/tuya/my_prj/stm32f4-prj/sys/sys_cfg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"sys/sys_cfg.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
sys/sys_delay.o: /home/share/samba/tuya/my_prj/stm32f4-prj/sys/sys_delay.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F4 -DDEBUG -DSTM32F407ZGTx -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -c -I../../fwlib/inc -I../../misis -I../../sys -I../../user -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"sys/sys_delay.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

