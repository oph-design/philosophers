/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:50:36 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/06 14:44:04 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *param)
{
	t_philo	*phil;

	phil = param;
	pthread_mutex_lock(&phil->param->pdead);
	ft_usleep(phil->param->time_to_eat);
	printf("\033[0;97mphil %u: %ld unehre\n", phil->id, get_time() - phil->param->time);
	pthread_mutex_unlock(&phil->param->pdead);
	//phil->is_dead = 1;
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
