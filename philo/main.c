/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:09:25 by bautrodr          #+#    #+#             */
/*   Updated: 2024/04/10 14:47:49 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_routine(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->philos_nb)
	{
		if (pthread_create(&(args->philo[i].philo_pid), NULL, &routine,
				&(args->philo[i])) != 0)
		{
			print_error("Error: thread creation failed\n");
			return (1);
		}
		// pthread_detach(args->philo[i].philo_pid);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc == 5 || argc == 6)
	{
		if (!init_data(&args, argv, argc))
		{
			init_philos(&args);
			if (!init_routine(&args))
			{
				supervisor(&args);
			}
			return (EXIT_SUCCESS);
		}
		return (EXIT_FAILURE);
	}
	else
	{
		print_error("Wrong input:\n" G "Correct input: ./philo <N-philos> <die-time>\
 <eat-time> <think-time> [<max-eat-count>]\n" RST);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
