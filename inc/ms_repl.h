/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_repl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 19:04:13 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/15 19:04:14 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_REPL_H
# define MS_REPL_H

typedef char* (*ms_repl_prompt_get)(void);

// run repl with readline
int	ms_repl(void);

// read and exec line by from the fd
int	ms_run_from_fd(int fd);


// repl utils (also used by heredoc)
char	*ms_gnl(ms_repl_prompt_get prompt_getter);

char *ms_repl_prompt_shell(void);
char *ms_repl_prompt_heredoc(void);

#endif
