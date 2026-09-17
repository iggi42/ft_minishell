/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:21:10 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:21:11 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNAL_H
# define MS_SIGNAL_H
// one slot per t_byte, so every signal number fits
# define MS_SIG_SLOTS 256

typedef void	(*t_ms_sig_handler)(int);

void			ms_signal_init(void);
void			ms_signal_child(void);

void			ms_signal_listen(int sig);
int				ms_signal_last(void);
void			ms_signal_set_handler(int sig, t_ms_sig_handler dab);
int				ms_signal_consume(void);
#endif
