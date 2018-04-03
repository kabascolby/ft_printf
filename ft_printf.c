/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 20:15:32 by lkaba             #+#    #+#             */
/*   Updated: 2018/04/02 18:05:10 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_printf(char *s, ...)
{
    size_t i;
    i = 0;
    t_p     p;
    char *s2;
    
    if(!s || !(*s))
        return (0);
    ft_bzero(&p, sizeof(t_p));
    p.s3 = s;
    s2 = ft_strdup(s); 
    va_start(p.ap, s);
    
    while (*s && !(i = 0))
    {
        ft_bzero(&p.f, sizeof(t_args));
        while (s[i] && s[i] != '%')
            ++i;
        ft_addnode(&p, s2, i);
        if (s[i] == '%')
        {
            s = ft_parse1(s + i + 1, &p);
            s2 = ft_strdup(s);
        }
        else
            s = s + i;
    }
    va_end(p.ap);
    return (ft_nodeprint(&p));
}