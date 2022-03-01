/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi <abadidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:29:43 by abadidi           #+#    #+#             */
/*   Updated: 2022/03/01 23:07:38 by abadidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_config
{
	long			number;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			how_many_eat;
	long			start;
	int				finish;
	pthread_mutex_t	msg;
	pthread_mutex_t	finished_mutex;

}				t_config;

typedef struct s_philo
{
	pthread_t		tid;
	long long		last_meal;
	unsigned int	id;
	int				eaten;
	t_config		*config;
	pthread_mutex_t	fork;
	pthread_mutex_t	eat_mutex;
	struct s_philo	*next;
	int				is_finshed;
	pthread_mutex_t	is_finshed_mutex;
}				t_philo;

int			ft_isdigit(int c);
int			check_if_digit(char *str);
long long	ft_atoi(char const *s);
long		get_time(void);
void		print(char *str, t_philo *philo);
void		ft_bzero(void *str, size_t n);
void		*ft_philo_help(t_philo *philo);
void		*ft_philo(void *data);
t_config	*parse(int argc, char **argv);
void		free_config_and_philo(t_philo **list, t_config *config);
t_philo		**init_philo(t_config *config);
void		monitoring(t_config *config, t_philo **list);
void		create_threads(t_config *config, t_philo *philo);
void		my_sleep(long long inter);
int			check_config(t_config *config);
int			check_args(int argc, char **argv);
#endif
