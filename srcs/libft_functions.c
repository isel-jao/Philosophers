/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yqodsi <yqodsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 21:12:52 by iseljao           #+#    #+#             */
/*   Updated: 2021/09/05 17:03:19 by yqodsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*p;

	p = s;
	while ((int)--len >= 0)
		*p++ = (unsigned char)c;
	return (s);
}

long int	ft_atoi(const char *str)
{
	long int	res;
	int			signe;

	signe = 1;
	res = 0;
	if (*str == '-')
		return (-1);
	if (*str == '+')
		++str;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str++ - 48);
		if (res > 2147483648 || (res > 2147483647 && signe == 1) || \
			res > 4294967295)
			return (-1);
	}
	if (*str)
		return (-1);
	return ((int)(res * signe));
}
