/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:29:12 by abadidi           #+#    #+#             */
/*   Updated: 2022/03/01 03:10:56 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philo(void *data)
{
	t_philo		*philo;

	philo = data;
	philo->eaten = 0;
	if (philo->id % 2)
		my_sleep(5);
	while (1)
	{
		print("thinking", philo);
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->next->fork);
		 pthread_mutex_lock(&philo->eat_mutex);
		philo->last_meal = get_time();
		 pthread_mutex_unlock(&philo->eat_mutex);
		print("eating", philo);
		my_sleep(philo->config->time_to_eat * 1000);
		philo->eaten++;
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		print("sleeping", philo);
		my_sleep(philo->config->time_to_sleep * 1000);
		if (philo->eaten == philo->config->how_many_eat)
			break ;
	}
	pthread_mutex_lock(&philo->config->finished_mutex);
	philo->config->finish++;
	pthread_mutex_unlock(&philo->config->finished_mutex);
	return NULL;
}

t_config	*parse(int argc, char **argv)
{
	t_config	*config;

	config = (t_config *)malloc(sizeof(t_config));
	if (config == NULL)
		exit(0);
	ft_bzero(config, sizeof(t_config));
	if (argc == 5 || argc == 6)
	{
		config->number = ft_atoi(argv[1]);
		config->time_to_die = ft_atoi(argv[2]);
		config->time_to_eat = ft_atoi(argv[3]);
		config->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			config->how_many_eat = ft_atoi(argv[5]);
	}
	return (config);
}

void	check_config(t_config *config)
{
	if (config->number < 1)
	{
		free(config);
		exit(0);
	}
	if (config->time_to_die < 0 || config->time_to_eat < 0 || config->time_to_sleep < 0)
	{
		free(config);
		exit(0);
	}
	if (config->how_many_eat < 0)
	{
		free(config);
		exit(0);
	}
}

void	free_config_and_philo(t_philo **list, t_config *config)
{
	int	i;

	i = 0;
	while (i < config->number)
	{
		pthread_mutex_destroy(&list[i]->fork);
		pthread_mutex_destroy(&list[i]->eat_mutex);
		free(list[i]);
		i++;
	}
	pthread_mutex_destroy(&config->msg);
	pthread_mutex_destroy(&config->finished_mutex);
	free(list);
	free(config);
}

t_philo	**init_philo(t_config *config)
{
	int		i;
	t_philo	**list;

	i = -1;
	list = (t_philo **)malloc(sizeof(t_philo *) * config->number);
	while (++i < config->number)
	{
		list[i] = malloc(sizeof(t_philo));
		pthread_mutex_init(&list[i]->fork, NULL);
		pthread_mutex_init(&list[i]->eat_mutex, NULL);
		list[i]->last_meal = get_time();
		list[i]->id = i + 1;
		list[i]->config = config;
	}
	i = -1;
	while (++i < config->number)
	{
		list[i]->next = list[(i + 1) % (config->number)];
	}
	return (list);
}

void	create_threads(t_config *config, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < config->number)
	{
		pthread_create(&philo->tid, NULL, (void *)ft_philo, philo);
		philo = philo->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_config	*config;
	t_philo		**list;

	config = parse(argc, argv);
	check_config(config);
	list = init_philo(config);
	config->start = get_time();
	pthread_mutex_init(&config->msg, NULL);
	pthread_mutex_init(&config->finished_mutex, NULL);
	create_threads(config, list[0]);
	monitoring(config, list);
	free_config_and_philo(list, config);
}
