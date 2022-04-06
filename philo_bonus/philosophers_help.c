/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_help.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi < abadidi@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:25:50 by abadidi           #+#    #+#             */
/*   Updated: 2022/04/06 15:53:51 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *check_death(void *a)
{   

    t_philo  *philo = (t_philo *)a;

    while  (1)
    {
		sem_wait(philo->eat_sem);
        if (get_time() - philo->last_meal > (philo->config->time_to_die * 1000))
        {
			//pthread_mutex_unlock(&philo->eat_mutex);
            sem_post(philo->eat_sem);
			print("DIE ", philo);
			sem_wait(philo->config->msg);
            exit(1);
        }
			sem_post(philo->eat_sem);
		usleep(5);
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
		sem_wait(philo->eat_sem);
		philo->last_meal = get_time();
		sem_post(philo->eat_sem);
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
