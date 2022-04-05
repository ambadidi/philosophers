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


void *check_death(void *a)
{   

    t_philo  *philo = (t_philo *)a;

    while  (1)
    {

        if (get_time() - philo->last_meal > (philo->config->time_to_die * 1000))
        {
            print("DIE ", philo);
			sem_wait(philo->config->msg);
            exit(1);
        }
    }
    return NULL;
}

void	*ft_philo_help(t_philo *philo)
{
	while (1)
	{
		print("is thinking", philo);
		sem_wait(philo->config->forks);
		sem_wait(philo->config->forks);
		print("has taken a fork", philo);
		print("has taken a fork", philo);
		pthread_mutex_lock(&philo->eat_mutex);
		philo->last_meal = get_time();
		pthread_mutex_unlock(&philo->eat_mutex);
		print("is eating", philo);
		my_sleep(philo->config->time_to_eat * 1000);
		philo->eaten++;
		sem_post(philo->config->forks);
		sem_post(philo->config->forks);
		print("is sleeping", philo);
		my_sleep(philo->config->time_to_sleep * 1000);
		if (philo->eaten == philo->config->how_many_eat)
			break ;
	}
	return (NULL);
}

void	*ft_philo(void *data)
{
	t_philo		*philo;

	philo = data;
	philo->eaten = 0;
	if (philo->id % 2)
		my_sleep(5);
	pthread_create(&philo->tid, NULL, check_death, (void *) philo);
	ft_philo_help(philo);
	exit(0);
	return (NULL);
}
