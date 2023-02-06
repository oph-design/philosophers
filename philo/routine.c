/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:50:36 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/06 20:33:58 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_action(t_print action, t_philo *phil)
{
	pthread_mutex_t	test;

	test = phil->param->pdead;
	if (action == take_fork)
		printf("\033[0;36m%ld philo %u: picked up fork\n",
			get_time() - phil->param->time, phil->id);
	if (action == eating)
		printf("\033[0;34m%ld philo %u: is eating\n",
			get_time() - phil->param->time, phil->id);
	if (action == sleeping)
		printf("\033[0;32m%ld philo %u: is sleeping\n",
			get_time() - phil->param->time, phil->id);
	if (action == thinking)
		printf("\033[0;33m%ld philo %u: is thinking\n",
			get_time() - phil->param->time, phil->id);
}

static void	eat_sleep_think(t_philo *phil)
{
	pthread_mutex_lock(&phil->r_fork);
	print_action(take_fork, phil);
	pthread_mutex_lock(phil->l_fork);
	print_action(take_fork, phil);
	print_action(eating, phil);
	phil->has_eaten = get_time();
	ft_usleep(phil->param->time_to_eat);
	pthread_mutex_unlock(&phil->r_fork);
	pthread_mutex_unlock(phil->l_fork);
	print_action(sleeping, phil);
	ft_usleep(phil->param->time_to_sleep);
	print_action(thinking, phil);
}

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
		eat_sleep_think(phil);
	return (NULL);
}

void	*death(void *param)
{
	unsigned int	i;
	t_philo			*phils;

	i = 0;
	phils = param;
	while (get_time() - phils[i].has_eaten < phils->param->time_to_die)
		if (++i == phils->param->number_of_philos)
			i = 0;
	pthread_mutex_lock(&phils->param->pdead);
	printf("\033[0;31m%ld philo %u: died\n",
		get_time() - phils->param->time, phils[i].id);
	i = 0;
	while (i < phils->param->number_of_philos)
		pthread_detach(phils[i++].thr);
	return (NULL);
}
