/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:50:36 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/07 11:37:38 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_action(t_print action, t_philo *phil)
{
	char			*s;
	pthread_mutex_t	test;

	s = NULL;
	if (action != die && action != eaten)
		test = phil->param->stop;
	if (action == take_fork)
		s = "\033[0;34mpicked up fork\033[0;97m";
	if (action == eating)
		s = "\033[0;36mis eating\033[0;97m";
	if (action == sleeping)
		s = "\033[0;32mis sleeping\033[0;97m";
	if (action == thinking)
		s = "\033[0;35mis thinking\033[0;97m";
	if (action == die)
		s = "\033[0;31mdied\033[0;97m";
	if (action == eaten)
		s = "\033[0;33mand everyone else have eaten enough\033[0;97m";
	printf("%ld philo %u: %s\n", get_time() - phil->param->start, phil->id, s);
}

static void	eat_sleep_think(t_philo *phil)
{
	pthread_mutex_lock(&phil->r_fork);
	print_action(take_fork, phil);
	pthread_mutex_lock(phil->l_fork);
	print_action(take_fork, phil);
	print_action(eating, phil);
	phil->has_eaten = get_time();
	pthread_mutex_lock(&phil->param->eating);
	phil->param->eat_count += 1;
	pthread_mutex_unlock(&phil->param->eating);
	ft_usleep(phil->param->time_to_eat);
	pthread_mutex_unlock(&phil->r_fork);
	pthread_mutex_unlock(phil->l_fork);
	print_action(sleeping, phil);
	ft_usleep(phil->param->time_to_sleep);
	print_action(thinking, phil);
}

void	*routine(void *input)
{
	t_philo	*phil;

	phil = input;
	if ((phil->id) % 2 == 0)
	{
		print_action(thinking, phil);
		usleep(30);
	}
	while (1)
		eat_sleep_think(phil);
	return (NULL);
}

void	*death(void *input)
{
	unsigned int	i;
	t_philo			*phils;
	t_param			*param;

	i = 0;
	phils = input;
	param = phils->param;
	while (get_time() - phils[i].has_eaten < param->time_to_die
		&& ((param->notepme >= 0 && param->eat_count < param->notepme)
			|| param->notepme < 0))
		if (++i == param->nbr_philos)
			i = 0;
	pthread_mutex_lock(&param->stop);
	if (param->eat_count == param->notepme)
		print_action(eaten, &phils[i]);
	else
		print_action(die, &phils[i]);
	i = 0;
	while (i < param->nbr_philos)
		pthread_detach(phils[i++].thr);
	i = 0;
	while (i < param->nbr_philos)
		pthread_mutex_destroy(&phils[i++].r_fork);
	pthread_mutex_destroy(&param->eating);
	return (pthread_mutex_destroy(&param->stop), NULL);
}
