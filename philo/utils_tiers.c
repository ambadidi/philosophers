/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tiers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:50:55 by abadidi           #+#    #+#             */
/*   Updated: 2022/03/01 22:50:59 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	ft_iswhitespace(int c)
{
	if (c == '\t' || c == '\r' || c == '\n'
		|| c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

long	long	ft_atoi(char const *s)
{
	long long	nbr;
	long		sign;
	int			i;

	i = 0;
	sign = 1;
	nbr = 0;
	while (ft_iswhitespace((int)s[i]) && s[i])
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
		{
			sign = -1;
			nbr = -nbr;
		}
		i++;
	}
	while (ft_isdigit(s[i]) && s[i])
		nbr = nbr * 10 + (s[i++] - 48);
	return (nbr * sign);
}
