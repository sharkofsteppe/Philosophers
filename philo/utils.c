/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gesperan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 20:11:51 by gesperan          #+#    #+#             */
/*   Updated: 2021/07/09 20:11:53 by gesperan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libra.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	negative;

	res = 0;
	negative = 1;
	while (*str != '\0' && (*str == '\n' || *str == '\t' || *str == '\v'
			|| *str == ' ' || *str == '\r' || *str == '\f'))
		str++;
	if (*str == '-')
	{
		negative = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	return (res * negative);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}
