/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    #:+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iseljao <iseljao@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:59:26 by iseljao           #+#    #+#             */
/*   Updated: 2021/09/02 20:59:27 by iseljao          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void parse(int ac, char **av, t_mem *mem)
{
	ft_memset(mem, 0, sizeof(t_mem));
	if (ac != 5 && ac != 6)
		ft_exit(*mem, "wrong number of arguments\n");
	mem->philosophers_count = ft_atoi(av[1]);
	mem->time_to_die = ft_atoi(av[2]);
	mem->time_to_eat = ft_atoi(av[3]);
	mem->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		mem->eating_count = ft_atoi(av[5]);
}