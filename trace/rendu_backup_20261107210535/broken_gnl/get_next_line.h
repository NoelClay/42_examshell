#ifndef GNL
#define GNL

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
# endif

# include <stdlib.h>
# include <unistd.h>

char *ft_strchr(char *s, int c);
void *ft_memcpy(void *dest, const void *src, size_t n);
size_t ft_strlen(char *s);
int str_append_mem(char **s1, char *s2, size_t size2);
int str_append_str(char **s1, char *s2);
void *ft_memmove(void *dest, const void *src, size_t n);
char *get_next_line(int fd);

#endif