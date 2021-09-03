/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 21:06:18 by iseljao           #+#    #+#             */
/*   Updated: 2021/09/03 16:05:40 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_status(t_philo *philo, int status)
{
	t_mem *mem;

	mem = philo->mem;
	pthread_mutex_lock(&mem->write);
	if (status == RFORK)
		printf("%10lums %d %-25s last meal ", current_time(mem), philo->id, "has taken his right fork");
	else if (status == LFORK)
		printf("%10lums %d %-25s last meal ", current_time(mem), philo->id, "has taken his left fork");
	else if (status == EATING)
		printf("%10lums %d %-25s last meal ", current_time(mem), philo->id, "is eating");
	else if (status == THINKINK)
		printf("%10lums %d %-25s last meal ", current_time(mem), philo->id, "is thinking");
	else if (status == SLEEPING)
		printf("%10lums %d %-25s last meal ", current_time(mem), philo->id, "is sleeping");
	printf("\t%10lu", philo->last_time_eat);
	printf("\t%10d\n", philo->eat_counter);
	pthread_mutex_unlock(&mem->write);
}