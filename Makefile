RED=\033[1;31m
GREEN=\033[1;32m
YELLOW=\033[1;33m
BLUE=\033[1;34m
MAGENTA=\033[1;35m
CYAN=\033[1;36m
END=\033[0m

NAME = libasm.a 
ASSEMBLER = nasm
FLAGS = -f elf64
DIR_S = srcs
DIR_O = obj

SRCS = $(shell find $(DIR_S) -name '*.s')
OBJS = $(patsubst $(DIR_S)/%.s,$(DIR_O)/%.o,$(SRCS))

${NAME}: ${OBJS} 
	@echo "${MAGENTA}Creating $@${END}"
	@ar rcs ${NAME} ${OBJS}
	@echo "${GREEN}Done!${END}"

$(DIR_O)/%.o: $(DIR_S)/%.s
	@mkdir -p $(dir $@)
	@echo "${BLUE}Compiling ${notdir $<}${END}"
	@$(ASSEMBLER) $(FLAGS) $< -o $@

all: ${NAME}

clean: 
	@echo "${RED}Removing objs${END}"
	@rm -rf obj

fclean: clean
	@echo "${RED}Removing ${NAME}${END}"
	@rm -rf ${NAME}

re: fclean all

git:
	git commit -m "auto commit"
	git push

.PHONY: all clean fclean re bonus test git