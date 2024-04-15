/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:07:12 by bautrodr          #+#    #+#             */
/*   Updated: 2024/04/10 14:47:37 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philo_args(t_philo *philo, t_args *args, int i)
{
	philo->id = i + 1;
	philo->args = args;
	philo->alive = 1;
	philo->eat_times = 0;
	philo->holding_left = 0;
	philo->holding_right = 0;
	philo->last_meal = get_time_value();
}

int	init_philos(t_args *args)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * args->philos_nb);
	if (!philo)
		return (EXIT_FAILURE);
	i = 0;
	while (i < args->philos_nb)
	{
		if (pthread_mutex_init(&(philo[i].right_fork), NULL)
			|| pthread_mutex_init(&philo->m_eat_times, NULL))
		{
			ft_memdel(philo);
			printf(RED "Error: mutex init failed\n" RST);
			return (EXIT_FAILURE);
		}
		init_philo_args(&philo[i], args, i);
		if (i != 0)
			philo[i].left_fork = &philo[i - 1].right_fork;
		i++;
	}
	philo[0].left_fork = &philo[args->philos_nb - 1].right_fork;
	args->philo = philo;
	return (EXIT_SUCCESS);
}
