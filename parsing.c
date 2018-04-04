/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 20:15:37 by lkaba             #+#    #+#             */
/*   Updated: 2018/04/03 17:17:59 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *ft_parse1(char *s, t_p *p)
{
	while (*s)
	{
		p->f.hash = *s == '#' ? 1 : p->f.hash;
		p->f.min = *s == '-' ? 1 : p->f.min;
		p->f.plus = *s == '+' ? 1 : p->f.plus;
		p->f.zero = *s == '0' ? 1 : p->f.zero;
		p->f.space = *s == ' ' ? 1 : p->f.space;

		if (!CE_5(*s, '#', '-', '+', ' ', '0'))
			break;
		s++;
	}
	/** if plus is on then the space is off, if min is on then zero is off **/
	p->f.space = p->f.plus ? 0 : p->f.space;
	p->f.zero = p->f.min ? 0 : p->f.zero;
	
	 //this behavior is define in the man but the implementaton is opposite might see later
	return (ft_parse2(s, p));
}
char *ft_parse2(char *s, t_p *p)
{
	while (ft_isdigit(*s))
		p->f.field_w = (10 * p->f.field_w) + NUM(*(s++));
	//printf("string %s\n", s);
	/* else if (*s == '*')
		{
			length = va_arg(*argp, int);s
			*++fmt;
			if (length < 0)
			{
				ladjust = !ladjust;
				length = -length;
			}
		} */
	if (*s == '.')
	{
		s++;
		p->f.prec = 1;
		while (ft_isdigit(*s))
			p->f.precis = (10 * p->f.precis) + NUM(*(s++));
		p->f.zero = 0;
	}
	//s++;
	return (ft_parse3(s, p));
}

char *ft_parse3(char *s, t_p *p)
{
	int k;

	k = 1;
	((*s == 'h') && (*(s + 1) != 'h')) ? p->f.length = H : 1;
	((*s == 'l') && (*(s + 1) != 'l')) ? p->f.length = L : k;
	(*s == 'j') ? p->f.length = J : k;
	(*s == 'z') ? p->f.length = Z : k;
	if ((*s == 'h') && *(s + 1) == 'h')
	{
		p->f.length = HH;
		s++;
	}
	if ((*s == 'l') && *(s + 1) == 'l')
	{
		p->f.length = LL;
		s++;
	}
	if (CE_4(*s, 'h', 'l', 'j', 'z'))
		s++;
	return (ft_parse4(s, p));
}

char *ft_parse4(char *s, t_p *p)
{
	if (CE_5(*s, 's', 'S', 'p', 'd', 'D') || CE_5(*s, 'i', 'o', 'O', 'u', 'U') ||
		CE_5(*s, 'x', 'X', 'c', 'C', '%') || *s == 'b')
	{
		//char str[]="s, S, p, d, D, i, o, O, u, U, x, X, c, C, %";
		p->f.type = *s;
		s++;
	}
	else
		return (s);		
	ft_conversion(p);
	
	ft_addnode(p, p->f.str, p->f.len);
	return (s);
}
