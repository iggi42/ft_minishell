/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_builtins.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 22:47:35 by fkruger           #+#    #+#             */
/*   Updated: 2026/08/05 22:47:59 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXEC_BUILTINS_H
# define MS_EXEC_BUILTINS_H
# include <libft_byte_t.h>

t_byte			ms_exec_builtin_cd(char **argv);
t_byte			ms_exec_builtin_echo(char **argv);
t_byte			ms_exec_builtin_env(char **argv);
t_byte			ms_exec_builtin_exit(char **argv);
t_byte			ms_exec_builtin_export(char **argv);
t_byte			ms_exec_builtin_pwd(char **argv);
t_byte			ms_exec_builtin_unset(char **argv);

#endif
