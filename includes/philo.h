/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iseljao <iseljao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 22:15:23 by iseljao           #+#    #+#             */
/*   Updated: 2021/09/02 17:27:52 by iseljao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <math.h>

#define SUCCESS 0
#define ERROR 1

#define FALSE 0
#define TRUE 1

typedef struct s_philo
{
	int id;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	int eat_counter;
	long unsigned last_time_eat;
	void *mem;
} t_philo;

typedef struct s_mem
{
	pthread_t philos_threads[200];
	pthread_mutex_t forks[200];
	t_philo philo[200];
	long unsigned int big_bang;
	int philosophers_count;
	pthread_mutex_t write;
	pthread_mutex_t stop;
	struct timeval t0;
	int time_to_sleep;
	int eating_count;
	int time_to_die;
	int time_to_eat;
} t_mem;

#endif