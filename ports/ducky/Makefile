include ../../py/mkenv.mk

DUCKY_TOOLCHAIN_ROOT ?= /opt/ducky

CC := $(DUCKY_TOOLCHAIN_ROOT)/bin/clang
LD := $(DUCKY_TOOLCHAIN_ROOT)/bin/ld.lld

LIBDUCKY_LIB ?= $(DUCKY_TOOLCHAIN_ROOT)/lib/libducky.a
LIBDUCKY_INCLUDES ?= $(DUCKY_TOOLCHAIN_ROOT)/usr/include

# qstr definitions (must come before including py.mk
QSTR_DEFS = qstrdefsport.h

# include py core make definitions
include $(TOP)/py/py.mk

INC += -isystem $(LIBDUCKY_INCLUDES)
INC += -I$(TOP)
INC += -I$(TOP)/ports/ducky
INC += -I$(BUILD)

CFLAGS := -nostdinc $(INC) \
	        -Wall \
					-ansi -std=gnu99 \
					-nostdlib -fno-builtin \
					-O2 -fno-inline-functions -mllvm -disable-tail-duplicate -mllvm -disable-early-taildup \
					-ffunction-sections -fdata-sections \
					$(COPT) \
					$(CFLAGS)

LDFLAGS := --no-threads \
	         -nostdlib \
					 --script=./micropython.ld \
					 -static \
					 --gc-sections \
					 $(LDFLAGS)

ifeq ($(DEBUG), 1)
CFLAGS += -DDEBUG -O0
else
CFLAGS += -DNDEBUG -O2
endif

SRC_C = \
	main.c \
	uart_core.c \
	modmachine.c \
	$(TOP)/lib/mp-readline/readline.c \
	$(TOP)/lib/utils/pyexec.c \
	$(TOP)/lib/utils/stdout_helpers.c

SRC_QSTR += $(SRC_C)

OBJ = $(PY_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o)) \
			lowlevel.o

$(BUILD)/firmware: $(OBJ) micropython.ld
	$(LD) $(LDFLAGS) -o $@ $(LIBDUCKY_LIB) $(OBJ)

firmware: $(BUILD)/firmware

lowlevel.o: lowlevel.S mpconfigport.h
	$(CC) -c $(CFLAGS) -o $@ $<

include $(TOP)/py/mkrules.mk
