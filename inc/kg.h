/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kg.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 04:24:26 by fkruger           #+#    #+#             */
/*   Updated: 2026/04/07 04:24:33 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KG_H
# define KG_H
# include <stdbool.h>
# include <unistd.h>

// @brief add pid to structure, bool to check if it worked
void	kg_add(pid_t new_pid);

// @brief remove a pid from the kindergarden
bool	kg_rm(pid_t existing_pid);

// @brief call the apply function against each stored pointer
void	kg_each(void (*apply)(pid_t stored_pid));

// @brief waits for all stored pids and frees the internal data structure
// only waits for stored pids if they wait is true (use with false after forking)
void	kg_cleanup(bool wait);

#endif
