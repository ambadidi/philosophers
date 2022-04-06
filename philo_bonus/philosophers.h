/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadidi < abadidi@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 10:29:43 by abadidi           #+#    #+#             */
/*   Updated: 2022/04/06 15:40:14 by abadidi          ###   ########.fr       */
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
#include <semaphore.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */

typedef struct s_config
{
	long			number;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			how_many_eat;
	long			start;
	int				finish;
	sem_t			*msg;
	sem_t			*forks;
}				t_config;

typedef struct s_philo
{
	pid_t			pid;
	pthread_t		tid;
	long long		last_meal;
	unsigned int	id;
	int				eaten;
	t_config		*config;
	struct s_philo	*next;
	sem_t			*eat_sem;
	int				is_finshed;
	char 			*eat_sem_name; // free
}				t_philo;

char			*ft_lltoa(long long nbr);
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
