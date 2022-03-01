/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 21:58:31 by abadidi           #+#    #+#             */
/*   Updated: 2022/03/01 03:13:04 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isdigit(int c)
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

void	monitoring(t_config *config, t_philo **list)
{
	int		i;

	i = 0;
	while (i < config->number)
	{
		pthread_mutex_lock(&list[i]->eat_mutex);
		if (get_time() - list[i]->last_meal > (config->time_to_die * 1000))
		{
			pthread_mutex_unlock(&list[i]->eat_mutex);
			print("DEATH", list[i]);
			pthread_mutex_lock(&config->msg);
			break ;
		}
		pthread_mutex_unlock(&list[i]->eat_mutex);
		pthread_mutex_lock(&config->finished_mutex);
		if (config->how_many_eat != 0 && config->finish == config->how_many_eat)
		{
			pthread_mutex_lock(&config->msg);
			printf("FINSHED\n");
			break ;
		}
		pthread_mutex_unlock(&config->finished_mutex);
		i = (i +1) % config->number ;
	}
}

void	my_sleep(long long interv)
{
	long start = get_time();

	while ( get_time() - start  < interv)
	{
		usleep(5);
	}
}
