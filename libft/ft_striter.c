/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:10:17 by lkaba             #+#    #+#             */
/*   Updated: 2017/12/04 17:53:43 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striter(char *c, void (*f)(char *))
{
	if ((c == NULL) || (f == NULL))
		return ;
	while (*c)
	{
		(*f)(c);
		c++;
	}
}