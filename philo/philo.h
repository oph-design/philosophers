/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:18:06 by oheinzel          #+#    #+#             */
/*   Updated: 2023/02/01 11:13:14 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				nbr;
	pthread_t		id;
	pthread_mutex_t	fork;
}					t_philo;

typedef struct s_param
{
	unsigned int	number_of_philos;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				notepme;
	t_philo			*philos;
	pthread_mutex_t	test;
}					t_param;

int			ft_atoi(const char *str);
void		*routine(void *param);

#endif
