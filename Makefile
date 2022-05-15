NAME = minishell
OBJ_DIR  = ./objs
CC = clang
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I includes -I libft/includes
LD_FLAGS = -L libft -ltinfo -lreadline
COMP = ${CC} ${CFLAGS}
RM	 = rm -rf
SRCS =	builtins.c \
		end.c \
		init.c \
		main.c \
		signals.c \
		tokenizer.c \
		parse.c
OBJS = ${addprefix ${OBJ_DIR}/,${SRCS:.c=.o}}

${OBJ_DIR}/%.o: %.c
	@mkdir -p ${OBJ_DIR}
	@echo create: ${@:%=%}
	@${COMP} ${INCLUDES} -o $@ -c $<

$(NAME): ${OBJS}
	@make -C libft
	@${COMP} ${LD_FLAGS} ${OBJS} -o ${NAME} -lft
	@echo "${NAME} created"

all: ${NAME}

clean:
	@make clean -C libft
	@${RM} ${OBJ_DIR}
	@echo "objs deleted"

fclean: clean
	@make fclean -C libft
	@${RM} ${NAME}
	@echo "program deleted"

re: fclean all

.PHONY: all clean fclean re
