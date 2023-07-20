################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/stm32f0xx_hal_msp.c \
../Core/Src/stm32f0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f0xx.c 

CPP_SRCS += \
../Core/Src/Button.cpp \
../Core/Src/DateTimeScreen.cpp \
../Core/Src/OneColMenuScreen.cpp \
../Core/Src/Screen.cpp \
../Core/Src/TwoColMenuScreen.cpp \
../Core/Src/TwoColScreen.cpp \
../Core/Src/lcd_i2c_lib.cpp \
../Core/Src/main.cpp \
../Core/Src/rtc.cpp \
../Core/Src/timer.cpp 

C_DEPS += \
./Core/Src/stm32f0xx_hal_msp.d \
./Core/Src/stm32f0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f0xx.d 

OBJS += \
./Core/Src/Button.o \
./Core/Src/DateTimeScreen.o \
./Core/Src/OneColMenuScreen.o \
./Core/Src/Screen.o \
./Core/Src/TwoColMenuScreen.o \
./Core/Src/TwoColScreen.o \
./Core/Src/lcd_i2c_lib.o \
./Core/Src/main.o \
./Core/Src/rtc.o \
./Core/Src/stm32f0xx_hal_msp.o \
./Core/Src/stm32f0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f0xx.o \
./Core/Src/timer.o 

CPP_DEPS += \
./Core/Src/Button.d \
./Core/Src/DateTimeScreen.d \
./Core/Src/OneColMenuScreen.d \
./Core/Src/Screen.d \
./Core/Src/TwoColMenuScreen.d \
./Core/Src/TwoColScreen.d \
./Core/Src/lcd_i2c_lib.d \
./Core/Src/main.d \
./Core/Src/rtc.d \
./Core/Src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.cpp Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m0 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x8 -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F030x8 -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Button.cyclo ./Core/Src/Button.d ./Core/Src/Button.o ./Core/Src/Button.su ./Core/Src/DateTimeScreen.cyclo ./Core/Src/DateTimeScreen.d ./Core/Src/DateTimeScreen.o ./Core/Src/DateTimeScreen.su ./Core/Src/OneColMenuScreen.cyclo ./Core/Src/OneColMenuScreen.d ./Core/Src/OneColMenuScreen.o ./Core/Src/OneColMenuScreen.su ./Core/Src/Screen.cyclo ./Core/Src/Screen.d ./Core/Src/Screen.o ./Core/Src/Screen.su ./Core/Src/TwoColMenuScreen.cyclo ./Core/Src/TwoColMenuScreen.d ./Core/Src/TwoColMenuScreen.o ./Core/Src/TwoColMenuScreen.su ./Core/Src/TwoColScreen.cyclo ./Core/Src/TwoColScreen.d ./Core/Src/TwoColScreen.o ./Core/Src/TwoColScreen.su ./Core/Src/lcd_i2c_lib.cyclo ./Core/Src/lcd_i2c_lib.d ./Core/Src/lcd_i2c_lib.o ./Core/Src/lcd_i2c_lib.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/rtc.cyclo ./Core/Src/rtc.d ./Core/Src/rtc.o ./Core/Src/rtc.su ./Core/Src/stm32f0xx_hal_msp.cyclo ./Core/Src/stm32f0xx_hal_msp.d ./Core/Src/stm32f0xx_hal_msp.o ./Core/Src/stm32f0xx_hal_msp.su ./Core/Src/stm32f0xx_it.cyclo ./Core/Src/stm32f0xx_it.d ./Core/Src/stm32f0xx_it.o ./Core/Src/stm32f0xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f0xx.cyclo ./Core/Src/system_stm32f0xx.d ./Core/Src/system_stm32f0xx.o ./Core/Src/system_stm32f0xx.su ./Core/Src/timer.cyclo ./Core/Src/timer.d ./Core/Src/timer.o ./Core/Src/timer.su

.PHONY: clean-Core-2f-Src

