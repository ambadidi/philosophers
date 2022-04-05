/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:29:12 by abadidi           #+#    #+#             */
/*   Updated: 2022/03/01 22:49:10 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_config	*parse(int argc, char **argv)
{
	t_config	*config;

	if ((argc == 5 || argc == 6) && check_args(argc, argv))
	{
		config = (t_config *)malloc(sizeof(t_config));
		ft_bzero(config, sizeof(t_config));
		config->number = ft_atoi(argv[1]);
		config->time_to_die = ft_atoi(argv[2]);
		config->time_to_eat = ft_atoi(argv[3]);
		config->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
		{
			config->how_many_eat = ft_atoi(argv[5]);
			if (config->how_many_eat == 0)
				return (NULL);
		}
		return (config);
	}
	return (NULL);
}

void	free_config_and_philo(t_philo **list, t_config *config)
{
	int	i;

	i = 0;
	while (i < config->number)
	{
		// pthread_mutex_destroy(&list[i]->fork);
		// pthread_mutex_destroy(&list[i]->eat_mutex);
		free(list[i]);
		i++;
	}
	// pthread_mutex_destroy(&config->msg);
	// pthread_mutex_destroy(&config->finished_mutex);
	 sem_unlink("message");
	 sem_unlink("forks");
	free(list);
	free(config);
}

t_philo	**init_philo(t_config *config)
{
	int		i;
	t_philo	**list;

	i = -1;
	sem_unlink("message");
	sem_unlink("forks");
	list = (t_philo **)malloc(sizeof(t_philo *) * config->number);
	while (++i < config->number)
	{
		list[i] = malloc(sizeof(t_philo));
		list[i]->last_meal = get_time();
		list[i]->id = i + 1;
		list[i]->is_finshed = 0;
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
		// pthread_create(&philo->tid, NULL, (void *)ft_philo, philo);
		philo->pid = fork();
		if (philo->pid == 0)
		{
			ft_philo(philo);
			exit(0);
		}
		philo = philo->next;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_config	*config;
	t_philo		**list;

	config = parse(argc, argv);
	if (!config)
		return (1);
	if (check_config(config) == 0)
		return (1);
	list = init_philo(config);
	config->start = get_time();
	// pthread_mutex_init(&config->msg, NULL);
	config->msg = sem_open("message",  O_CREAT | O_EXCL, 0666,1);
	config->forks = sem_open("forks",  O_CREAT | O_EXCL, 0666, config->number);
	if (config->msg  == SEM_FAILED ||  config->forks  == SEM_FAILED)
	{
		perror("semphore :");
		exit(0);
	}
	
	pthread_mutex_init(&config->finished_mutex, NULL);
	create_threads(config, list[0]);
	monitoring(config, list);
	free_config_and_philo(list, config);
	return (0);
}
