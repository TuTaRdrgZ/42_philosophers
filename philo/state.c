/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:48:27 by bautrodr          #+#    #+#             */
/*   Updated: 2024/04/10 14:48:29 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	many_philos(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork);
	philo->holding_right = 1;
	print_state(W "has taken RIGHT fork" RST, philo);
	print_state(B "is eating" RST, philo);
	pthread_mutex_lock(&philo->args->m_eat);
	philo->eat_times++;
	philo->last_meal = get_timestamp();
	pthread_mutex_unlock(&philo->args->m_eat);
	ft_usleep(philo->args->time_to_eat);
	pthread_mutex_unlock(&philo->right_fork);
	philo->holding_right = 0;
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo->holding_left = 1;
	print_state(W "has taken LEFT fork" RST, philo);
	pthread_mutex_lock(&philo->args->m_death);
	if (philo->args->death_flag)
	{
		pthread_mutex_unlock(&philo->args->m_death);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->m_death);
	if (philo->args->philos_nb != 1)
	{
		many_philos(philo);
	}
	pthread_mutex_unlock(philo->left_fork);
	philo->holding_left = 0;
	if (philo->eat_times == philo->args->max_meals)
	{
		pthread_mutex_lock(&philo->args->m_done);
		philo->args->finish_eating++;
		pthread_mutex_unlock(&philo->args->m_done);
		return (1);
	}
	return (0);
}

int	philo_sleep_or_think(t_philo *philo, int flag)
{
	if (flag == 1) // sleep
	{
		pthread_mutex_lock(&philo->args->m_death);
		if (philo->args->death_flag)
		{
			pthread_mutex_unlock(&philo->args->m_death);
			return (1);
		}
		pthread_mutex_unlock(&philo->args->m_death);
		print_state(G "is sleeping" RST, philo);
		ft_usleep(philo->args->time_to_sleep);
		return (0);
	}
	else // think
	{
		pthread_mutex_lock(&philo->args->m_death);
		if (philo->args->death_flag)
		{
			pthread_mutex_unlock(&philo->args->m_death);
			return (1);
		}
		pthread_mutex_unlock(&philo->args->m_death);
		print_state(C "is thinking" RST, philo);
		return (0);
	}
}

void	handle_one_philo(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
	print_state(W "has taken a fork" RST, philo);
	ft_usleep(philo->args->time_to_die);
	pthread_mutex_lock(&philo->args->printer);
	printf(RED "%ld %d died\n" RST, get_timestamp(), philo->id);
	pthread_mutex_unlock(&philo->args->printer);
	pthread_mutex_lock(&philo->args->m_stop);
	philo->args->death_flag = 1;
	pthread_mutex_unlock(&philo->args->m_stop);
    pthread_mutex_unlock(philo->left_fork);
}

void	*routine(void *p_data)
{
	t_philo	*philo;

	philo = (t_philo *)p_data;
	if (philo->args->philos_nb == 1)
		return (handle_one_philo(philo), NULL);
	if (philo->id % 2 == 0)
        usleep(500);
    else
        usleep(1000);
	while (!pthread_mutex_lock(&philo->args->m_death) && philo->args->death_flag == 0)
	{
		pthread_mutex_unlock(&philo->args->m_death);
		if (eat(philo))
			break ;
		if (philo_sleep_or_think(philo, 1))
			break ;
		if (philo_sleep_or_think(philo, 2))
			break ;
	}
	pthread_mutex_unlock(&philo->args->m_death);
	if (philo->holding_left)
		pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
