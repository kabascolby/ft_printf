/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:12:07 by lkaba             #+#    #+#             */
/*   Updated: 2018/04/06 14:01:29 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*lstremove(t_list *lst, void *ptr)
{
	t_list *temp;

	if (!lst)
		return (NULL);
	if (lst->content == ptr)
	{
		temp = lst->next;
		ft_memdel((void **)&lst);
		return (temp);
	}
	lst->next = lstremove(lst->next, ptr);
	return (lst);
}

/*
** Removes a single node from a linked list.
*/

void			ft_lstremove(t_list **lst, void *ptr)
{
	*lst = lstremove(*lst, ptr);
}
