/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:50:36 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/07 16:52:54 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ************** philosopher routine ************** */

static void	print_action(t_print action, t_philo *phil)
{
	char			*s;
	pthread_mutex_t	test;

	if (action != death && action != eaten)
		test = phil->param->stop;
	if (action == take_fork)
		s = "\033[0;34mpicked up fork\033[0;97m";
	if (action == eating)
		s = "\033[0;36mis eating\033[0;97m";
	if (action == sleeping)
		s = "\033[0;32mis sleeping\033[0;97m";
	if (action == thinking)
		s = "\033[0;35mis thinking\033[0;97m";
	if (action == death)
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
		write(1, "\033[0;97m", 7);
		print_action(thinking, phil);
		usleep(30);
	}
	while (1)
		eat_sleep_think(phil);
	return (NULL);
}

/* ************** death_watch routine ************** */

static int	check_death(t_philo *phils, t_param *param, unsigned int i)
{
	return (get_time() - phils[i].has_eaten < param->time_to_die
		&& ((param->notepme >= 0 && param->eat_count < param->notepme)
			|| param->notepme < 0));
}

void	*death_watch(void *input)
{
	unsigned int	i;
	t_philo			*phils;
	t_param			*param;

	i = 0;
	phils = input;
	param = phils->param;
	while (check_death(phils, param, i))
		if (++i == param->nbr_philos)
			i = 0;
	pthread_mutex_lock(&param->stop);
	ft_usleep(5);
	if (param->eat_count == param->notepme)
		print_action(eaten, &phils[i]);
	else
		print_action(death, &phils[i]);
	i = param->nbr_philos;
	while (i--)
		pthread_detach(phils[i].thr);
	while (i < param->nbr_philos)
		pthread_mutex_destroy(&phils[i++].r_fork);
	pthread_mutex_destroy(&param->eating);
	return (pthread_mutex_destroy(&param->stop), NULL);
}
