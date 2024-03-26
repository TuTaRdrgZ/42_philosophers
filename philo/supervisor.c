/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:01:09 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/21 10:11:55 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void finish(t_args *args)
{
	int	i;

	i = -1;
	pthread_mutex_unlock(&args->printer);
	pthread_mutex_unlock(&args->m_stop);
	pthread_mutex_unlock(&args->m_death);
	pthread_mutex_unlock(&args->m_time);
    pthread_mutex_unlock(&args->m_eat);
	if (args->philos_nb == 1)
		pthread_mutex_unlock((&args->philo[0])->left_fork);
	while (++i < args->philos_nb)
		pthread_join(args->philo[i].philo_pid, NULL);
	i = -1;
	while (++i < args->philos_nb)
	{
		pthread_mutex_unlock((&args->philo[i])->left_fork);
		pthread_mutex_destroy((&args->philo[i])->left_fork);
	}
	pthread_mutex_destroy(&args->printer);
	pthread_mutex_destroy(&args->m_stop);
	pthread_mutex_destroy(&args->m_death);
	pthread_mutex_destroy(&args->m_time);
    pthread_mutex_destroy(&args->m_eat);
}

void    finish_eating(t_args *args)
{
	pthread_mutex_lock(&args->m_stop);
	args->death_flag = 1;
	pthread_mutex_unlock(&args->m_stop);
    printf("All philos have eaten %d times\n", args->max_meals);
	finish(args);
}


void	supervisor(void *p_args)
{
	int	    i;
    t_args  *args;

    args = (t_args *)p_args;
	i = 0;
	while (args->death_flag == 0)
	{
		pthread_mutex_lock(&args->m_eat);
		if (args->finish_eating == args->philos_nb \
			&& args->max_meals)
			finish_eating(args);
		pthread_mutex_unlock(&args->m_eat);
		pthread_mutex_lock(&args->m_time);
		if (args->philo[i].last_meal + args->time_to_die < get_timestamp())
		{
			pthread_mutex_lock(&args->m_death);
			args->death_flag = 1;
			pthread_mutex_unlock(&args->m_death);
			printf("%ld %d %s\n", get_timestamp(), args->philo[i].id, "died");
			finish(args);
		}
		pthread_mutex_unlock(&args->m_time);
		if (++i == args->philos_nb)
			i = 0;
	}
	finish(args);
}
