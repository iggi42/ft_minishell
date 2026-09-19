/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 16:19:14 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/19 16:19:15 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_HEREDOC_H
# define MS_HEREDOC_H
# include "ms_cmd_t.h"

void	ms_heredoc_cleanup_running(t_ms_heredoc *chd);

void	ms_heredoc_cleanup_ready(t_ms_heredoc *chd);

// returns NULL if the input delimiter carried no quotes at all,
// otherwise the delimiter with every quote removed
char	*unquoted_delimiter(char *delimiter);
char	*ms_gnl_heredoc(char *delimiter);
char	**ms_heredoc_readin(char *delimiter);
#endif
