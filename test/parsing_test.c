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
#include "ms_parsing.h"
#include <criterion/criterion.h>
#include <libft_mem.h>

#define T(a) Test(minishell_parsing, a)

T(hello)
{
	ms_set_env("HELLO", "WORLD");
	cr_assert_str_eq(ms_expand_vars("hello $HELLO"), "hello WORLD");
}

T(no_hello)
{
	cr_assert_str_eq(ms_expand_vars("hello $HELLO"), "hello ");
}
