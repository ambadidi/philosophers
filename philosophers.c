/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:29:12 by abadidi           #+#    #+#             */
/*   Updated: 2022/02/28 23:12:04 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philo(void *data)
{
	t_philo		*philo;

	philo = data;
	if (philo->id % 2)
		usleep(10);
	while (1)
	{
		print("thinking", philo);
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->next->fork);
		philo->last_meal = get_time();
		print("eating", philo);
		usleep(philo->config->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		print("sleeping", philo);
		usleep(philo->config->time_to_sleep * 1000);
	}
}

t_config	*pars(int argc, char **argv)
{
	t_config	*config;

	config = (t_config *)malloc(sizeof(t_config));
	if (config == NULL)
		exit(0);
	ft_bzero(config, sizeof(t_config));
	if (argc == 5 || argc == 6)
	{
		config->number = ft_atoi(argv[1]);
		printf("%s\n", argv[2]);
		config->time_to_die = ft_atoi(argv[2]);
		config->time_to_eat = ft_atoi(argv[3]);
		config->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			config->how_many_eat = ft_atoi(argv[5]);
	}
	return (config);
}

t_philo	**init_philo(t_config *config)
{
	int		i;
	t_philo	**list;
	int		ret;

	i = -1;
	list = (t_philo **)malloc(sizeof(t_philo *) * config->number);
	while (++i < config->number)
	{
		list[i] = malloc(sizeof(t_philo));
		ret = pthread_mutex_init(&list[i]->fork, NULL);
		list[i]->last_meal = get_time();
		if (ret != 0)
			exit(0);
		list[i]->id = i + 1;
		list[i]->config = config;
	}
	i = -1;
	while (++i < config->number)
	{
		list[i]->next = list[(i + 1) % (config->number)];
		if (i != 0)
			list[i]->prev = list[i - 1];
		else
			list[i]->prev = list[config->number - 1];
	}
	return (list);
}

void	create_threads(t_config *config, t_philo *philo)
{
	int		i;

	i = 0;
	while (i < config->number)
	{
		pthread_create(&philo->tid, NULL, ft_philo, philo);
		philo = philo->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	pthread_t	tid[NUM_PHILO];
	t_config	*config;
	t_philo		**list;
	int			i;

	config = pars(argc, argv);
	list = init_philo(config);
	config->start = get_time();
	i = 0;
	create_threads(config, list[0]);
	monitoring(config, list);
	i = -1;
	while (++i < config->number)
		pthread_join(list[i]->tid, NULL);
}
