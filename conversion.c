/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 04:13:13 by lkaba             #+#    #+#             */
/*   Updated: 2018/04/03 19:47:54 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

wchar_t		*ft_wstrdup(wchar_t *ws)
{
    wchar_t *tmp;
    int     i;

	if (!ws)
		return (NULL);
	i = -1;
	while (ws[++i])
		;
    if (!(tmp = (wchar_t *)ft_strnew(sizeof(wchar_t) * i)))
        return (NULL);
    i = -1;
    while (ws[++i])
        tmp[i] = ws[i];
    tmp[i] = L'\0';
    return (tmp);
}

void ft_conversion(t_p *p)
{	
	if (((p->f.type == 's') && (p->f.length == L)) || ((p->f.type == 'S')))
	{
		p->f.types.ws = ft_wstrdup((wchar_t *)va_arg(p->ap, wchar_t *));
		p->f.types.ws = !(p->f.types.ws) ? ft_wstrdup(L"(null)") : p->f.types.ws; // Test it later
	}
	else if (((p->f.type == 'c') && (p->f.length == L)) || ((p->f.type == 'C')))
		p->f.types.wc = (wchar_t)va_arg(p->ap, wchar_t);
	else if (p->f.type == 's')
	{
		p->f.str = ft_strdup((char *)va_arg(p->ap, char *));
		p->f.str = !(p->f.str) ? ft_strdup("(null)") : p->f.str;
	}
	else if (CE_3(p->f.type, 'd', 'i', 'D'))
		p->f.types.im = (int64_t)va_arg(p->ap, int64_t);		
	else if((CE_5(p->f.type, 'o', 'u', 'x', 'O', 'U')) || (CE_3(p->f.type, 'X', 'p', 'b')))
		p->f.types.um = (uintmax_t)va_arg(p->ap, uintmax_t);
	else if(p->f.type == '%')
			p->f.str = ft_strdup("%");
	else if(p->f.type == 'c')
		p->f.types.c = (char)va_arg(p->ap, int);
	else
		return ;
	p->f.length = CE_5(p->f.type, 'D', 'O', 'U', 'S', 'C') || (p->f.type == 'p') ? L : p->f.length;	
	ft_field_width(p);
}

void format_conversion(t_p *p)
{	
	if(CE_3(p->f.type, 'd', 'i', 'D'))
	{
		p->f.sign = ((int)p->f.types.im < 0) ? 1 : p->f.sign;
		p->f.plus = p->f.sign ? 0 : p->f.plus;
		p->f.str = (!p->f.length) ? ft_itoa((int)p->f.types.im) : p->f.str;
		p->f.str = (p->f.length == H) ? ft_itoa((short)p->f.types.im) : p->f.str;
		p->f.str = (p->f.length == HH) ? ft_itoa((signed char)p->f.types.im) : p->f.str;
		p->f.str = (p->f.length == L) ? ft_itoa((long)p->f.types.im) : p->f.str;
		p->f.str = (p->f.length == LL) ? ft_itoa((long long)p->f.types.im) : p->f.str;
		p->f.str = (p->f.length == J) ? ft_itoa((int64_t)p->f.types.im) : p->f.str;
		p->f.str = (p->f.length == Z) ? ft_itoa((ssize_t)p->f.types.im) : p->f.str;
		p->f.str =  p->f.types.im == 0 && p->f.prec &&  !p->f.precis ? ft_strdup("\0") : p->f.str;
		
	}
	else if (((p->f.type == 's') && (p->f.length == L)) || ((p->f.type == 'S')))
	{
		int i;

		i = -1;
		while(p->f.types.ws[++i])
			;
		p->f.str = ft_strnew(i);
		while(i-- > -1)
			p->f.str[i] = (char)p->f.types.ws[i];
		free(p->f.types.ws);
	}
	
	format_conversion2(p);
}
void format_conversion2(t_p *p)
{
	if (((p->f.type == 'c') && (p->f.length == L)) || ((p->f.type == 'C')))
	{
		p->f.str = ft_strnew(1);
		p->f.str[0] = (char)p->f.types.wc;

	}
	if(p->f.type == 'c')
	{		
		p->f.str = ft_strnew(1);
		p->f.str[0] = p->f.types.c;
	}
	if(CE_2(p->f.type, 'u', 'U'))
	{	
		p->f.plus = 0;	
		p->f.str = (!p->f.length) ? ft_strdup(ft_uitoabase((unsigned int)p->f.types.im, 10, 0)) : p->f.str;
		p->f.str = (p->f.length == H) ? ft_strdup(ft_uitoabase((unsigned short)p->f.types.im, 10, 0)) : p->f.str;
		p->f.str = (p->f.length == HH) ? ft_strdup(ft_uitoabase((unsigned char)p->f.types.im, 10, 0)) : p->f.str;
		p->f.str = (p->f.length == L) ? ft_strdup(ft_uitoabase((unsigned long)p->f.types.im, 10, 0)) : p->f.str;
		p->f.str = (p->f.length == LL) ? ft_strdup(ft_uitoabase((unsigned long long)p->f.types.im, 10, 0)) : p->f.str;
		p->f.str = (p->f.length == J) ? ft_strdup(ft_uitoabase((intmax_t)p->f.types.im, 10, 0)) : p->f.str;
		p->f.str = (p->f.length == Z) ? ft_strdup(ft_uitoabase((uintmax_t)p->f.types.im, 10, 0)) : p->f.str;
		p->f.str =  p->f.types.um == 0 && p->f.prec &&  !p->f.precis ? ft_strdup("\0") : p->f.str;
		p->f.str =  p->f.types.um == 0 && !p->f.prec ? ft_strdup("0") : p->f.str;
	}	

	format_conversion3(p);
}

void format_conversion3(t_p *p)
{	
	if(CE_2(p->f.type, 'o', 'O'))
	{
		p->f.str = (!p->f.length) ? ft_strdup(ft_uitoabase((unsigned int)p->f.types.um, 8, 0)) : p->f.str;
		p->f.str = (p->f.length == H) ? ft_strdup(ft_uitoabase((unsigned short)p->f.types.um, 8, 0)) : p->f.str;
		p->f.str = (p->f.length == HH) ? ft_strdup(ft_uitoabase((unsigned char)p->f.types.um, 8, 0)) : p->f.str;
		p->f.str = (p->f.length == L) ? ft_strdup(ft_uitoabase((unsigned long)p->f.types.um, 8, 0)) : p->f.str;
		p->f.str = (p->f.length == LL) ? ft_strdup(ft_uitoabase((unsigned long long)p->f.types.um, 8, 0)) : p->f.str;
		p->f.str = (p->f.length == J) ? ft_strdup(ft_uitoabase((uintmax_t)p->f.types.um, 8, 0)) : p->f.str;
		p->f.str = (p->f.length == Z) ? ft_strdup(ft_uitoabase((size_t)p->f.types.um, 8, 0)) : p->f.str;
		p->f.str =  p->f.types.um == 0 && p->f.prec &&  !p->f.precis ? ft_strdup("\0") : p->f.str;
		p->f.str =  !p->f.types.um && !p->f.prec ? ft_strdup("0") : p->f.str;
		p->f.str =  !p->f.types.um  && p->f.hash && !p->f.precis ? ft_strdup("0") : p->f.str;
	}
	if(CE_3(p->f.type, 'x', 'X', 'p'))
	{		
		p->f.str = (!p->f.length) ? ft_strdup(ft_uitoabase((unsigned int)p->f.types.um, 16, 0)) : p->f.str;
		p->f.str = (p->f.length == H) ? ft_strdup(ft_uitoabase((unsigned short)p->f.types.um, 16, 0)) : p->f.str;
		p->f.str = (p->f.length == HH) ? ft_strdup(ft_uitoabase((unsigned char)p->f.types.um, 16, 0)) : p->f.str;
		p->f.str = (p->f.length == L) ? ft_strdup(ft_uitoabase((unsigned long)p->f.types.um, 16, 0)) : p->f.str;
		p->f.str = (p->f.length == LL) ? ft_strdup(ft_uitoabase((unsigned long long)p->f.types.um, 16, 0)) : p->f.str;
		p->f.str = (p->f.length == J) ? ft_strdup(ft_uitoabase((uintmax_t)p->f.types.um, 16, 0)) : p->f.str;
		p->f.str = (p->f.length == Z) ? ft_strdup(ft_uitoabase((size_t)p->f.types.um, 16, 0)) : p->f.str;
		p->f.str = p->f.type == 'X' ? ft_strupcase(p->f.str) : p->f.str;
		p->f.str =  p->f.types.um == 0 && p->f.prec &&  !p->f.precis ? ft_strdup("\0") : p->f.str;
		p->f.str =  p->f.types.um == 0 && !p->f.prec ? ft_strdup("0") : p->f.str;
	}
	p->f.str = p->f.type == 'b' ? ft_strdup(ft_uitoabase((unsigned long long)p->f.types.um, 2, 0)) : p->f.str;
	
	p->f.len =  CE_2(p->f.type, 'c', 'C') ? 1 : ft_strlen(p->f.str);
}

void ft_precision(t_p *p)
{
	if ((CE_5(p->f.type, 'd', 'i', 'D', 'o','O') || CE_5(p->f.type, 'x', 'X', 'p', 'u', 'U')) && p->f.precis)
	{
		char f[p->f.precis ? p->f.precis + 1 : 1];
		p->f.zero = 0;
		
		p->f.precis = (p->f.precis < p->f.len - p->f.sign) ? 0 : p->f.precis - p->f.len + p->f.sign;
		f[p->f.precis] = '\0';
		ft_memset((char *)f, '0', p->f.precis);
		p->f.str = ft_frsplitstr(&p->f.str, 1 + p->f.sign, f);
	}
	if((CE_2(p->f.type, 's', 'S')) && (p->f.precis < ft_strlen(p->f.str)))
		ft_memset((char *)&p->f.str[p->f.precis], 0, 1);
}