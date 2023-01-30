/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oheinzel <oheinzel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:21:56 by oheinzel          #+#    #+#             */
/*   Updated: 2023/01/30 13:19:57 by oheinzel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// notepme = number_of_times_each_philosopher_must_eat

int	main(int argc, char *argv[])
{
	t_param	*param;

	if (check_input(argc, argv))
		return (printf("ERROR: wrong input\n"), 1);
	param = init_param(argv, argc);
	return (0);
}
