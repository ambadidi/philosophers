/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:29:43 by abadidi           #+#    #+#             */
/*   Updated: 2022/02/28 23:07:15 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include "philo.h"
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/time.h>
# define NUM_PHILO	4

typedef struct s_config
{
	long	number;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	how_many_eat;
	long	start;
}				t_config;

typedef struct s_philo
{
	pthread_t		tid;
	long long		last_meal;
	unsigned int	id;
	t_config		*config;
	pthread_mutex_t	fork;
	struct s_philo	*prev;
	struct s_philo	*next;
}				t_philo;

long long	ft_atoi(char const *s);
long		get_time(void);
void		print(char *str, t_philo *philo);
void		ft_bzero(void *str, size_t n);
void		*ft_philo(void *data);
t_config	*pars(int argc, char **argv);
t_philo		**init_philo(t_config *config);
void		monitoring(t_config *config, t_philo **list);
void		create_threads(t_config *config, t_philo *philo);

#endif