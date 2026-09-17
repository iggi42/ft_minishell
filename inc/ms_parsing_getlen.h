/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing_getlen.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 11:03:01 by fkruger           #+#    #+#             */
/*   Updated: 2026/09/17 11:03:13 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PARSING_GETLEN_H
# define MS_PARSING_GETLEN_H
# include <stddef.h>

// this header is to detected parts of the syntax
// like var names, or quotes
// every function in here expectes the string to start with what is searched
// if it does not start with what we are searching every function here returns 0

size_t	ms_parsing_varname(char *str);

#endif
