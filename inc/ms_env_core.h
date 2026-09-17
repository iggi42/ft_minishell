/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env_core.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:15:10 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:15:12 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENV_CORE_H
# define MS_ENV_CORE_H

# include <libft_kv.h>

// get an key value store, configured to store environment variables
t_kv	*ms_env_core_get(void);

#endif
