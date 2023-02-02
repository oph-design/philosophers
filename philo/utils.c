/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:14:38 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/02 18:54:08 by oheinzel         ###   ########.fr       */
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

void	ft_exit(char *mess, t_philo *phil, t_param *param)
{
	int	i;

	i = 0;
	while (mess[i])
		i++;
	write(2, mess, i);
	write(2, "\n", 1);
	free(phil);
	free(param);
	exit(1);
}

void	*routine(void *param)
{
	t_philo	*phil;

	phil = param;
	while (1)
	{
		printf("phil %u: unehre\n", phil->id);
		usleep(100000);
	}
	return (NULL);
}
