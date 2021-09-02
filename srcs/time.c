/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iseljao <iseljao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 21:04:41 by iseljao           #+#    #+#             */
/*   Updated: 2021/09/02 21:05:43 by iseljao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	// return (t1.tv_sec * 1000 + t1.tv_usec / 1000 - mem->big_bang);
	return ((t1.tv_sec - mem->t0.tv_sec) * 1000.0f + (t1.tv_usec - mem->t0.tv_usec) / 1000.0f);
}