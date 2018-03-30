/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaba <lkaba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 20:15:44 by lkaba             #+#    #+#             */
/*   Updated: 2018/03/30 02:51:33 by lkaba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_PRINTF_H
# define _FT_PRINTF_H
# include "libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# define NUM(c) ((c) - '0')
# define NUMBERSET "0123456789abcdef0123456789ABCDEF"

# define CE_(a, b) ((a) == (b))
# define CE_2(a, b, c) (CE_(a, b) || CE_(a, c))
# define CE_3(a, b, c, d) (CE_(a, b) || CE_(a, c) || CE_(a, d))
# define CE_4(a, b, c, d, e) (CE_2(a, b, c) || CE_2(a, d, e))
# define CE_5(a, b, c, d, e, f) (CE_3(a, b, c, d) || CE_2(a, e, f))

typedef union  s_values
{
	wchar_t 	wc;
	char 		c;
	char 		*str;
	wchar_t 	*ws;
	int64_t		im;
	uintmax_t 	um;
	void		*p;
}			t_value;

typedef struct s_pfnode
{
    int             c;
    char            *s;
    struct s_pfnode *next;
}               t_pfnode;

typedef struct 		s_args
{
	u_int8_t 		min;
	u_int8_t 		plus;
	u_int8_t 		space;
	u_int8_t 		hash;
	u_int8_t 		zero;
	u_int8_t 		start;
	u_int8_t 		prec;
	unsigned int 	field_w;
	unsigned int 	precis;
	unsigned int 	length;
	char 			type;
	char 			*str;
	unsigned int	sign;
	unsigned int	len;
	int 			pos;
	char 			fw;
	t_value			types;
} 					t_args;

typedef struct		s_printf
{
	t_args			f;
	va_list			ap;
	t_pfnode		*head;
	char			*s3;
}					t_p;

enum 		length{H = 1, HH, L, LL, J, Z};
void 		ft_addnode(t_p *p, char *s1, size_t len);
//void 		ft_addnode(char *s1, int len, t_pfnode **head);
int 		ft_printf(char *s, ...);
int 		ft_nodeprint(t_p *p);
void 		ft_reverse(t_p *p);
char 		*ft_parse1(char *s, t_p *p);
char 		*ft_parse2(char *s, t_p *p);
char 		*ft_parse3(char *s, t_p *p);
char 		*ft_parse4(char *s, t_p *p);
void 		ft_conversion(t_p *p);
//ft_struct_check(t_args *flags);
void 		format_conversion(t_p *p);
void 		format_conversion2(t_p *p);
void 		format_conversion3(t_p *p);
void 		ft_precision(t_p *p);
void 		ft_field_width(t_p *p);
void 		flags_space_sign(t_p *p);
void 		flags_zero(t_p *p);
char 		*ft_frsplitstr(char **s, int j, char *s2);
char		*ft_uitoabase(uintmax_t val, int base, int opt);
#endif