/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 21:58:31 by abadidi           #+#    #+#             */
/*   Updated: 2022/03/01 22:50:38 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_finshed(t_config *config)
{
	int	ret;

	pthread_mutex_lock(&config->finished_mutex);
	ret = config->finish;
	pthread_mutex_unlock(&config->finished_mutex);
	return (ret);
}

int	get_isfinshed(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->is_finshed_mutex);
	ret = philo->is_finshed;
	pthread_mutex_unlock(&philo->is_finshed_mutex);
	return (ret);
}

void	monitoring(t_config *config, t_philo **list)
{
	int		i;

	i = 0;
	while (i < config->number)
	{
		pthread_mutex_lock(&list[i]->eat_mutex);
		if (get_isfinshed(list[i]) == 0
			&& get_time() - list[i]->last_meal > (config->time_to_die * 1000))
		{
			pthread_mutex_unlock(&list[i]->eat_mutex);
			print("died", list[i]);
			pthread_mutex_lock(&config->msg);
			break ;
		}
		pthread_mutex_unlock(&list[i]->eat_mutex);
		if (config->how_many_eat != 0 && get_finshed(config) == config->number)
		{
			pthread_mutex_lock(&config->msg);
			printf("FINSHED\n");
			break ;
		}
		i = (i +1) % config->number;
		usleep(2);
	}
}

void	my_sleep(long long interv)
{
	long	start;

	start = get_time();
	while (get_time() - start < interv)
	{
		usleep(100);
	}
}
