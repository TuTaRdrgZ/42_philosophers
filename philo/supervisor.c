/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:01:09 by bautrodr          #+#    #+#             */
/*   Updated: 2024/04/14 01:15:27 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	finish(t_args *args)
{
	int	i;

	i = -1;
	args->finish = 1;
	while (++i < args->philos_nb)
		pthread_join(args->philo[i].philo_pid, NULL);
	i = -1;
	while (++i < args->philos_nb)
	{
		pthread_mutex_destroy((&args->philo[i])->left_fork);
	}
	pthread_mutex_destroy(&args->printer);
	pthread_mutex_destroy(&args->m_stop);
	pthread_mutex_destroy(&args->m_death);
	pthread_mutex_destroy(&args->m_eat);
	pthread_mutex_destroy(&args->m_done);
	free(args->philo);
}

int	is_dead(t_philo *philo)
{
	long int	time;

	pthread_mutex_lock(&philo->args->m_eat);
		time = get_timestamp(philo->args) - philo->last_meal;
	if (time >= philo->args->time_to_die)
	{
		pthread_mutex_unlock(&philo->args->m_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->m_eat);
	return (0);
}

int	check_if_stop(t_args *args)
{
	pthread_mutex_lock(&args->m_stop);
	if (args->death_flag == 1)
	{
		pthread_mutex_unlock(&args->m_stop);
		return (1);
	}
	pthread_mutex_unlock(&args->m_stop);
	return (0);
}

int	complete_eating(t_args *args)
{
	pthread_mutex_lock(&args->m_done);
	if (args->finish_eating == args->philos_nb)
	{
		pthread_mutex_unlock(&args->m_done);
		return (1);
	}
	pthread_mutex_unlock(&args->m_done);
	return (0);
}

void	supervisor(void *p_data)
{
	int		i;
	t_args	*args;

	args = p_data;
    ft_usleep(100);
	while (check_if_stop(args) == 0)
	{
		i = -1;
		while (++i < args->philos_nb)
		{
			if (complete_eating(args) == 1)
			{
				printf(G "All philosophers have eaten enough\n" RST);
				return (finish(args));
			}
			if (is_dead(&args->philo[i]) == 1 && args->philos_nb != 1)
			{
				pthread_mutex_lock(&args->m_death);
				args->death_flag = 1;
				pthread_mutex_unlock(&args->m_death);
				printf(RED "%ld %d died\n" RST, get_timestamp(args), i + 1);
				return (finish(args));
			}
		}
	}
}
