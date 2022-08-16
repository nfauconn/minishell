TARGET = minishell

INC_DIR = ./includes
SRC_DIR  = ./srcs

EXEC = exec/
BUILTINS = builtins/
REDIR = redir/

PARSING = parsing/
CMD_BUILD = cmd_build/
COMPAR_UTILS = compar_utils/
TOKENIZER = tokenizer/

BUILD_DIR  = ./objs

LIBFT_DIR = ./libft
LIBFT_INC_DIR = ./libft/includes
LIBFT = ./libft/libft.a

S_EXT = .c

SRCS = ${addsuffix ${S_EXT}, ${addprefix ${SRC_DIR}/, \
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
		parser \
		lexer \
		expand \
		quote_removal \
		debug_utils \
		${addprefix ${TOKENIZER}, \
		tokenize \
		utils} \
		${addprefix ${CMD_BUILD}, \
		build_list \
		build_cmd \
		params \
		params_utils \
		${addprefix ${REDIR}, \
		redir_set \
		heredoc_set \
		heredoc_run \
		redir_check}} \
		${addprefix ${COMPAR_UTILS}, \
		builtins \
		files \
		metachars}} \
		${addprefix ${EXEC}, \
		cmd_execve \
		cmd_path \
		launch \
		launch_builtin \
		launch_pipeline \
		launch_single \
		wait \
		${addprefix ${REDIR}, \
		dup_io_pipeline \
		dup_io_singlecmd \
		open \
		utils} \
		${addprefix ${BUILTINS}, \
		cd \
		echo \
		env \
		exit \
		export \
		pwd \
		unset}}}}

DEPS = ${subst ${SRC_DIR}, ${BUILD_DIR}, ${SRCS:%.c=%.d}}
OBJS = ${subst ${SRC_DIR}, ${BUILD_DIR}, ${SRCS:%.c=%.o}}
VPATH = ${SRC_DIR}:${INC_DIR}:${BUILD_DIR}

CC = clang
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
INCLUDES = -I ${INC_DIR} -I ${LIBFT_INC_DIR}
LD_FLAGS = -L ${LIBFT_DIR} -ltinfo -lreadline
COMP = ${CC} ${CFLAGS}
RM	 = rm -rf

all: libftcreat ${TARGET}

libftcreat:
	@make -sC ${LIBFT_DIR}

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

.PHONY: all clean fclean re libftcreat
