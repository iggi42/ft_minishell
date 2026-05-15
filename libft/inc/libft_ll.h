/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_ll.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkruger <fkruger@student.42vienna.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:32:03 by fkruger           #+#    #+#             */
/*   Updated: 2026/02/13 18:39:04 by fkruger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LL_H
# define LIBFT_LL_H

# include "libft_arr_t.h"

//! @name linked list
//!@{

//! one link of a linked list
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/**
 * @brief create a new list
 */
t_list				**ft_lststart(t_list *head);

/**
 * @brief create a new node
 */
t_list				*ft_lstnew(void *content);

/**
 * @brief create a new node
 */
void				ft_lstadd_front(t_list **lst, t_list *new_l);

/**
 * @brief get the length of the list
 */
int					ft_lstsize(t_list *lst);

/**
 * @brief get the last element of a list
 */
t_list				*ft_lstlast(t_list *lst);

/**
 * @brief append a node to a list
 */
void				ft_lstadd_back(t_list **lst, t_list *new_l);

/**
 * @brief remove first element of list
 * @param del function to free content
 */
void				ft_lstdelone(t_list **lst, void (*del)(void *));

/**
 * @brief append a node to a list
 */
void				ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief apply function to each element of a list
 */
void				ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief apply function to each element
 * and create new list out of the function returns
 */
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/**
 * @brief fold function to each element into one value
 */
void				*ft_lstfold(t_list *lst, void *acc, void *(*f)(void *,
							void *));

//! @brief removes the first list element from the list and returns its content;
// returns NULL if list is empty;
void				*ft_lst_pop(t_list **lst);

//! @brief removes the first list element from the list and returns its content;
// returns NULL if list is empty;
void				ft_lst_push(t_list **lst, void *new_el);

t_arr				*ft_lst2arr(t_list *head);

//!@}
#endif
