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
		./srcs/end.c \
		./srcs/error.c \
		./srcs/init.c \
		./srcs/main.c \
		./srcs/parsing_lexer.c \
		./srcs/parsing_tokenizer.c \
		./srcs/parsing_utils.c \
		./srcs/parsing.c \
		./srcs/signals.c
OBJS := $(subst $(SRC_DIR), $(BUILD_DIR), $(SRCS:%.c=%.o))
DEPS := $(OBJS:.o=.d)
VPATH = $(SRC_DIR):$(INC_DIR):$(BUILD_DIR)

CC = clang
CFLAGS = -Wall -Wextra -Werror -g
COMP = ${CC} ${CFLAGS}
RM	 = rm -rf

all: ${TARGET}

$(TARGET): ${OBJS}
	@make -C libft
	@${COMP} ${LD_FLAGS} ${OBJS} -o ${TARGET} -lft
	@echo "${TARGET} created"

${BUILD_DIR}/%.o: %.c
	@mkdir -p ${BUILD_DIR}
	@echo create: ${@:%=%}
	@${COMP} ${INCLUDES} -c $< -o $@

# Place dependency files in build directory
# automatically generate dependency rules
$(BUILD_DIR)%.d: %.c
	$(CXX) $(CXXFLAGS) -MF"$@" -MG -MM -MD -MP -MT"$@" -MT"$(OBJS)" "$<"
# -MF  write the generated dependency rule to a file
# -MG  assume missing headers will be generated and don't stop with an error
# -MM  generate dependency rule for prerequisite, skipping system headers
# -MP  add phony target for each header to prevent errors when header is missing
# -MT  add a target to the generated dependency

clean:
	@make clean -C libft
	@${RM} ${BUILD_DIR}
	@echo "objs deleted"

fclean: clean
	@make fclean -C libft
	@${RM} ${TARGET}
	@echo "program deleted"

re: fclean all

.PHONY: all clean fclean re
