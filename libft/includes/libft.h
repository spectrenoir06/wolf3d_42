/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 11:04:26 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/28 15:14:39 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include "get_next_line.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(const void *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *ne);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_lstpushback(t_list **lst, t_list *ne);
void				ft_lstsmartpushback(t_list **list, t_list *ne);
void				ft_lstsimpledel(t_list **list);
void				ft_lstsimpledelone(t_list **list);

int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_islower(int c);
int					ft_isprint(int c);
int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isspace(int c);

size_t				ft_strlen(const char *str);
char				*ft_strcpy(char *dst, const char *src);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);

void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const	void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memalloc(size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_memdel(void **ap);

char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);

char				*ft_strdup(const char *s1);
size_t				ft_strlen(const char *s);

char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);

char				*ft_strstr(const char *str, const char *to_find);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);

char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *s1, const char *s2, size_t n);

char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);

int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);

char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);

char				*ft_itoa(int i);

void				ft_putchar(char c);
void				ft_putstr(const char *s);
void				ft_putendl(const char *s);
void				ft_putnbr(int i);
void				ft_putnbrll(long long int nb);

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

void				*ft_malloc(size_t t);
char				*ft_burger(const char *s1, char c, const char *s2);
void				ft_putstr_sub(char *str, int start, int l);

void				ft_sort_bbl(void **t, int s, int (*f)(void*, void*));
void				ft_sort_qck(void **t, int s, int (*f)(void*, void*));

void				ft_swap(void **p1, void **p2);
void				ft_kebab(char *buff, const char *first, ...);

#endif
