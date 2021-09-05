/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 22:15:16 by iseljao           #+#    #+#             */
/*   Updated: 2021/09/05 17:06:36 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_simulation(t_mem *mem, int status)
{
	int	i;

	i = 0;
	while (i < mem->philosophers_count)
	{
		pthread_mutex_destroy(&(mem->forks[i]));
		i++;
	}
	exit(status);
}

void	*check_death(void *arg)
{
	t_philo		*philo;
	long int	present;
	t_mem		*mem;

	philo = (t_philo *)arg;
	mem = (t_mem *)(philo->mem);
	while (philo->full == 0)
	{
		present = current_time(mem);
		if (present - philo->last_time_eat > mem->time_to_die)
		{
			pthread_mutex_lock(&mem->write);
			printf("%10lums %d %-25s\n", present, philo->id, "has died");
			break ;
		}
		usleep(500);
	}
	pthread_mutex_unlock(&mem->stop);
	return (NULL);
}

void	handle_threads(t_mem *mem, t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, RFORK);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, LFORK);
		philo->last_time_eat = current_time(mem);
		philo->eat_counter++;
		print_status(philo, EATING);
		usleep(mem->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (mem->option_specified && philo->eat_counter >= mem->eating_count)
		{
			philo->full = 1;
			break ;
		}
		print_status(philo, SLEEPING);
		usleep(mem->time_to_sleep * 1000);
		print_status(philo, THINKINK);
	}
}

void	*routine(void *arg)
{
	t_mem		*mem;
	t_philo		*philo;
	pthread_t	death;

	philo = (t_philo *)arg;
	mem = (t_mem *)(philo->mem);
	pthread_create(&death, NULL, &check_death, philo);
	handle_threads(mem, philo);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_mem	mem;

	parse(ac, av, &mem);
	init(&mem);
	init_simulation(&mem);
	clean_simulation(&mem, 0);
	return (0);
}
