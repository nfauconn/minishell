TARGET = minishell

INCLUDES = -I includes -I libft/includes
LD_FLAGS = -L libft -ltinfo -lreadline

BUILD_DIR  = ./objs
SRC_DIR  = ./srcs

SRCS := ${addprefix ${SRC_DIR}/, \
		builtins_cd.c \
		builtins_echo.c \
		builtins_env.c \
		builtins_export.c \
		builtins_pwd.c \
		builtins_unset.c \
		end.c \
		error.c \
		init.c \
		main.c \
		execute_redirection.c \
		execute_utils.c \
		parsing_conv_to_cmd.c \
		parsing_conv_utils.c \
		parsing_expand.c \
		parsing_input.c \
		parsing_lexer.c \
		parsing_parser.c \
		parsing_tokenizer.c \
		parsing_types.c \
		parsing_utils.c \
		signals.c}
	
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

${BUILD_DIR}/%.o: ${SRCS}/%.c
	@mkdir -p ${BUILD_DIR}
	@echo create: ${@:%=%}
	@${COMP} ${INCLUDES} -c $? -o $@

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
