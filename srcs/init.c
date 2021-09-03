/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 21:43:29 by iseljao           #+#    #+#             */
/*   Updated: 2021/09/03 16:04:17 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(t_mem *mem)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(mem->stop), NULL);
	pthread_mutex_init(&(mem->write), NULL);
	while (i < mem->philosophers_count)
	{
		memset(&mem->philo[i], 0, sizeof(t_philo));
		pthread_mutex_init(&(mem->forks[i]), NULL);
		i++;
	}
	i = 0;
	while (i < mem->philosophers_count - 1)
	{
		mem->philo[i].id = i + 1;
		mem->philo[i].left_fork = &mem->forks[i];
		mem->philo[i].right_fork = &mem->forks[i + 1];
		mem->philo[i].mem = mem;
		i++;
	}
	mem->philo[i].id = i + 1;
	mem->philo[i].left_fork = &mem->forks[i];
	mem->philo[i].right_fork = &mem->forks[0];
	mem->philo[i].mem = mem;
}
