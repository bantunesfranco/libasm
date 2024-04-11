RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
CYAN=\033[1;36m
END=\033[0m

NAME = libasm.a

ASM = nasm
ASM_FLAGS = -f elf64 -F dwarf -g

AR = ar
AR_FLAGS = rcs

DIR_S = srcs
DIR_O = obj

SRCS = $(shell find $(DIR_S) -name '*.s')
OBJS = $(patsubst $(DIR_S)/%.s,$(DIR_O)/%.o,$(SRCS))

${NAME}: ${OBJS} 
	@echo "${MAGENTA}Creating $@${END}"
	@$(AR) $(AR_FLAGS) $@ $^
	@echo "${GREEN}Done!${END}"

$(DIR_O)/%.o: $(DIR_S)/%.s
	@mkdir -p $(dir $@)
	@echo "${BLUE}Compiling ${notdir $<}${END}"
	@$(ASM) $(ASM_FLAGS) $< -o $@

all: ${NAME}

clean: 
	@echo "${RED}Removing objs${END}"
	@rm -rf obj

fclean: clean
	@echo "${RED}Removing ${NAME}${END}"
	@rm -rf ${NAME}

re: fclean all

test: all
	@echo "${CYAN}Testing ${NAME}${END}\n"
	@./tester.sh

.PHONY: all clean fclean re bonus test 