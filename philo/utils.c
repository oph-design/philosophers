/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:14:38 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/10 14:28:20 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while ((47 < str[i]) && (str[i] < 58))
		r = r * 10 + (str[i++] - 48);
	return (r);
}

int	handle_edgecases(t_print action, t_philo *phil, int *running)
{
	if (action != death && action != eaten)
		pthread_mutex_lock(&phil->param->stop);
	if (action != death && action != eaten
		&& !phil->param->kill_threads && running)
		return (*running = 0, pthread_mutex_unlock(&phil->param->stop), 1);
	if (action != death && action != eaten)
		pthread_mutex_unlock(&phil->param->stop);
	if (action == death && phil->param->nbr_philos == 1)
		pthread_mutex_unlock(&phil->r_fork);
	return (0);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	msleep(long sleep)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < sleep)
		usleep(100);
}
