/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 20:57:44 by fkruger           #+#    #+#             */
/*   Updated: 2026/06/05 20:57:46 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "ms_safe.h"
#include <fcntl.h>

int	ms_open_infile(char *infile_path)
{
	return (ms_open(infile_path, O_RDONLY | O_CLOEXEC));
}

int	ms_open_outfile(char *outfile_path)
{
	return (ms_open(outfile_path, O_CREAT | O_TRUNC | O_WRONLY | O_CLOEXEC));
}

int	ms_open_outappfile(char *outfile_path)
{
	return (ms_open(outfile_path, O_CREAT | O_WRONLY | O_APPEND | O_CLOEXEC));
}
