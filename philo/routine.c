/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:50:36 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/06 17:11:53 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *param)
{
	t_philo	*phil;

	phil = param;
	if ((phil->id) % 2 == 0)
	{
		printf("\033[0;33m%ld phil %u: is thinking\n",
			get_time() - phil->param->time, phil->id);
		usleep(30);
	}
	while (1)
	{
		pthread_mutex_lock(&phil->r_fork);
		printf("\033[0;36m%ld phil %u: picked up fork\n",
			get_time() - phil->param->time, phil->id);
		pthread_mutex_lock(phil->l_fork);
		printf("\033[0;36m%ld phil %u: picked up fork\n",
			get_time() - phil->param->time, phil->id);
		printf("\033[0;34m%ld phil %u: is eating\n",
			get_time() - phil->param->time, phil->id);
		ft_usleep(phil->param->time_to_eat);
		pthread_mutex_unlock(&phil->r_fork);
		pthread_mutex_unlock(phil->l_fork);
		printf("\033[0;32m%ld phil %u: is sleeping\n",
			get_time() - phil->param->time, phil->id);
		ft_usleep(phil->param->time_to_sleep);
		printf("\033[0;33m%ld phil %u: is thinking\n",
			get_time() - phil->param->time, phil->id);
	}
	return (NULL);
}

void	*death(void *param)
{
	unsigned int	i;
	t_philo			*phils;

	i = 0;
	phils = param;
	while (!phils[i].is_dead)
		if (++i == phils->param->number_of_philos)
			i = 0;
	printf("\033[0;31mphil %d: died\n", phils[i].id);
	i = 0;
	while (i < phils->param->number_of_philos)
		pthread_detach(phils[i++].thr);
	return (NULL);
}
