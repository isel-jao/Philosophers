/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iseljao <iseljao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 22:15:16 by iseljao           #+#    #+#             */
/*   Updated: 2021/09/02 17:35:10 by iseljao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_exit(t_mem mem, char *error_msj)
{
	if (error_msj == NULL)
		exit(0);
	printf("%s", error_msj);
	exit(1);
}

void parse(int ac, char **av, t_mem *mem)
{
	int i;

	memset(mem, 0, sizeof(t_mem));
	if (ac != 5 && ac != 6)
		ft_exit(*mem, "wrong number of arguments\n");
	mem->philosophers_count = atoi(av[1]);
	mem->time_to_die = atoi(av[2]);
	mem->time_to_eat = atoi(av[3]);
	mem->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		mem->eating_count = atoi(av[5]);
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

void init_locks(t_mem *mem)
{
	int i;

	i = 0;
	pthread_mutex_init(&(mem->stop), NULL);
	pthread_mutex_init(&(mem->write), NULL);
	while (i < mem->philosophers_count)
	{
		pthread_mutex_init(&(mem->forks[i]), NULL);
		i++;
	}
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

void get_first_time(t_mem *mem)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	mem->t0.tv_sec = tv.tv_sec;
	mem->t0.tv_usec = tv.tv_usec;
	mem->big_bang = tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
long unsigned current_time(t_mem *mem)
{
	struct timeval t1;
	gettimeofday(&t1, NULL);
	return (t1.tv_sec * 1000 + t1.tv_usec / 1000 - mem->big_bang);
	return ((t1.tv_sec - mem->t0.tv_sec) * 1000.0f + (t1.tv_usec - mem->t0.tv_usec) / 1000.0f);
}

void *check_death(void *arg)
{
	t_philo *philo;
	t_mem *mem;

	philo = (t_philo *)arg;
	mem = (t_mem *)(philo->mem);
	while (1)
	{
		if (current_time(mem) - philo->last_time_eat > mem->time_to_die)
		{
			pthread_mutex_lock(&mem->write);
			printf("%lums %d has died\n", current_time(mem), philo->id);
			pthread_mutex_unlock(&mem->stop);
			printf("%lums %d has died\n", current_time(mem), philo->id);
		}
		usleep(5000);
	}
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
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&mem->write);
	printf("%lums %d has taken his right fork\n", current_time(mem), philo->id);
	pthread_mutex_unlock(&mem->write);
	pthread_mutex_lock(philo->left_fork);
	printf("%lums %d has taken his left fork\n", current_time(mem), philo->id);
	philo->last_time_eat = current_time(mem);
	printf("%lums %d is eating\n", current_time(mem), philo->id);
	usleep(mem->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->eat_counter++;
	printf("%lums %d is sleeping\n", current_time(mem), philo->id);
	usleep(mem->time_to_sleep * 1000);
	printf("%lums %d is thinking\n", current_time(mem), philo->id);
	return (NULL);
}

void init_simulation(t_mem *mem)
{
	int i;

	i = 0;
	pthread_mutex_lock(&(mem->stop));
	get_first_time(mem);

	while (i < mem->philosophers_count)
	{
		if (pthread_create(&mem->philos_threads[i], NULL, &routine, &mem->philo[i]))
			exit(errno);
		if (pthread_detach(mem->philos_threads[i]))
			exit(errno);
		i += 2;
		if (i >= mem->philosophers_count && i % 2 == 0)
		{
			i = 1;
			usleep(200);
		}
	}
	i = 0;
	pthread_mutex_lock(&(mem->stop));
}

int main(int ac, char **av)
{
	pthread_mutex_t lock;
	t_mem mem;

	parse(ac, av, &mem);
	init_locks(&mem);
	init_simulation(&mem);
	clean_simulation(&mem, 0);

	return (0);
}