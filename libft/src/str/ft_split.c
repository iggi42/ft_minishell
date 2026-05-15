/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 08:15:06 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:06 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"
#include "libft_str.h"
#include <stdbool.h>
#include <stddef.h>

static char	**build_array(char const *s, char c)
{
	size_t	count;
	char	*runner;
	bool	prev_c;

	if (s == NULL)
		return (NULL);
	count = 0;
	runner = (char *)s;
	prev_c = true;
	while (*runner != '\0')
	{
		if (*runner == c && prev_c == false)
			count++;
		prev_c = (*runner == c);
		runner++;
	}
	if (prev_c == false)
		count++;
	return (ft_calloc(count + 1, sizeof(char *)));
}

// count the amount chars until a c in s appears
static size_t	word_len(char const *s, char c)
{
	size_t	result;

	result = 0;
	while (*(s + result) != c && *(s + result) != '\0')
		result++;
	return (result);
}

static char	**clean_up(char **arr)
{
	while (arr != NULL && *arr != NULL)
	{
		ft_free(*arr);
		arr++;
	}
	ft_free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	size_t	word_l;
	size_t	word_i;

	i = 0;
	word_i = 0;
	result = build_array(s, c);
	while (result != NULL && *(s + i) != '\0')
	{
		word_l = word_len(s + i, c);
		if (word_l > 0 && *(s + i) != '\0')
		{
			result[word_i] = ft_substr(s, i, word_l);
			if (result[word_i] == NULL)
				return (clean_up(result));
			word_i++;
			i += word_l;
		}
		else
			i++;
	}
	return (result);
}

/*
{
	char	**result;
	char	*runner;
	size_t	word_count;
	size_t	word_i;
	int		word_start;

	runner = (char *) s;
	word_i = 0;
	word_count = count_words(s, c);
	result = ft_calloc(word_count + 1, sizeof(char *));
	while (result != NULL && *runner != '\0')
	{
		if (*runner == c)
			word_start = -1;
		else if (word_start == -1)
			word_start = i;
		runner++;
	}
	return (result);
}
*/

/*
#include <stdio.h>

int	main(void)
{
	char	**out;
	int		i;
	char	*input;
	char	c;

	input = "test";
	c = '\0';
	out = ft_split(input, c);
	i = 0;
	while (out[i])
	{
		printf("%d : \"%s\"\n", i, out[i]);
		i++;
	}
	printf("%d : %d\n", i, out[i]);
	return (0);
}
*/
