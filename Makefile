CC:=gcc
CFLAGS:=-std=c99 -Wall -Werror
LDFLAGS:=

DEBUG:=false

# make DEBUG=true emits debug info
ifeq ($(DEBUG),true)
	CFLAGS:=$(CFLAGS) -g
endif

# used for filename of output program
NAME:=main

MKF_PATH :=$(abspath $(lastword $(MAKEFILE_LIST)))
MKF_DIR:=$(patsubst %/,%,$(dir $(MKF_PATH))) # dir leaves a trailing /
MKF_DIR:=$(strip $(MKF_DIR))

# absolute paths to dirs
BIN:=$(MKF_DIR)/bin
OBJ:=$(MKF_DIR)/obj
SRC:=$(MKF_DIR)

HEADERS:=bytestr.h p6_data.h pixel.h strbuilder.h sys_headers.h
H_PATHS:=$(HEADERS:%=$(SRC)/%)

SOURCES:=bytestr.c main.c strbuilder.c
S_PATHS:=$(SOURCES:%=$(SRC)/%)

OBJECTS:=$(SOURCES:.c=.o)
O_PATHS:=$(OBJECTS:%=$(OBJ)/%)

# path to output lib/exe
OUTPUT:=$(BIN)/$(NAME)

ifeq ($(OS),Windows_NT)
	OUTPUT:=$(OUTPUT).exe
endif

.PHONY: all clean print-%

all: $(OUTPUT)

clean:
	rm -rf $(BIN) $(OBJ)

# useful for debugging
# usage: print-VARNAME
print-%:
	@echo $*=$($*) # $* matches the stem of a pattern rule

$(BIN):
	@mkdir -p $@

$(O_PATHS): $(OBJ)/%.o: $(SRC)/%.c $(H_PATHS) | $(OBJ)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ):
	@mkdir -p $@

$(OUTPUT): $(O_PATHS) | $(BIN)
	$(CC) $(LDFLAGS) -o $@ $(O_PATHS)
