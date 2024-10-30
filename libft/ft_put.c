/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rparodi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:13:14 by rparodi           #+#    #+#             */
/*   Updated: 2024/03/15 14:22:53 by rparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_putchar(int fd, char c, int *ret_value)
{
	write(fd, &c, 1);
	(*ret_value)++;
}

void	ft_putnbr(int fd, int nb, int *ret_value)
{
	if (nb < 0)
	{
		if (nb == INT_MIN)
		{
			write(fd, "-2147483648", 11);
			*ret_value += 11;
			return ;
		}
		nb = -nb;
		ft_putchar(fd, '-', ret_value);
	}
	if (nb >= 10)
	{
		ft_putnbr(fd, nb / 10, ret_value);
		nb = nb % 10;
	}
	if (nb < 10)
		ft_putchar(fd, nb + 48, ret_value);
}

void	ft_putnbr_base(\
		unsigned long long nbr, char *base, int *ret_value, char c)
{
	if (c == 'p')
	{
		if (nbr != 0)
			ft_putstr(1, "0x", ret_value);
		else if (nbr == 0)
		{
			ft_putstr(1, "(nil)", ret_value);
			return ;
		}
		c++;
	}
	if (c != 'p')
	{
		if (nbr >= 16)
			ft_putnbr_base(nbr / 16, base, ret_value, c);
		ft_putchar(1, base[nbr % 16], ret_value);
	}
}

void	ft_putnbr_unsigned(int fd, unsigned int nb, int *ret_value)
{
	if (nb >= 10)
	{
		ft_putnbr_unsigned(fd, nb / 10, ret_value);
		nb = nb % 10;
	}
	if (nb < 10)
		ft_putchar(fd, nb + 48, ret_value);
}

void	ft_putstr(int fd, char *str, int *ret_value)
{
	if (!str)
		*ret_value += write(fd, "(null)", 6);
	else
		*ret_value += write(fd, str, ft_strlen(str));
}
