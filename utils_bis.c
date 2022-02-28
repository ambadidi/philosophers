/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:02:11 by abadidi           #+#    #+#             */
/*   Updated: 2022/02/28 22:49:09 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	start;

	if (gettimeofday(&start, NULL))
		return (0);
	return (1000000 * start.tv_sec + start.tv_usec);
}

void	print(char *str, t_philo *philo)
{
	long	time;

	time = (get_time() - philo->config->start) / 1000;
	printf("%ld- philosopher %d is %s\n", time, philo->id, str);
}

static	void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*dest;

	dest = str;
	while (n--)
	{
		*dest = (unsigned char)c;
		dest++;
	}
	return (str);
}

void	ft_bzero(void *str, size_t n)
{
	ft_memset(str, 0, n);
}
