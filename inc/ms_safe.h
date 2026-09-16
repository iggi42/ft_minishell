#include <libft_byte_t.h>
#include <stdbool.h>
#include <stdlib.h>

// memory safety
void	*ms_malloc(size_t size);
char	*ms_strdup(char *copy_me);
char	*ms_substr(const char *s, size_t start, size_t len);

// high level memory safety
//// close all fds that aren't stdenv
//// kill all wait for all child processes
//// free all allocated pointers that aren't in the env store or gnl cache or were added ms_clean_keep
void	ms_clean(void);
bool	ms_clean_keep(void *keep_me);

// fd safety
int		ms_open(char *path, int flags);
void	ms_close(int fd);
int		ms_dup(int from);
void	ms_dup2(int from, int to);
int		*ms_pipe(int *new_pipe);

// os process safety
pid_t	ms_fork(void);
t_byte	ms_wait(pid_t wait_for_me);
