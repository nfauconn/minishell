TARGET = minishell

INCLUDES = -I includes -I libft/includes
LD_FLAGS = -L libft -ltinfo -lreadline

BUILD_DIR  = ./objs
SRC_DIR  = ./srcs

SRCS := \
		./srcs/builtins_cd.c \
		./srcs/builtins_echo.c \
		./srcs/builtins_env.c \
		./srcs/builtins_export.c \
		./srcs/builtins_pwd.c \
		./srcs/builtins_unset.c \
		./srcs/data_env_list.c \
		./srcs/end.c \
		./srcs/error.c \
		./srcs/init.c \
		./srcs/main.c \
		./srcs/execute_redirection.c \
		./srcs/parsing_get_types.c \
		./srcs/parsing_lexer.c \
		./srcs/parsing_tokenizer.c \
		./srcs/parsing_utils.c \
		./srcs/parsing_expand.c \
		./srcs/signals.c
OBJS := $(subst $(SRC_DIR), $(BUILD_DIR), $(SRCS:%.c=%.o))
VPATH = $(SRC_DIR):$(INC_DIR):$(BUILD_DIR)

CC = clang
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
COMP = ${CC} ${CFLAGS}
RM	 = rm -rf

all: ${TARGET}

$(TARGET): ${OBJS} Makefile
	@make -C libft
	@${COMP} ${LD_FLAGS} ${OBJS} -o ${TARGET} -lft
	@echo "${TARGET} created"

${BUILD_DIR}/%.o: %.c
	@mkdir -p ${BUILD_DIR}
	@echo create: ${@:%=%}
	@${COMP} ${INCLUDES} -c $< -o $@

clean:
	@make clean -C libft
	@${RM} ${BUILD_DIR}
	@echo "objs deleted"

fclean: clean
	@make fclean -C libft
	@${RM} ${TARGET}
	@echo "program deleted"

re: fclean all

TIME = `date +"%d/%m/%Y %Hh%M %Z"`
USER := $(shell env | grep USER | tail --bytes=+6)

git: fclean
	git add .
	git commit -m "by $(USER) at $(TIME)"
	git push

.PHONY: all clean fclean re
