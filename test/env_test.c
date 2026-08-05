/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <your@mail.com>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:23:38 by fkruger           #+#    #+#             */
/*   Updated: 2026/05/30 22:08:01 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_env.h"
#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <libft_arr.h>
#include <unistd.h>

#define T(a) Test(minishell_env, a)

T(set)
{
	ms_set_env("VAR_NAME", "WORLD");
	cr_assert_str_eq(ms_get_env("VAR_NAME", "WRONG"), "WORLD");
}

T(overwrite)
{
	ms_set_env("VAR_NAME", "WORLD");
	ms_set_env("VAR_NAME", "LOL");
	cr_assert_str_eq(ms_get_env("VAR_NAME", "WRONG"), "LOL");
}

T(not_set)
{
	cr_assert_str_eq(ms_get_env("HELLO", "RIGHT"), "RIGHT");
}

T(unset)
{
	ms_set_env("VAR_NAME", "WORLD");
	ms_set_env("VAR_NAME", "WORLD2");
	ms_unset_env("VAR_NAME");
	cr_assert_str_eq(ms_get_env("VAR_NAME", "fallback"), "fallback");
}

T(load_environ)
{
	ms_load_env(__environ);
	cr_assert_str_neq(ms_get_env("PATH", "fallback"), "fallback");
}

// const char	**ms_get_environ(void);
T(export2environ_empty)
{
	const char	**environ = ms_get_environ();

	cr_assert_eq(ft_arr_len((t_arr)environ), 0);
}

// const char	**ms_get_environ(void);
T(export2environ_one_var)
{
	const char	**environ;

	ms_set_env("LOL", "OH YES");
	environ = ms_get_environ();
	cr_assert_str_eq(environ[0], "LOL=OH YES");
	cr_assert_eq(ft_arr_len((t_arr)environ), 1);
}

// const char	**ms_get_environ(void);
T(export2environ_one_var_wit_eq)
{
	const char	**environ;

	ms_set_env("LOL", "OH=YES");
	environ = ms_get_environ();
	cr_assert_str_eq(environ[0], "LOL=OH=YES");
	cr_assert_eq(ft_arr_len((t_arr)environ), 1);
}

// const char	**ms_get_environ(void);
T(export2environ_two_vars)
{
	const char	**environ;

	ms_set_env("LOL", "KEIn_SH'IZO_TEST_STRING");
	ms_set_env("wh0t", "OH=YES");
	environ = ms_get_environ();
	cr_assert_str_eq(environ[0], "LOL=KEIn_SH'IZO_TEST_STRING");
	cr_assert_str_eq(environ[1], "wh0t=OH=YES");
	cr_assert_eq(ft_arr_len((t_arr)environ), 2);
}
