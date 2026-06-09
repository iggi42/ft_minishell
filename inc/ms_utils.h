/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:04:10 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/15 19:04:12 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_UTILS_H
# define MS_UTILS_H
# define MS_MEM_ERR "malloc failed"

// ms_exit_if(ft_malloc(size), "malloc failed");
void	*ms_exit_if(void *cond, const char *error_msg);

// exit clean with memory allocation error if cond is NULL, otherwise return cond
void	*ms_protect(void *cond);

#endif
