TARGET:=main.elf

CC:=arm-none-eabi-gcc

BUILD_DIR:=./Build
OBJ_DIR:= $(BUILD_DIR)/obj

ifndef ARM_SEMIHOSTING
	ARM_SEMIHOSTING := Disable #Enable
endif

SRC_DIR:= .
INC_DIR:= .

ifeq ($(ARM_SEMIHOSTING), Enable)
	SRC:=$(shell find $(SRC_DIR) ! -name 'syscalls.c' -name '*.c') #this way we can exclude certain src files individually
	#SRC:=$(shell find $(SRC_DIR) -name '*.c')
	#SRCS:=$(filter-out ./sycalls.c, $(SRC))  #do something similar as above line but requires $(SRC) definition and need to provide complete path for the file to be exclude unlike above cmd
else
	SRC:=$(shell find $(SRC_DIR) -name '*.c')
endif


INC:=$(shell find $(INC_DIR) -type d)

OBJ:=$(patsubst %.c,%.o,$(SRC))
OBJS:= $(addprefix $(OBJ_DIR)/,$(OBJ))

CPPFLAGS:= $(addprefix -I,$(INC))
CFLAGS:= -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -std=gnu11 -Wall --save-temps #-mabi=aapcs

ifeq ($(ARM_SEMIHOSTING), Enable)
	LDFLAGS:= -mcpu=cortex-m4 -mthumb -mfloat-abi=soft --specs=rdimon.specs  -T stm32_linker_script.ld -Wl,-Map=main.map #-nostdlib -lc -lrdimon
else
	LDFLAGS:= -mcpu=cortex-m4 -mthumb -mfloat-abi=soft --specs=nano.specs -T stm32_linker_script.ld -Wl,-Map=$(BUILD_DIR)/main.map #-nostdlib
endif

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJS)
	@echo "ARM_SEMIHOSTING = "$(ARM_SEMIHOSTING)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $^ -o $@

load:
	openocd -f board/st_nucleo_f4.cfg #board/stm32f4discovery.cfg

.PHONY:= clean

clean:
	rm -rf $(BUILD_DIR)