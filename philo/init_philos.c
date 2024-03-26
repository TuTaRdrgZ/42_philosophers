/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:07:12 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/25 09:55:12 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philos(t_args args)
{
	int		i;
	t_philo	*tmp;

	i = 1;
	while (i < args.philos_nb)
	{
        printf("free philo %d\n", tmp->id);
        pthread_mutex_destroy(&tmp->right_fork);
		pthread_mutex_destroy(tmp->left_fork);
		ft_memdel(tmp);
		i++;
	}
	//pthread_mutex_destroy(args.printer);
	//ft_memdel(args.printer);
}

int init_philos(t_args *args)
{
	t_philo	*philo;
    int     i;

	philo = malloc(sizeof(t_philo) * args->philos_nb);
	if (!philo)
		return (EXIT_FAILURE);
    i = 0;
    while (i < args->philos_nb)
    {
        if (pthread_mutex_init(&philo->right_fork, NULL)
            || pthread_mutex_init(&philo->m_last_meal, NULL)
            || pthread_mutex_init(&philo->m_eat_times, NULL))
        {
            ft_memdel(philo);
            print_error("Error: mutex init failed\n");
            return (EXIT_FAILURE);
        }
        philo[i].id = i + 1;
        philo[i].state = THINKING;
        philo[i].args = args;
        philo[i].first_meal = 0;
        philo[i].eat_times = 0;
        philo[i].last_meal = get_time_value();
        if (i > 0)
            philo[i].left_fork = &philo[i - 1].right_fork;
        i++;
    }
    philo[0].left_fork = &philo[args->philos_nb - 1].right_fork;
    args->philo = philo;
    return (EXIT_SUCCESS);
}
