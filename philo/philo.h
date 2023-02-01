/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:18:06 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/01 18:21:50 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_param
{
	unsigned int	number_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				notepme;
}					t_param;

typedef struct s_philo
{
	int				nbr;
	t_param			*param;
	pthread_t		id;
	pthread_mutex_t	fork;
}					t_philo;

int			ft_atoi(const char *str);
void		*routine(void *param);
void		ft_exit(char *mess, t_philo *phil, t_param *param);

#endif
