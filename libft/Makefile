NAME = libft.a

INC_DIR = ./includes

SRC_DIR  = ./srcs
#SUBDIRECTORIES#
COMPARISON_SEARCH = comparison_search
CONV = conversions
DISPLAY = display
FT_PRINTF = ft_printf
GNL = gnl
LST = lst
MEMORY = memory_add_free
REPLACE = replace_copy_join_iter
SIZE_LEN_MATHS = size_len_maths

BUILD_DIR  = ./objs

S_EXT = .c

SRCS := ${addsuffix ${S_EXT}, ${addprefix ${SRC_DIR}/, \
		${addprefix ${COMPARISON_SEARCH}/, \
		ft_is_whitespace \
		ft_isalnum \
		ft_isalpha \
		ft_isascii \
		ft_isdigit \
		ft_isprint \
		ft_memchr \
		ft_memcmp \
		ft_str_isdigit \
		ft_strchr \
		ft_strcmp \
		ft_strend_cmp \
		ft_strncmp \
		ft_strnstr \
		ft_strrchr} \
		${addprefix ${CONV}/, \
		ft_atoi \
		ft_atoi_base \
		ft_itoa \
		ft_split \
		ft_str_array_to_lst \
		ft_ulltoa_base} \
		${addprefix ${DISPLAY}/, \
		ft_printerror \
		ft_putchar_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_putstr_fd \
		ft_str_array_display \
		${addprefix ${FT_PRINTF}/, \
		pf_conv_c \
		pf_conv_s \
		pf_conv_p \
		pf_conv_d_i \
		pf_conv_u \
		pf_conv_x \
		pf_conv_mx \
		pf_conv_percent \
		pf_convert \
		pf_fill_nb \
		pf_isflag \
		pf_ft_printf \
		pf_init \
		pf_insert_into_buffer \
		pf_main_loop \
		pf_parse_printf}} \
		${addprefix ${GNL}/, \
		get_next_line} \
		${addprefix ${LST}/, \
		ft_lstadd_back \
		ft_lstadd_front \
		ft_lstclear \
		ft_lstdelone \
		ft_lstiter \
		ft_lstlast \
		ft_lstmap \
		ft_lstnew \
		ft_lstsize} \
		${addprefix ${MEMORY}/, \
		ft_calloc \
		ft_memalloc \
		ft_memdel \
		ft_replace_free_old \
		ft_str_array_free \
		ft_strdel} \
		${addprefix ${REPLACE}/, \
		ft_bzero \
		ft_memccpy \
		ft_memcpy \
		ft_memmove \
		ft_memset \
		ft_strdup \
		ft_strfdup \
		ft_strfjoin \
		ft_strfjoinchar \
		ft_strjoin \
		ft_strlcat \
		ft_strlcpy \
		ft_strmapi \
		ft_strtrim \
		ft_substr \
		ft_tolower \
		ft_toupper} \
		${addprefix ${SIZE_LEN_MATHS}/, \
		ft_nbrlen_base \
		ft_negative_power \
		ft_operate_vector \
		ft_power \
		ft_rev_int_tab \
		ft_sort_int_tab \
		ft_str_array_size \
		ft_strlen \
		ft_square_root}}}

DEPS := ${subst ${SRC_DIR}, ${BUILD_DIR}, ${SRCS:%.c=%.d}}
OBJS := ${subst ${SRC_DIR}, ${BUILD_DIR}, ${SRCS:%.c=%.o}}
VPATH = ${SRC_DIR}:${INC_DIR}:${BUILD_DIR}

CC = clang
CFLAGS = -Wall -Wextra -Werror -g3
INCLUDES = -I ${INC_DIR}
COMP = ${CC} ${CFLAGS}
RM	 = rm -rf

all: ${NAME}

${NAME}: ${OBJS} Makefile
	@ar rc ${NAME} ${OBJS}
	@echo "lib created"

-include ${DEPS}

${BUILD_DIR}/%.o: %.c
	@mkdir -p ${dir $@}
	@echo create: ${@:%=%}
	@${COMP} -MMD ${INCLUDES} -o $@ -c $<

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: clean fclean all re
