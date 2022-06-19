TARGET = minishell

INC_DIR = ./includes
SRC_DIR  = ./srcs
BUILTINS = builtins/
EXEC = exec/
PARSING = parsing/
BUILD_DIR  = ./objs

LIBFT_DIR = ./libft
LIBFT_INC_DIR = ./libft/includes

L_EXT = .a
H_EXT = .h
S_EXT = .c

LIBS := ${addsuffix ${L_EXT}, ${addprefix ${LIBFT_DIR}, \
		libft}}

SRCS := ${addsuffix ${S_EXT}, ${addprefix ${SRC_DIR}/, \
		end \
		error \
		init \
		main \
		signals \
		${addprefix ${BUILTINS}, \
		cd \
		echo \
		env \
		export \
		pwd \
		unset} \
		${addprefix ${EXEC}, \
		get_path \
		heredoc \
		pipeline \
		redirection \
		utils_for_fd} \
		${addprefix ${PARSING}, \
		conv_to_cmd \
		conv_utils \
		expand \
		input \
		lexer \
		parser \
		tokenizer \
		types \
		utils}}}

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

${TARGET}: ${OBJS} Makefile
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

git: fclean
	git add .
	git commit -m "by ${USER} at ${TIME}"
	git push

.PHONY: all clean fclean re
