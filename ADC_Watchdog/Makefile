DIR_StdPeriph ?= $(HOME)/stm32lib
STD_PERIPH_LIBS ?= $(DIR_StdPeriph)/STM32F10x_StdPeriph_Lib_V3.5.0
GCC_PATH ?= 

# name for output binary files
PROJECT ?= ADC_Watchdog

SRCDIR = sources
USERDIR = ../user
# list of source files
SOURCES += $(shell find $(SRCDIR) -name '*.c')
SOURCES += $(shell find $(STD_PERIPH_LIBS)/Libraries/STM32F10x_StdPeriph_Driver/src -name '*.c')

SOURCES += $(USERDIR)/delay.c
SOURCES += $(USERDIR)/syscalls.c

SOURCES += $(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/system_stm32f10x.c
SOURCES += $(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x/startup/TrueSTUDIO/startup_stm32f10x_md.s

# compiler, objcopy (should be in GCC_PATH)
PREFIX = arm-none-eabi-
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif

# path to st-flash (or should be specified in PATH)
ST_FLASH ?= st-flash

# specify compiler flags
CFLAGS  = -O2 -g -Wall -Wno-unused-variable
CFLAGS += -T$(STD_PERIPH_LIBS)/Project/STM32F10x_StdPeriph_Template/TrueSTUDIO/STM3210B-EVAL/stm32_flash.ld
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m3 -mthumb-interwork --specs=rdimon.specs  -specs=nano.specs   
CFLAGS += -mfloat-abi=soft  -lgcc -lc -lm 
CFLAGS += -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -MD
CFLAGS += -Wl,-Map=$(PROJECT).map,--gc-sections
CFLAGS += -I $(SRCDIR)
CFLAGS += -I $(USERDIR)
CFLAGS += -I $(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
CFLAGS += -I $(STD_PERIPH_LIBS)/Libraries/CMSIS/CM3/CoreSupport
CFLAGS += -I $(STD_PERIPH_LIBS)/Libraries/STM32F10x_StdPeriph_Driver/inc

OBJS = $(SOURCES:.c=.o)

all: $(PROJECT).elf

# compile
$(PROJECT).elf: $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@
	$(CP) -O ihex $(PROJECT).elf   $(PROJECT).hex
	$(CP) -O binary $(PROJECT).elf $(PROJECT).bin 
	@echo $(PROJECT).bin "file size is (kB) :" 
	@stat -L -c %s $(PROJECT).bin
	@$(SZ) $(PROJECT).elf

# remove binary files
clean:
	@echo "************************************"
	@echo -e '\e[91mCLEANING SOLUTIONS\e[39m'
	@echo "------------------------------------"
	@rm -f $(PROJECT).*
	@echo Done!

# flash
flash:
	@echo "************************************"
	@echo -e '\e[5mBURNING\e[25m'
	@echo "------------------------------------"
	$(ST_FLASH) --reset write $(PROJECT).bin 0x8000000
	@echo Done !
erase:
	@echo "************************************"
	@echo -e '\e[91mFLASH ERASE\e[39m'
	@echo "------------------------------------"
	@$(ST_FLASH) erase 
	@echo Done!
deploy:
	@echo "************************************"
	@echo -e '\e[5mDEPLOY SEQUENCE INITIALIZED\e[25m'
	@echo "------------------------------------"
	@make clean && make all && make burn
debug:
	@echo "************************************"
	@echo "DEBUG INTERFACE"
	@echo "------------------------------------"
	@arm-none-eabi-gdb $(PROJECT).elf

	

	

