/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:22:20 by nfauconn          #+#    #+#             */
/*   Updated: 2022/06/23 12:20:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "ft_printf.h"

# define BUFFER_SIZE 100
# define FD_MAX 10240

typedef unsigned int		t_uint;
typedef unsigned long long	t_ull;

typedef enum e_bool
{
	SUCCESS = 0,
	FAILURE = 1
}	t_bool;

typedef struct s_vector
{
	int	x;
	int	y;
}	t_v;

typedef struct s_float_vector
{
	float	x;
	float	y;
}	t_float_vector;

typedef struct s_double_vector
{
	double	x;
	double	y;
}	t_double_vector;

typedef struct s_list
{
	void			*content;
	int				type;
	struct s_list	*next;
}	t_list;

/* ARRAYS */
void		ft_str_array_display(char **tab);
void		ft_str_array_free(char **tab);
int			ft_str_array_size(char **tab);

/* CHARACTERS */
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isflagpf(int c);
int			ft_isprint(int c);
char		*ft_itoa(int n);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_ulltoa_base(unsigned long long n, int base, size_t maj);

/* GNL */

int			get_next_line(int fd, char **line);

/* LISTS */
t_list		*ft_str_array_to_lst(char **tab);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstadd_front(t_list **alst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);

/* MATHS */
int			ft_atoi(const char *s);
int			ft_atoi_base(const char *s, int base);
int			ft_nbrlen_base(int nbr, int base);
float		ft_negative_power(int nb, int power);
t_v			ft_operate_vector(t_v vector, char operation, int nb);
t_ull		ft_power(int nb, int power);
void		ft_rev_int_tab(int *tab, int size);
int			*ft_sort_int_tab(int *tab, int size);
int			ft_square_root(int nb);

/* MEMORY */
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		*ft_memalloc(size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		ft_memdel(void **ap);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		ft_replace_and_free(void **prev_content, void *new_content);

/* PRINT */
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);

/* STRINGS */
char		**ft_split(char const *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_strdel(char **as);
int			ft_strend_cmp(char *name, char *end);
char		*ft_strdup(const char *s1);
void		ft_strfdup(char **over, char *buff);
int			ft_str_isdigit(char *str);
void		ft_strfjoin(char **to_free, char *to_add);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strfjoinchar(char *str, char c);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *str);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);

#endif
