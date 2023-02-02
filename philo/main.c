/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:21:56 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/02 18:52:06 by oheinzel         ###   ########.fr       */
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

	new = malloc(sizeof(t_param *));
	if (new == NULL)
		ft_exit("philo: failed to initialize param struct", NULL, NULL);
	new->number_of_philos = ft_atoi(argv[0]);
	new->time_to_die = ft_atoi(argv[1]);
	new->time_to_eat = ft_atoi(argv[2]);
	new->time_to_sleep = ft_atoi(argv[3]);
	new->notepme = -1;
	if (argc == 6)
		new->notepme = ft_atoi(argv[4]);
	return (new);
}

static t_philo	*create_philos(t_param *param)
{
	unsigned int	i;
	t_philo			*new;

	i = 0;
	new = malloc(sizeof(t_philo) * (param->number_of_philos));
	if (new == NULL)
		ft_exit("philo: failed to initialize phil array", NULL, param);
	while (i < param->number_of_philos)
	{
		new[i].id = i + 1;
		new[i].thr = NULL;
		new[i].param = param;
		if (i != 0)
			new[i].l_fork = &new[i - 1].r_fork;
		pthread_mutex_init(&(new[i++].r_fork), NULL);
	}
	new[0].l_fork = &new[i - 1].r_fork;
	return (new);
}

int	main(int argc, char *argv[])
{
	t_param			*param;
	t_philo			*phils;
	unsigned int	i;

	i = 0;
	if (check_input(argc, ++argv))
		ft_exit("philo: wrong input", NULL, NULL);
	param = init_param(argc, argv);
	phils = create_philos(param);
	while (i++ < param->number_of_philos)
		if (pthread_create(&(phils[i - 1].thr), NULL, &routine, &phils[i - 1]))
			ft_exit("philo: not able to initialize thread", phils, param);
	while (i && pthread_join(phils[i - 1].thr, NULL))
		i--;
	free(phils);
	free(param);
	return (0);
}
