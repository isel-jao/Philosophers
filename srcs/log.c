/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 21:06:18 by iseljao           #+#    #+#             */
/*   Updated: 2021/09/05 17:03:40 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, int status)
{
	t_mem	*mem;

	mem = philo->mem;
	pthread_mutex_lock(&mem->write);
	printf("%10lums", current_time(mem));
	if (status == RFORK)
		printf(" %d %-25s \n", philo->id, "has taken his right fork");
	else if (status == LFORK)
		printf(" %d %-25s \n", philo->id, "has taken his left fork");
	else if (status == EATING)
		printf(" %d %-25s \n", philo->id, "is eating");
	else if (status == THINKINK)
		printf(" %d %-25s \n", philo->id, "is thinking");
	else if (status == SLEEPING)
		printf(" %d %-25s \n", philo->id, "is sleeping");
	pthread_mutex_unlock(&mem->write);
}
