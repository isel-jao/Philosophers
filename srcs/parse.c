/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 20:59:26 by iseljao           #+#    #+#             */
/*   Updated: 2021/09/05 17:04:27 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(t_mem mem, char *error_msj)
{
	(void)mem;
	if (error_msj == NULL)
		exit(0);
	printf("%s", error_msj);
	exit(1);
}

void	parse(int ac, char **av, t_mem *mem)
{
	ft_memset(mem, 0, sizeof(t_mem));
	if (ac != 5 && ac != 6)
		ft_exit(*mem, "Error: number of arguments\n");
	mem->philosophers_count = ft_atoi(av[1]);
	if (mem->philosophers_count <= 0)
		ft_exit(*mem, "Error: philosopher count!\n");
	mem->time_to_die = ft_atoi(av[2]);
	if (mem->time_to_die <= 0)
		ft_exit(*mem, "Error: time to die\n");
	mem->time_to_eat = ft_atoi(av[3]);
	if (mem->time_to_eat <= 0)
		ft_exit(*mem, "Error: time to eat\n");
	mem->time_to_sleep = ft_atoi(av[4]);
	if (mem->time_to_sleep <= 0)
		ft_exit(*mem, "Error: time to sleep\n");
	if (ac == 6)
	{
		mem->option_specified = 1;
		mem->eating_count = ft_atoi(av[5]);
		if (mem->eating_count <= 0)
			ft_exit(*mem, "Error: eating count\n");
	}
}
