/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:14:38 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/01 11:23:04 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	f;
	int	r;

	i = 0;
	f = 1;
	r = 0;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			f = -1;
	}
	while ((47 < str[i]) && (str[i] < 58))
		r = r * 10 + (str[i++] - 48);
	return (f * r);
}

void	*routine(void *param)
{
	t_param		*phil;
	static int	i = 0;

	phil = param;
	pthread_mutex_lock(&phil->test);
	printf("phil %d: unehre\n", phil->philos[i++].nbr);
	pthread_mutex_unlock(&phil->test);
	return (NULL);
}
