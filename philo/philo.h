/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:18:06 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/09 13:21:22 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef enum e_print
{
	take_fork,
	eating,
	sleeping,
	thinking,
	death,
	eaten
}	t_print;

typedef struct s_param
{
	unsigned int	nbr_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				loop;
	long			start;
	long			notepme;
	unsigned int	eat_count;
	pthread_mutex_t	stop;
	pthread_mutex_t	eating;
}					t_param;

typedef struct s_philo
{
	unsigned int	id;
	long			has_eaten;
	t_param			*param;
	pthread_t		thr;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	r_fork;
}					t_philo;

int		ft_atoi(const char *str, t_param *param);
void	ft_exit(char *mess, t_philo *phil, t_param *param, long ph_count);
int		handle_edgecases(t_print action, t_philo *phil, int *blean);
long	get_time(void);
void	msleep(long sleep);
void	*routine(void *input);
void	*death_watch(void *input);

#endif
