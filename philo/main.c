/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:21:56 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/01 11:21:24 by oheinzel         ###   ########.fr       */
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
	new->number_of_philos = ft_atoi(argv[0]);
	new->time_to_die = ft_atoi(argv[1]);
	new->time_to_eat = ft_atoi(argv[2]);
	new->time_to_sleep = ft_atoi(argv[3]);
	new->notepme = -1;
	new->philos = NULL;
	pthread_mutex_init(&new->test, NULL);
	if (argc == 6)
		new->notepme = ft_atoi(argv[4]);
	return (new);
}

static t_philo	*init_threads(t_param *param)
{
	unsigned int	i;
	t_philo			*new;

	i = 0;
	new = malloc(sizeof(t_philo) * (param->number_of_philos));
	while (i < param->number_of_philos)
	{
		new[i].nbr = i + 1;
		new[i].id = NULL;
		printf("%d\n", new[i].nbr);
		pthread_mutex_init(&(new[i++].fork), NULL);
		//pthread_create(&(new[i++].id), NULL, &routine, param);
	}
	return (new);
}

int	main(int argc, char *argv[])
{
	t_param			*param;
	unsigned int	i;

	i = 0;
	if (check_input(argc, ++argv))
		return (printf("ERROR: wrong input\n"), 1);
	param = init_param(argc, argv);
	param->philos = init_threads(param);
	while (i < param->number_of_philos)
	{
		pthread_create(&(param->philos[i].id), NULL, &routine, param);
		i++;
		usleep(30);
	}
	return (0);
}
