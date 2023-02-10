/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:26:08 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/10 15:19:12 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	aboard_threads(t_philo *phils, t_param *param)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&param->stop);
	param->kill_threads = 0;
	pthread_mutex_unlock(&param->stop);
	while (i < param->nbr_philos)
	{
		if (phils[i].thr != 0)
			pthread_join(phils[i].thr, NULL);
		i++;
	}
}

void	ft_exit(char *mess, t_philo *phils, t_param *param, long ph_count)
{
	long	len;

	len = 0;
	while (mess[len])
		len++;
	if (len == 11)
		aboard_threads(phils, param);
	while (phils != NULL && ph_count--)
		pthread_mutex_destroy(&phils[ph_count].r_fork);
	if (param != NULL)
		pthread_mutex_destroy(&param->stop);
	if (param != NULL)
		pthread_mutex_destroy(&param->eating);
	free(phils);
	free(param);
	write(2, "\033[0;31m", 7);
	write(2, "error: ", 7);
	write(2, mess, len);
	write(2, "\n\033[0;97m", 8);
}
