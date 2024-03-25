#ifndef LIBASM_H
#define LIBASM_H

#include "sys/types.h"
#include "sys/errno.h"

extern "C" ssize_t	ft_read(int fd, void *buf, size_t count);
extern "C" ssize_t	ft_write(int fd, const void *buf, size_t count);
extern "C" size_t	ft_strlen(const char *s);
extern "C" int		ft_strcmp(const char *s1, const char *s2);
extern "C" char		*ft_strcpy(char *dest, const char *src);
extern "C" char		*ft_strdup(const char *s1);

#endif