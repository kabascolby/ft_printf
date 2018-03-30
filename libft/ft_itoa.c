/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:03:54 by lkaba             #+#    #+#             */
/*   Updated: 2018/03/30 02:56:44 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static size_t	digit_count(int64_t n)
{
	size_t i;

	i = 1;
	if (n < 0)
		n = -n;
	while (n >= 10)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char			*ft_itoa(int64_t n)
{
	size_t	count;
	char	*str;
	char	neg;

	neg = (n < 0 ? 1 : 0);
	count = digit_count(n);
	str = ft_strnew(count + neg);
	if (str == NULL)
		return (NULL);
	if (neg)
	{
		n = -n;
		str[0] = '-';
	}
	while (count > 0)
	{
		str[neg ? count-- : --count] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
