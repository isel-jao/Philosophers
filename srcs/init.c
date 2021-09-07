/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 21:43:29 by iseljao           #+#    #+#             */
/*   Updated: 2021/09/07 16:12:25 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_init(t_mem *mem)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(mem->stop), NULL);
	pthread_mutex_init(&(mem->write), NULL);
	pthread_mutex_init(&(mem->full_lock), NULL);
	while (i < mem->philosophers_count)
	{
		memset(&mem->philo[i], 0, sizeof(t_philo));
		pthread_mutex_init(&(mem->forks[i]), NULL);
		i++;
	}
}

void	init(t_mem *mem)
{
	int	i;

	lock_init(mem);
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

void	init_simulation(t_mem *mem)
{
	int	i;

	pthread_mutex_lock(&(mem->stop));
	get_first_time(mem);
	i = 0;
	while (i < mem->philosophers_count)
	{
		if (pthread_create(&mem->philos_threads[i], NULL, &routine, \
			&mem->philo[i]))
			exit(errno);
		if (pthread_detach(mem->philos_threads[i]))
			exit(errno);
		i += 2;
		if (i >= mem->philosophers_count && i % 2 == 0)
		{
			usleep(300);
			i = 1;
		}
	}	
	pthread_mutex_lock(&(mem->stop));
}
