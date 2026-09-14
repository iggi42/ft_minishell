/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:04:10 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/15 19:04:12 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENV_H
# define MS_ENV_H

# include <libft_byte_t.h>
# include <stdbool.h>

void	ms_env_environ_import(char **environ);
char	**ms_env_environ_export(void);

// set an environment variable, copies the string into an key value storage.
void	ms_env_set(char *name, char *value);

bool	ms_env_unset(char *name);

// get an environment variable, freeing it directly is not your job
char	*ms_env_get(char *name, char *fallback);

void	ms_env_each(void (*fold)(void *acc, char *name, char *value),
			void *acc);

void	ms_env_inc_shlvl(void);
void	ms_env_init(void);

t_byte	ms_env_get_status(void);
void	ms_env_set_status(t_byte status_code);

// free the storage of environment variables
void	ms_env_free(void);

#endif
