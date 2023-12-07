TARGET:=main.elf

CC:=arm-none-eabi-gcc

BUILD_DIR:=./Build
OBJ_DIR:= $(BUILD_DIR)/obj

SRC_DIR:= .
INC_DIR:= .

SRC:=$(shell find $(SRC_DIR) -name '*.c')
INC:=$(shell find $(INC_DIR) -type d)

OBJ:=$(patsubst %.c,%.o,$(SRC))
OBJS:= $(addprefix $(OBJ_DIR)/,$(OBJ))

CPPFLAGS:= $(addprefix -I,$(INC))
CFLAGS:= -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -std=gnu11 -Wall --save-temps #-mabi=aapcs

LDFLAGS:= -mcpu=cortex-m4 -mthumb -mfloat-abi=soft --specs=nano.specs -T stm32_linker_script.ld -Wl,-Map=$(BUILD_DIR)/main.map #-nostdlib
#LDFLAGS:= -mcpu=cortex-m4 -mthumb -mfloat-abi=soft --specs=rdimon.specs -T stm32_linker_script.ld -Wl,-Map=main.map #-nostdlib --specs=nano.specs

$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $^ -o $@

load:
	openocd -f board/st_nucleo_f4.cfg #board/stm32f4discovery.cfg

.PHONY:= clean

clean:
	rm -rf $(BUILD_DIR)