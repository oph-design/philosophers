/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 10:14:38 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/08 18:52:48 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str, t_param *param)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while ((47 < str[i]) && (str[i] < 58))
		r = r * 10 + (str[i++] - 48);
	if (r < 0)
		ft_exit("error: integer overflow", NULL, param, 0);
	return (r);
}

void	ft_exit(char *mess, t_philo *phils, t_param *param, long ph_count)
{
	long	len;

	len = 0;
	while (mess[len])
		len++;
	while (phils != NULL && ph_count--)
		pthread_mutex_destroy(&phils[ph_count].r_fork);
	if (param != NULL)
		pthread_mutex_destroy(&param->stop);
	if (param != NULL)
		pthread_mutex_destroy(&param->eating);
	free(phils);
	free(param);
	write(2, "\033[0;31m", 7);
	write(2, mess, len);
	write(2, "\n", 1);
	exit(1);
}

int	handle_edgecases(t_print action, t_philo *phil, int *crusty)
{
	if (action != death && action != eaten)
		pthread_mutex_lock(&phil->param->stop);
	if (action != death && action != eaten && !phil->param->loop && crusty)
		return (*crusty = 0, pthread_mutex_unlock(&phil->param->stop), 1);
	if (action != death && action != eaten)
		pthread_mutex_unlock(&phil->param->stop);
	if (action == death && phil->param->nbr_philos == 1)
		pthread_mutex_unlock(&phil->r_fork);
	return (0);
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long sleep)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < sleep)
		usleep(100);
}
