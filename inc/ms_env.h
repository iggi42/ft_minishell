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

void		ms_load_env(char **environ);
const char	**ms_get_environ(void);

// set an environment variable, copies the string into an key value storage.
void		ms_set_env(char *name, const char *value);

// get an environment variable, freeing it directly is not your job
char		*ms_get_env(char *name, const char *fallback);

void		ms_env_each(void (*fold)(void *acc, char *name, char *value),
				void *acc);

// free the storage of environment variables
void		ms_env_free(void);

#endif
