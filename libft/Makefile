NAME = libft.a
OS    = $(shell uname)
CC	 = clang
SRC_DIR  = ./srcs
OBJ_DIR  = ./objs
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I includes

SRCS = ft_atoi.c ft_atoi_base.c ft_array_size.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_itoa.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c \
ft_nbrlen_base.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strcmp.c \
ft_strdel.c ft_strdup.c ft_strfdup.c ft_strfjoin.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_ulltoa_base.c get_next_line.c maths.c \
rev_int_tab.c sort_int_tab.c str_isdigit.c strfjoinchar.c pf_conv_c.c ft_strend_cmp.c \
pf_conv_s.c pf_conv_p.c pf_conv_d_i.c pf_conv_u.c pf_conv_x.c pf_conv_mx.c pf_conv_percent.c pf_convert.c pf_fill_nb.c\
pf_isflag.c pf_ft_printf.c pf_init.c pf_insert_into_buffer.c pf_main_loop.c pf_parse_printf.c

OBJS  = ${addprefix ${OBJ_DIR}/,${SRCS:%.c=%.o}}

all: $(NAME)

$(NAME): ${OBJS}
	@ar rc $(NAME) $(OBJS)
	@echo "lib created"

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@mkdir -p ${OBJ_DIR}
	@echo create: ${@:%=%}
	@${CC} ${CFLAGS} ${INCLUDES} -o $@ -c $<

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re