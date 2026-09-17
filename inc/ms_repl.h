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
# include <libft_byte_t.h>

typedef char	*(*t_ms_repl_prompt_get)(void);

// run repl (with readline in interactive)
t_byte			ms_repl(void);

// repl utils (also used by heredoc)
char			*ms_repl_readline(t_ms_repl_prompt_get prompt_getter,
					int (*ms_rl_hook)(void));
// char			*ms_repl_readline(ms_repl_prompt_get prompt_getter);

// char			*ms_repl_rl_wrapper(char *prompt);A
char			*ms_repl_rl_wrapper(char *prompt, int (*ms_rl_hook)(void));

// add the line to the readline history
void			ms_repl_history_add(char *line);
void			ms_repl_history_clear(void);

char			*ms_repl_prompt_shell(void);
char			*ms_repl_prompt_heredoc(void);

#endif
