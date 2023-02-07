/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:14:38 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/07 11:15:39 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str, t_param *param)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while ((47 < str[i]) && (str[i] < 58))
		r = r * 10 + (str[i++] - 48);
	if (r < 0)
		ft_exit("philo: integer overflow", NULL, param, 0);
	return (r);
}

void	ft_exit(char *mess, t_philo *phil, t_param *param, long ph_count)
{
	long	i;

	i = 0;
	while (mess[i])
		i++;
	i = 0;
	while (phil != NULL && i < ph_count)
		pthread_mutex_destroy(&phil[i].r_fork);
	if (param != NULL)
		pthread_mutex_destroy(&param->stop);
	if (param != NULL)
		pthread_mutex_destroy(&param->eating);
	free(phil);
	free(param);
	write(2, mess, i);
	write(2, "\n", 1);
	exit(1);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long sleep)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < sleep)
		usleep(100);
}
