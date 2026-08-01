/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmt_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:19:02 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:05 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft_fmt_ops.h"
#include "libft_str.h"
#include "libft_mem.h"
#include "libft_iol.h"

static size_t	get_seg_size(const char *template)
{
	char	*seeker;

	if (*template == '\0')
		return (0);
	if (*template == '%')
		return (2);
	seeker = ft_strchr(template, '%');
	if (seeker == NULL)
		return (ft_strlen(template));
	else
		return (seeker - template);
}

t_list	*ft_fmt_parse(const char *template)
{
	t_list		*result;
	t_iol_el	*seg;

	if (template == NULL || *template == '\0')
		return (NULL);
	seg = (t_iol_el *)ft_malloc(sizeof(t_iol_el));
	if (seg == NULL)
		return (ft_fmt_parse(template));
	seg->buffer = (char *)template;
	seg->size = get_seg_size(template);
	seg->free = NULL;
	result = ft_lstnew(seg);
	if (result != NULL)
		result->next = ft_fmt_parse(template + seg->size);
	else
		ft_free(seg);
	return (result);
}
