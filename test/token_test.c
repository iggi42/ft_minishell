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

#include "libft_arr_t.h"
#include "ms_env.h"
#include "ms_token.h"
#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <libft_mem.h>
#include <libft_arr.h>
#include <libft_io.h>
#include <unistd.h>

#define T(name) Test(minishell_token, name)
#define STR_ARRAY(...) ((char *[]) { __VA_ARGS__, NULL })
#define TT(name, in, ...) T(name) { \
	char **soll = STR_ARRAY(__VA_ARGS__); \
	crm_assert_token_eq(ms_tokenize(in), soll); \
}

// null terminate the varadice arrays
void crm_assert_token_eq(t_token *is, char **soll)
{
	if(is == NULL && *soll == NULL)
		return;
	if(is == NULL)
		cr_assert_fail("token list ended earlier than expected");
	if(*soll == NULL)
		cr_assert_fail("token list ended later than expected");
   cr_assert_str_eq(is->value, *soll);
   crm_assert_token_eq(is->next, soll + 1);
}

// start test cases
TT(simple_token, "ECHO maybe", "ECHO", "maybe")
TT(simple_pipe, "ECHO maybe |", "ECHO", "maybe", "|")
TT(simple_double_quotes, "ECHO \" maybe | \"", "ECHO", "\" maybe | \"")
TT(simple_single_quotes, "ECHO 'maybe |'", "ECHO", "'maybe |'")
TT(nested_quotes, " \" this's mine\" ech0", "\" this's mine\"", "ech0")
TT(redi_in, " \" this's mine\" < ech0", "\" this's mine\"", "<", "ech0")
TT(redi_out, " > \" this's mine\" 0c7", ">", "\" this's mine\"", "0c7")
TT(redi_heredoc, " <<LOL \" this's mine\" 0c7", "<<", "LOL", "\" this's mine\"", "0c7")
