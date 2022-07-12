TARGET = minishell

INC_DIR = ./includes
SRC_DIR  = ./srcs
BUILTINS = builtins/
EXEC = exec/
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
		init \
		input \
		clear \
		error \
		signals \
		${addprefix ${PARSING}, \
		tokenizer \
		token_utils \
		types \
		lexer \
		expand \
		expand_utils \
		conv_to_cmd \
		conv_utils_creat \
		conv_utils_redir \
		parser \
		utils_comparison \
		utils_comparison2} \
		${addprefix ${EXEC}, \
		cmd_execve \
		cmd_path \
		launch \
		launch_pipeline \
		launch_single \
		redir_apply \
		redir_heredoc \
		redir_open \
		redir_utils \
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

all: libftcreat ${TARGET}

libftcreat: 
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

TIME = `date +"%d/%m/%Y %Hh%M %Z"`
USER := ${shell env | grep USER | tail --bytes=+6}

git:
	git add .
	git commit -m "by ${USER} at ${TIME}"
	git push

.PHONY: all clean fclean re
