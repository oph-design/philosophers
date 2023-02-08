/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:21:56 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/08 18:22:18 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_num(char *str)
{
	while (*str)
	{
		if (*str < 48 || *str > 57)
			return (1);
		str++;
	}
	return (0);
}

static int	check_input(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (1);
	while (*argv != NULL)
	{
		if (check_num(*argv) || **argv == 0)
			return (1);
		argv++;
	}
	return (0);
}

static t_param	*init_param(int argc, char *argv[])
{
	t_param	*new;

	new = malloc(sizeof(t_param));
	if (new == NULL)
		ft_exit("error: struct init fail", NULL, NULL, 0);
	if (pthread_mutex_init(&new->stop, NULL))
		ft_exit("error: mutex init fail", NULL, new, 0);
	if (pthread_mutex_init(&new->eating, NULL))
		ft_exit("error: mutex init fail", NULL, new, 0);
	new->nbr_philos = ft_atoi(argv[0], new);
	if (new->nbr_philos == 0)
		ft_exit("error: not enough philos", NULL, new, 0);
	new->time_to_die = ft_atoi(argv[1], new);
	new->time_to_eat = ft_atoi(argv[2], new);
	new->time_to_sleep = ft_atoi(argv[3], new);
	new->start = get_time();
	new->loop = 1;
	new->eat_count = 0;
	new->notepme = -1;
	if (argc == 6)
		new->notepme = ft_atoi(argv[4], new) * new->nbr_philos;
	return (new);
}

static t_philo	*create_philos(t_param *param)
{
	unsigned int	i;
	t_philo			*new;

	i = 0;
	new = malloc(sizeof(t_philo) * (param->nbr_philos));
	if (new == NULL)
		ft_exit("error: struct init fail", NULL, param, 0);
	while (i < param->nbr_philos)
	{
		new[i].id = i + 1;
		new[i].has_eaten = get_time();
		new[i].thr = 0;
		new[i].param = param;
		if (i != 0)
			new[i].l_fork = &new[i - 1].r_fork;
		if (pthread_mutex_init(&(new[i++].r_fork), NULL))
			ft_exit("error: mutex init fail", new, param, i);
	}
	new[0].l_fork = &new[i - 1].r_fork;
	return (new);
}

int	main(int argc, char *argv[])
{
	t_param			*param;
	t_philo			*phils;
	pthread_t		thr;
	unsigned int	i;

	i = 0;
	thr = 0;
	if (check_input(argc, ++argv))
		ft_exit("error: wrong input", NULL, NULL, 0);
	param = init_param(argc, argv);
	phils = create_philos(param);
	while (i++ < param->nbr_philos)
		if (pthread_create(&(phils[i - 1].thr), NULL, &routine, &phils[i - 1]))
			ft_exit("error: thread init fail", phils, param, param->nbr_philos);
	pthread_create(&thr, NULL, &death_watch, phils);
	pthread_join(thr, NULL);
	free(phils);
	free(param);
	return (0);
}
