/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_help.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:25:50 by abadidi           #+#    #+#             */
/*   Updated: 2022/03/01 22:12:24 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philo_help(t_philo *philo)
{
	while (1)
	{
		print("is thinking", philo);
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->next->fork);
		print("has taken a fork", philo);
		print("has taken a fork", philo);
		pthread_mutex_lock(&philo->eat_mutex);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->eat_mutex);
		print("is eating", philo);
		my_sleep(philo->config->time_to_eat * 1000);
		philo->eaten++;
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		print("is sleeping", philo);
		my_sleep(philo->config->time_to_sleep * 1000);
		if (philo->eaten == philo->config->how_many_eat)
			break ;
	}
	pthread_mutex_lock(&philo->is_finshed_mutex);
	philo->is_finshed = 1;
	pthread_mutex_unlock(&philo->is_finshed_mutex);
	return (NULL);
}

void	*ft_philo(void *data)
{
	t_philo		*philo;

	philo = data;
	philo->eaten = 0;
	if (philo->id % 2)
		my_sleep(5);
	ft_philo_help(philo);
	pthread_mutex_lock(&philo->config->finished_mutex);
	philo->config->finish++;
	pthread_mutex_unlock(&philo->config->finished_mutex);
	return (NULL);
}
