TARGET = minishell

INC_DIR = ./includes
SRC_DIR  = ./srcs
BUILTINS = builtins/
EXEC = exec/
REDIR = redirections/
PARSING = parsing/
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
		close \
		error \
		exit \
		init \
		input \
		prompt \
		reset \
		signals \
		${addprefix ${PARSING}, \
		tokenizer \
		token_utils \
		types \
		lexer \
		expand \
		expand_utils \
		conv_to_cmd \
		cmd_creat \
		cmd_init \
		parser \
		utils_comparison \
		utils_comparison2} \
		${addprefix ${REDIR}, \
		check_access \
		heredoc_run \
		heredoc_set \
		open \
		set_redir \
		pipeline_red \
		single_red \
		utils} \
		${addprefix ${EXEC}, \
		cmd_execve \
		cmd_path \
		launch \
		launch_builtin \
		launch_pipeline \
		launch_single \
		wait \
		${addprefix ${BUILTINS}, \
		cd \
		echo \
		env \
		exit \
		export \
		pwd \
		unset}}}}

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

${TARGET}: ${OBJS} ${LIBFT} Makefile
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
