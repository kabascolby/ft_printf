/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 04:13:13 by lkaba             #+#    #+#             */
/*   Updated: 2018/03/28 15:54:02 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_conversion(t_p *p)
{	
	if (((p->f.type == 's') && (p->f.length == L)) || ((p->f.type == 'S') && (!p->f.length)))
		p->f.types.ws = (wchar_t *)va_arg(p->ap, wchar_t *);
	else if (((p->f.type == 'c') && (p->f.length == L)) || ((p->f.type == 'C') && (!p->f.length)))
		p->f.types.wc = (wchar_t)va_arg(p->ap, wchar_t);
	else if (p->f.type == 's')
	{
		p->f.str = (char *)va_arg(p->ap, char *);
		p->f.str = !(p->f.str) ? ft_strdup("(null)") : p->f.str;
	}
	else if (CE_2(p->f.type, 'd', 'i'))
		p->f.types.im = (int)(intmax_t)va_arg(p->ap, intmax_t);		
	else if((CE_5(p->f.type, 'o', 'u', 'x', 'O', 'U')) || (CE_3(p->f.type, 'X', 'D', 'p'))) // cheker le cas ou on donne les flags X et x
			p->f.types.um = (uintmax_t)va_arg(p->ap, uintmax_t);
	else if(p->f.type == '%')
			p->f.str = "%";
	else if(p->f.type == 'c')
		p->f.types.c = (char)va_arg(p->ap, int);
	else
		return ;
	ft_field_width(p);
}

void format_conversion(t_p *p)
{	
	if(CE_2(p->f.type, 'd', 'i'))
	{
		p->f.sign = p->f.types.im < 0 ? '-' : p->f.sign;
		p->f.plus = p->f.sign ? 0 : p->f.plus;
		p->f.str = ft_itoa(p->f.types.im);
	}	
	else if (((p->f.type == 's') && (p->f.length == L)) || ((p->f.type == 'S') && (!p->f.length)))
	{
		int i;

		i = -1;
		while(p->f.types.ws[++i])
			;
		p->f.str = ft_strnew(i);
		while(i-- > -1)
			p->f.str[i] = (char)p->f.types.ws[i];
		p->f.str = !(p->f.types.ws) ? ft_strdup("(null)") : p->f.str; // Test it later
	}
	else if (((p->f.type == 'c') && (p->f.length == L)) || ((p->f.type == 'C') && (!p->f.length)))
	{
		p->f.str = ft_strnew(1);
		p->f.str[0] = (char)p->f.types.wc;
	}
	format_conversion2(p);
}

void format_conversion2(t_p *p)
{
	if(p->f.type == 'c')
	{
		p->f.str = ft_strnew(1);
		p->f.str[0] = p->f.types.c; 
	}
	else if(p->f.type == 'D')
		p->f.str = ft_strdup(ft_uitoabase((uintmax_t)p->f.types.um, 10, 0));
	else if(p->f.type == 'D')
		p->f.str = ft_strdup(ft_uitoabase((uintmax_t)p->f.types.um, 10, 0));
	if(CE_2(p->f.type, 'o', 'O'))
		p->f.str = ft_strdup(ft_uitoabase((uintmax_t)p->f.types.um, 8, 0));
	if(CE_3(p->f.type, 'x', 'X', 'p'))
	{
		p->f.str = (p->f.length != L) ? ft_strdup(ft_uitoabase((int)p->f.types.um, 16, 0)) : p->f.str;
		p->f.str = (p->f.length == L) ? ft_strdup(ft_uitoabase((long)p->f.types.um, 16, 0)) : p->f.str;
		p->f.str = p->f.type == 'X' ? ft_strupcase(p->f.str) : p->f.str;
	}
	//p->f.str = p->f.str ? ft_strdup(p->f.str) : NULL;
	p->f.len = ft_strlen(p->f.str);
	
}



void ft_precision(t_p *p)
{
	if ((CE_5(p->f.type, 'd', 'i', 'D', 'o','O') || CE_3(p->f.type, 'x', 'X', 'p')) && p->f.precis)
	{
		char f[p->f.precis ? p->f.precis + 1 : 1];
		p->f.zero = 0;
		p->f.precis = (p->f.precis < p->f.len) ? 0 : p->f.precis - p->f.len;
		f[p->f.precis] = '\0';
		ft_memset((char *)f, '0', p->f.precis);
		p->f.str = ft_frsplitstr(&p->f.str, 1, f);
	}
	if((CE_2(p->f.type, 's', 'S')) && (p->f.precis < ft_strlen(p->f.str)))
		ft_memset((char *)&p->f.str[p->f.precis], 0, 1);
}