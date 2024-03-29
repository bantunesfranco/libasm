#ifndef LIBASM_H
#define LIBASM_H

#include <sys/types.h>
#include <sys/errno.h>

typedef struct	s_list
{
	void *data;
	struct s_list *next;
}				t_list;

// Mandatory
extern "C" ssize_t	ft_read(int fd, void *buf, size_t count);
extern "C" ssize_t	ft_write(int fd, const void *buf, size_t count);
extern "C" size_t	ft_strlen(const char *s);
extern "C" int		ft_strcmp(const char *s1, const char *s2);
extern "C" char		*ft_strcpy(char *dest, const char *src);
extern "C" char		*ft_strdup(const char *s1);

// Bonus
extern "C" int		ft_atoi(const char *s);
extern "C" void		ft_list_push_front(t_list **begin_list, void *data);
extern "C" int		ft_list_size(t_list *begin_list);
extern "C" void		ft_list_sort(t_list **begin_list, int (*cmp)());
extern "C" void		ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(const char*, const char*), void (*free_fct)(void *));

// Extra
extern "C" t_list	*ft_list_new(void *data);

// Test helpers
extern "C" void		ft_list_clear(t_list **begin_list, void (*free_fct)(void *));


#endif