/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eujeong <eujeong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:11:51 by eujeong           #+#    #+#             */
/*   Updated: 2022/12/22 14:13:43 by eujeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define FLAG_MINUS 1
# define FLAG_PLUS 2
# define FLAG_SPACE 4
# define FLAG_NUMBERSIGN 8
# define FLAG_ZERO 16
# define FLAGS "-+ #0"
# define FORMAT_TPYE "cspdiuxX%"
# define HEX_LOW "0123456789abcdef"
# define HEX_UPP "0123456789ABCDEF"

typedef unsigned int	t_uint;
typedef unsigned long	t_ulong;

typedef struct s_format
{
	int		flag;
	int		width;
	int		prec;
	char	type;
}	t_format;

int		ft_printf(const char *str, ...);

int		ft_format_len(char *str);
int		ft_put_format(char *str, va_list ap);
void	ft_set_format(t_format *foramt, char *str);
void	ft_set_flag(t_format *format, char c);

int		ft_put_data(t_format *format, va_list ap);
int		ft_put_char_format(t_format *format, int c);
int		ft_put_str_format(t_format *format, char *str);
int		ft_put_int_format(t_format *format, int num);
int		ft_put_uint_format(t_format *format, t_uint unum);
int		ft_put_pointer_format(t_format *format, t_ulong p);
int		ft_put_hex_format(t_format *format, t_uint unum);

int		ft_put_padding(int size, int flag_zero);
int		ft_put_sign(int sign, int flag);
int		ft_putnbr_prec(t_uint unum, int prec);
int		ft_putnbr_hex_prec(t_ulong nbr, char *base, int prec);
int		ft_put_zero_x(char x);

int		ft_max(int a, int b);
int		ft_min(int a, int b);
t_uint	ft_abs(int num);
int		ft_disits_len(char *str);
int		ft_uint_len_prec(t_uint nbr, int prec);
int		ft_nbrlen_hex_prec(t_ulong nbr, int prec);

#endif