/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_safe.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:17:18 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:17:26 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SAFE_H
# define MS_SAFE_H
# include <libft_byte_t.h>
# include <stdbool.h>
# include <stdlib.h>

// memory safety
void	*ms_malloc(size_t size);
char	*ms_strdup(char *copy_me);
char	*ms_substr(const char *s, size_t start, size_t len);

// high level memory safety
//// close all fds that aren't stdenv
//// wait for for all child processes
void	ms_clean(void);

// fd safety
int		ms_open(char *path, int flags);
void	ms_close(int fd);
int		ms_dup(int from);
void	ms_dup2(int from, int to);
int		*ms_pipe(int *new_pipe);

// os process safety
pid_t	ms_fork(void);
t_byte	ms_wait(pid_t wait_for_me);
#endif
