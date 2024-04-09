/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:49:51 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/21 10:11:12 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(t_args *args, char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (is_digit_str(argv[i]) == -1)
		{
			print_error("Only positive numbers are accepted\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	args->philos_nb = ft_atoi(argv[1]);
	if (args->philos_nb > 200)
	{
		print_error("You shouldn't test with more than 200 philos!!\n");
		usleep(2500000);
	}
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	args->finish_eating = 0;
	args->max_meals = 1;
	args->death_flag = 0;
	return (EXIT_SUCCESS);
}

int init_mutex(t_args *args)
{
    if (pthread_mutex_init(&args->printer, NULL) != 0)
    {
        print_error("Error: mutex init failed\n");
        return (EXIT_FAILURE);
    }
    if (pthread_mutex_init(&args->m_death, NULL) != 0)
    {
        print_error("Error: mutex init failed\n");
        return (EXIT_FAILURE);
    }
    if (pthread_mutex_init(&args->m_eat, NULL) != 0)
    {
        print_error("Error: mutex init failed\n");
        return (EXIT_FAILURE);
    }
    if (pthread_mutex_init(&args->m_stop, NULL) != 0)
    {
        print_error("Error: mutex init failed\n");
        return (EXIT_FAILURE);
    }
    if (pthread_mutex_init(&args->m_done, NULL) != 0)
    {
        print_error("Error: mutex init failed\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int	init_data(t_args *args, char **argv, int argc)
{
	if (check_args(args, argv, argc))
		return (EXIT_FAILURE);
    if (init_mutex(args))
        return (EXIT_FAILURE);
	if (argc == 6)
		args->max_meals = ft_atoi(argv[5]);
	if (args->philos_nb < 1 || args->time_to_die < 0 || args->time_to_eat < 0
		|| args->time_to_sleep < 0)
		return (EXIT_FAILURE);
	if (args->max_meals <= 0)
		return (EXIT_FAILURE);
	if (argc < 6)
		args->max_meals = -1;
    args->initial_time = get_time_value();
	return (EXIT_SUCCESS);
}
