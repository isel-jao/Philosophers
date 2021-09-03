/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 22:15:16 by iseljao           #+#    #+#             */
/*   Updated: 2021/09/03 16:16:57 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_exit(t_mem mem, char *error_msj)
{
	(void)mem;
	if (error_msj == NULL)
		exit(0);
	printf("%s", error_msj);
	exit(1);
}

void clean_simulation(t_mem *mem, int status)
{

	int i;

	i = 0;
	while (i < mem->philosophers_count)
	{
		pthread_mutex_destroy(&(mem->forks[i]));
		i++;
	}
	exit(status);
}

void *check_death(void *arg)
{
	t_philo *philo;
	long int present;
	t_mem *mem;

	philo = (t_philo *)arg;
	mem = (t_mem *)(philo->mem);
	while (philo->full == 0)
	{
		present = current_time(mem);
		if (present - philo->last_time_eat > mem->time_to_die)
		{
			pthread_mutex_lock(&mem->write);
			printf("%10lums %d %-25s", present, philo->id, "has died");
			printf(" last meal %10lu\n", present - philo->last_time_eat);
		}
		usleep(500);
	}
	pthread_mutex_unlock(&mem->stop);
	return (NULL);
}

void *routine(void *arg)
{
	t_mem *mem;
	t_philo *philo;
	pthread_t death;

	philo = (t_philo *)arg;
	mem = (t_mem *)(philo->mem);
	pthread_create(&death, NULL, &check_death, philo);
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
			break;
		}
		print_status(philo, SLEEPING);
		usleep(mem->time_to_sleep * 1000);
		print_status(philo, THINKINK);
	}

	return (NULL);
}

void init_simulation(t_mem *mem)
{
	int i;

	pthread_mutex_lock(&(mem->stop));
	get_first_time(mem);
	i = 0;
	while (i < mem->philosophers_count)
	{
		if (pthread_create(&mem->philos_threads[i], NULL, &routine, &mem->philo[i]))
			exit(errno);
		if (pthread_detach(mem->philos_threads[i]))
			exit(errno);
		i += 2;
	}
	usleep(300);
	i = 1;
	while (i < mem->philosophers_count)
	{
		if (pthread_create(&mem->philos_threads[i], NULL, &routine, &mem->philo[i]))
			exit(errno);
		if (pthread_detach(mem->philos_threads[i]))
			exit(errno);
		i += 2;
	}
	pthread_mutex_lock(&(mem->stop));
}

int main(int ac, char **av)
{
	t_mem mem;

	parse(ac, av, &mem);
	init(&mem);
	init_simulation(&mem);
	clean_simulation(&mem, 0);
	return (0);
}
