#
# Auto-Generated file. Do not edit!
#

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../libc/stdio/printf.c \
../libc/stdio/sscanf.c

OBJS += \
./libc/stdio/printf.o \
./libc/stdio/sscanf.o

C_DEPS += \
./libc/stdio/printf.d \
./libc/stdio/sscanf.d

# Each subdirectory must supply rules for building sources it contributes
libc/stdio/%.o: ../libc/stdio/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: RTEMS C Compiler'
	D:/LoongIDE/rtems-4.10/bin/mips-rtems4.10-gcc.exe -mips32 -G0 -EL -msoft-float -DLS1B -DOS_NONE  -O0 -g -Wall -c -fmessage-length=0 -pipe -I"../" -I"../include" -I"../core/include" -I"../core/mips" -I"../ls1x-drv/include" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

