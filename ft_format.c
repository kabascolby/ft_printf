/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 17:36:05 by lkaba             #+#    #+#             */
/*   Updated: 2018/04/03 19:48:42 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
	** if the flag zero is on then the field width is replaced by zero
	** '0' is ignnored when '-' is present;
	** the space depends also to the minus sign
	** space is ignnored when '+' is on
*/
void ft_field_width(t_p *p)
{
	format_conversion(p);
	p->f.prec ? ft_precision(p) : 0;
	p->f.field_w -= (!p->f.types.c && CE_2(p->f.type, 'c', 'C') && p->f.field_w > 0) ? 1 : 0;
	char f[p->f.field_w ? p->f.field_w + 1 : 1];
	p->f.str = (p->f.space && CE_2(p->f.type, 'd', 'i') && !p->f.sign) ? ft_frsplitstr(&p->f.str, 1, " ") : p->f.str;
	p->f.plus ? p->f.str = ft_frsplitstr(&p->f.str, 1, "+") : 0;
	p->f.len = ft_strlen(p->f.str);
	p->f.field_w = (p->f.field_w < p->f.len) ? 0 : p->f.field_w - p->f.len;

	p->f.field_w -= ((p->f.hash && p->f.field_w && CE_2(p->f.type, 'x', 'X')) || p->f.type == 'p') ? 2 : 0;
	p->f.field_w -= (p->f.hash && p->f.field_w && CE_2(p->f.type, 'o', 'O')) ? 1 : 0;
	p->f.field_w = p->f.field_w < 0 ? 0 : p->f.field_w;
	f[p->f.field_w] = '\0';
	p->f.fw = p->f.zero ? '0' : ' ';
	ft_memset(f, p->f.fw, p->f.field_w);
	p->f.str = p->f.zero ? ft_frsplitstr(&p->f.str, 1 + p->f.sign + p->f.plus, f) : p->f.str;
	p->f.pos = p->f.min ? p->f.len + 1 : (1 + p->f.plus - p->f.sign - p->f.plus);
	p->f.str = !p->f.zero ? ft_frsplitstr(&p->f.str, p->f.pos, f) : p->f.str;
	ft_field_width2(p);
}

void ft_field_width2(t_p *p)
{
	char *s;
	if (CE_2(p->f.type, 'o', 'O') && p->f.hash)
	{
		p->f.pos = p->f.min ? 1 : 1 + p->f.field_w;
		p->f.str = p->f.str[0] != '0' ? ft_frsplitstr(&p->f.str, p->f.pos, "0") : p->f.str;
	}
	if ((CE_2(p->f.type, 'x', 'X') && p->f.hash) || (p->f.type == 'p'))
	{
		s = p->f.type == 'X' ? "0X" : "0x";
		p->f.pos = !p->f.zero && !p->f.min ? p->f.field_w + 1 : 1;
		p->f.str = p->f.types.um || p->f.type == 'p' ? ft_frsplitstr(&p->f.str, p->f.pos, s) : p->f.str;
	}
	p->f.len = ft_strlen(p->f.str);
}