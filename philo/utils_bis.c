/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 22:02:11 by abadidi           #+#    #+#             */
/*   Updated: 2022/03/01 23:13:22 by abadidi          ###   ########.fr       */
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
	pthread_mutex_lock(&philo->config->msg);
	printf("%ld  %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->config->msg);
}

void	ft_bzero(void *str, size_t n)
{
	memset(str, 0, n);
}

int	check_config(t_config *config)
{
	if (config->number < 1)
	{
		free(config);
		return (0);
	}
	if (config->time_to_die < 0 || config->time_to_eat < 0
		|| config->time_to_sleep < 0)
	{
		free(config);
		return (0);
	}
	if (config->how_many_eat < 0)
	{
		free(config);
		return (0);
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!check_if_digit(argv[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}
