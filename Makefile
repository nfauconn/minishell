TARGET = minishell

INC_DIR = ./includes
SRC_DIR  = ./srcs
BUILTINS = builtins/
EXEC = exec/
REDIR = redirections/
PARSING = parsing/
COMPAR_UTILS = compar_utils/
BUILD_DIR  = ./objs

LIBFT_DIR = ./libft
LIBFT_INC_DIR = ./libft/includes
LIBFT = ./libft/libft.a

L_EXT = .a
H_EXT = .h
S_EXT = .c

LIBS := ${addsuffix ${L_EXT}, ${addprefix ${LIBFT_DIR}, \
		libft}}

SRCS := ${addsuffix ${S_EXT}, ${addprefix ${SRC_DIR}/, \
		main \
		clear \
		error \
		exit \
		init \
		input \
		prompt \
		reset \
		signals \
		${addprefix ${PARSING}, \
		parse \
		tokenize \
		tokenize_utils \
		lexer \
		cmd_list_build \
		cmd_init \
		cmd_args_redir \
		cmd_args_redir_utils \
		expand \
		expand_utils \
		expand_quotes \
		expand_string \
		expand_var \
		${addprefix ${COMPAR_UTILS}, \
		builtins \
		files \
		metachars}} \
		${addprefix ${REDIR}, \
		set_redir \
		ambiguous_redir \
		heredoc_set \
		heredoc_run \
		check_access} \
		${addprefix ${EXEC}, \
		wait}}}

DEPS := ${subst ${SRC_DIR}, ${BUILD_DIR}, ${SRCS:%.c=%.d}}
OBJS := ${subst ${SRC_DIR}, ${BUILD_DIR}, ${SRCS:%.c=%.o}}
VPATH = ${SRC_DIR}:${INC_DIR}:${BUILD_DIR}

CC = clang
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
INCLUDES = -I ${INC_DIR} -I ${LIBFT_INC_DIR}
LD_FLAGS = -L ${LIBFT_DIR} -ltinfo -lreadline
COMP = ${CC} ${CFLAGS}
RM	 = rm -rf

all: ${LIBFT} ${TARGET}

${LIBFT}:
	@make -C ${LIBFT_DIR}

${TARGET}: ${OBJS} ${LIBFT} #Makefile
	@${COMP} ${LD_FLAGS} ${OBJS} -o ${TARGET} -lft
	@echo "${TARGET} created"

-include ${DEPS}

${BUILD_DIR}/%.o: %.c
	@mkdir -p ${dir $@}
	@echo create: ${@:%=%}
	@${COMP} -MMD ${INCLUDES} -c $< -o $@

clean:
	@make clean -C libft
	@${RM} ${BUILD_DIR}
	@${RM} ${DEPS}
	@echo "objs deleted"

fclean: clean
	@make fclean -C libft
	@${RM} ${TARGET}
	@echo "program deleted"

re: fclean all

.PHONY: all clean fclean re
