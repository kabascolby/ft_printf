/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 17:36:05 by lkaba             #+#    #+#             */
/*   Updated: 2018/03/30 04:19:28 by lkaba            ###   ########.fr       */
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
	if (CE_5(p->f.type, 'd', 'i', '%', 's', 'S') || CE_5(p->f.type, 'C', 'c', 'D', 'x', 'X') || CE_5(p->f.type, 'o', 'O', 'p', 'u', 'U' ))
	{
		char f[p->f.field_w ? p->f.field_w + 1 : 1];
		(p->f.space && CE_2(p->f.type, 'd', 'i')) ? p->f.str = ft_frsplitstr(&p->f.str, 1, " ") : 0;
		p->f.plus ? p->f.str = ft_frsplitstr(&p->f.str, 1 , "+") : 0;
		p->f.len = ft_strlen(p->f.str);
		p->f.field_w = (p->f.field_w < p->f.len) ? 0 : p->f.field_w - p->f.len;
		p->f.field_w -= (p->f.hash && p->f.field_w && CE_3(p->f.type, 'x', 'X', 'p')) ? 2 : 0;
		p->f.field_w -= (p->f.hash && p->f.field_w && CE_2(p->f.type, 'o', 'O')) ? 1  : 0;	
		f[p->f.field_w] = '\0';
		p->f.fw = p->f.zero ? '0' : ' ';
		ft_memset((char *)f, p->f.fw, p->f.field_w);
		p->f.pos = p->f.min ? p->f.len + 1 : (1 + p->f.plus + p->f.sign);
		p->f.str = ft_frsplitstr(&p->f.str, p->f.pos , f);
	}
	if(CE_2(p->f.type, 'o', 'O') && p->f.hash)
		p->f.str = p->f.type == 'o' && p->f.str[0] != '0' ? ft_frsplitstr(&p->f.str, 1, "0") :  p->f.str;
	if(CE_3(p->f.type, 'x', 'X', 'p') && p->f.hash)
	{
		p->f.pos = !p->f.zero && !p->f.min  ? p->f.field_w + 1 : 1;
		p->f.str =  p->f.types.um ? ft_frsplitstr(&p->f.str, p->f.pos, (p->f.type == 'X' ? "0X" : "0x")) : p->f.str;
	}
}