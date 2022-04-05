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
