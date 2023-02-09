/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:50:36 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/09 13:22:03 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_action(t_print action, t_philo *phil, int *blean)
{
	char	*s;

	s = NULL;
	if (handle_edgecases(action, phil, blean))
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

static void	eat_sleep_think(t_philo *phil, int *blean)
{
	pthread_mutex_lock(&phil->r_fork);
	print_action(take_fork, phil, blean);
	pthread_mutex_lock(phil->l_fork);
	print_action(take_fork, phil, blean);
	pthread_mutex_lock(&phil->param->eating);
	if (phil->param->notepme)
		phil->param->eat_count += 1;
	if (phil->param->notepme)
		print_action(eating, phil, blean);
	pthread_mutex_unlock(&phil->param->eating);
	phil->has_eaten = get_time();
	msleep(phil->param->time_to_eat);
	pthread_mutex_unlock(&phil->r_fork);
	pthread_mutex_unlock(phil->l_fork);
	print_action(sleeping, phil, blean);
	msleep(phil->param->time_to_sleep);
	print_action(thinking, phil, blean);
}

void	*routine(void *input)
{
	t_philo	*phil;
	int		blean;

	phil = input;
	blean = 1;
	if ((phil->id) % 2 == 0)
	{
		write(1, "\033[0;97m", 7);
		print_action(thinking, phil, &blean);
		msleep(3);
	}
	while (blean)
		eat_sleep_think(phil, &blean);
	return (NULL);
}

/* ************** death_watch routine ************** */

static int	check_death(t_philo *phils, t_param *param, unsigned int i)
{
	int	death_time;
	int	max_eat;
	int	notepme_init;

	if (i == 0)
		msleep(param->time_to_die);
	pthread_mutex_lock(&param->eating);
	death_time = get_time() - phils[i].has_eaten < param->time_to_die;
	max_eat = param->eat_count < param->notepme;
	notepme_init = param->notepme < 0;
	if (death_time && ((max_eat && !notepme_init) || notepme_init))
		pthread_mutex_unlock(&param->eating);
	return (death_time && ((max_eat && !notepme_init) || notepme_init));
}

void	*death_watch(void *input)
{
	unsigned int	i;
	t_philo			*phils;

	i = 0;
	phils = input;
	while (check_death(phils, phils->param, i))
		if (++i == phils->param->nbr_philos)
			i = 0;
	pthread_mutex_lock(&phils->param->stop);
	phils->param->loop = 0;
	msleep(1);
	if (phils->param->eat_count >= phils->param->notepme
		&& phils->param->notepme > 0)
		print_action(eaten, &phils[i], NULL);
	else
		print_action(death, &phils[i], NULL);
	i = phils->param->nbr_philos;
	pthread_mutex_unlock(&phils->param->stop);
	pthread_mutex_unlock(&phils->param->eating);
	while (i--)
		pthread_join(phils[i].thr, NULL);
	while (i < phils->param->nbr_philos)
		pthread_mutex_destroy(&phils[i++].r_fork);
	pthread_mutex_destroy(&phils->param->eating);
	return (pthread_mutex_destroy(&phils->param->stop), NULL);
}
