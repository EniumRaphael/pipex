/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:27:44 by rparodi           #+#    #+#             */
/*   Updated: 2024/03/15 14:22:23 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_check_percent_args(int fd, char c, va_list args, int *ret_value)
{
	if (c == 'c')
		ft_putchar(fd, (char)va_arg(args, int), ret_value);
	else if (c == 's')
		ft_putstr(fd, (char *)va_arg(args, char *), ret_value);
	else if (c == 'i' || c == 'd')
		ft_putnbr(fd, (int)va_arg(args, int), ret_value);
	else if (c == '%')
		ft_putchar(fd, '%', ret_value);
	else if (c == 'u')
		ft_putnbr_unsigned(fd, \
				(unsigned int)va_arg(args, unsigned int), ret_value);
	else if (c == 'x')
		ft_putnbr_base((unsigned int)va_arg(args, unsigned int), \
				"0123456789abcdef", ret_value, c);
	else if (c == 'X')
		ft_putnbr_base((unsigned int)va_arg(args, unsigned int), \
				"0123456789ABCDEF", ret_value, c);
	else if (c == 'p')
		ft_putnbr_base((unsigned long long)va_arg(args, unsigned long long), \
				"0123456789abcdef", ret_value, c);
	va_end(args);
	return (1);
}

int	ft_fprintf(int fd, const char *s, ...)
{
	size_t	i;
	va_list	args;
	char	*str;
	int		ret_value;

	ret_value = 0;
	str = ft_strdup(s);
	va_start(args, s);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			ft_check_percent_args(fd, str[i + 1], args, &ret_value);
			i++;
		}
		else
			ft_putchar(fd, str[i], &ret_value);
		i++;
	}
	free(str);
	return (ret_value);
}
