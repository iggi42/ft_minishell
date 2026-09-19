/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expander_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:44:39 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:44:42 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_safe.h"
#include "ms_token.h"

// hides the quote characters of a variable value, so that the quote
// removal pass does not eat quotes that the user never typed
char	*ms_quote_hide(char *value)
{
	char	*result;
	size_t	i;

	result = ms_strdup(value);
	i = 0;
	while (result[i] != '\0')
	{
		if (result[i] == '\'')
			result[i] = MS_HIDDEN_SQ;
		else if (result[i] == '\"')
			result[i] = MS_HIDDEN_DQ;
		i++;
	}
	return (result);
}

// brings the hidden quote characters back, once quote removal is done
char	*ms_quote_show(char *str)
{
	size_t	i;

	i = 0;
	while (str != NULL && str[i] != '\0')
	{
		if (str[i] == MS_HIDDEN_SQ)
			str[i] = '\'';
		else if (str[i] == MS_HIDDEN_DQ)
			str[i] = '\"';
		i++;
	}
	return (str);
}
