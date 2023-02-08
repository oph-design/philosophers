/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:50:36 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/08 18:53:57 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_action(t_print action, t_philo *phil, int *crusty)
{
	char	*s;

	s = NULL;
	if (handle_edgecases(action, phil, crusty))
		return ;
	if (action == take_fork)
		s = "\033[0;34mhas taken a fork\033[0;97m";
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

/* ************** philosopher routine ************** */

static void	eat_sleep_think(t_philo *phil, int *crusty)
{
	pthread_mutex_lock(&phil->r_fork);
	print_action(take_fork, phil, crusty);
	pthread_mutex_lock(phil->l_fork);
	print_action(take_fork, phil, crusty);
	pthread_mutex_lock(&phil->param->eating);
	if (phil->param->notepme)
		phil->param->eat_count += 1;
	if (phil->param->notepme)
		print_action(eating, phil, crusty);
	phil->has_eaten = get_time();
	pthread_mutex_unlock(&phil->param->eating);
	ft_usleep(phil->param->time_to_eat);
	pthread_mutex_unlock(&phil->r_fork);
	pthread_mutex_unlock(phil->l_fork);
	print_action(sleeping, phil, crusty);
	ft_usleep(phil->param->time_to_sleep);
	print_action(thinking, phil, crusty);
}

void	*routine(void *input)
{
	t_philo	*phil;
	int		crusty;

	phil = input;
	crusty = 1;
	if ((phil->id) % 2 == 0)
	{
		write(1, "\033[0;97m", 7);
		print_action(thinking, phil, &crusty);
		usleep(30);
	}
	while (crusty)
		eat_sleep_think(phil, &crusty);
	return (NULL);
}

/* ************** death_watch routine ************** */

static int	check_death(t_philo *phils, t_param *param, unsigned int i)
{
	int	death_time;
	int	max_eat;
	int	notepme_init;

	pthread_mutex_lock(&param->eating);
	death_time = get_time() - phils[i].has_eaten < param->time_to_die;
	max_eat = param->eat_count < param->notepme;
	notepme_init = param->notepme < 0;
	if (max_eat || death_time)
		pthread_mutex_unlock(&param->eating);
	return (death_time && ((max_eat && !notepme_init) || notepme_init));
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
	param->loop = 0;
	ft_usleep(1);
	if (param->eat_count == param->notepme)
		print_action(eaten, &phils[i], NULL);
	else
		print_action(death, &phils[i], NULL);
	i = param->nbr_philos;
	pthread_mutex_unlock(&param->stop);
	pthread_mutex_unlock(&param->eating);
	while (i--)
		pthread_join(phils[i].thr, NULL);
	while (i < param->nbr_philos)
		pthread_mutex_destroy(&phils[i++].r_fork);
	pthread_mutex_destroy(&param->eating);
	return (pthread_mutex_destroy(&param->stop), NULL);
}
