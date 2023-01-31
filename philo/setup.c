/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:33:47 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/31 10:52:22 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*new_philo(t_param	*param)
{
	t_philo	*new;

	new = malloc(sizeof(t_philo *));
	new->id = NULL;
	new->next = NULL;
	pthread_mutex_init(&new->fork, NULL);
	pthread_create(&(new->id), NULL, &routine, param);
	return (new);
}

void	add_philo(t_param	*param)
{
	while (param->philos->next != NULL)
		param->philos = param->philos->next;
	param->philos->next = new_philo(param);
}

void	init_threads(t_param *param)
{
	size_t	i;

	i = 1;
	if (param->number_of_philos <= 0)
		return ;
	param->philos = new_philo(param);
	while (i++ < param->number_of_philos)
		add_philo(param);
}
