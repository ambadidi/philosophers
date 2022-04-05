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
#include <sys/types.h>
#include <sys/wait.h>

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
	int k = 0;
	int status;
	int stat;

    while (waitpid(-1, &stat, 0 ) && config->finish < config->number)
    {
        status = WEXITSTATUS(stat);
		if (status == 1){
			while (k < config->number)
				kill(list[k++]->pid, SIGKILL);
                break ;
        }
        else
		{
			config->finish++;
        }
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
