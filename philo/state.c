/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:51:44 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/21 10:11:49 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(char *action, useconds_t delay, t_philo *philo)
{
	long	timestamp;

	pthread_mutex_lock(&philo->args->printer);
    pthread_mutex_lock(&philo->args->m_death);
    pthread_mutex_lock(&philo->args->m_time);
	if (!philo->args->death_flag && philo->args->philos_nb > 0)
		printf("%ld %d %s\n", get_timestamp(), philo->id, action);
	if (delay > 0)
		ft_msleep(delay);
	pthread_mutex_unlock(&philo->args->printer);
    pthread_mutex_unlock(&philo->args->m_death);
    pthread_mutex_unlock(&philo->args->m_time);
}

int	eat(t_philo *philo)
{
    pthread_mutex_lock(&philo->right_fork);
    print_state("has taken a fork", 0, philo);
    pthread_mutex_lock(philo->left_fork);
    print_state("has taken a fork", 0, philo);
    print_state("is eating", philo->args->time_to_eat, philo);
    pthread_mutex_lock(&philo->m_last_meal);
    philo->last_meal = get_timestamp();
    pthread_mutex_unlock(&philo->m_last_meal);
    ft_msleep(philo->args->time_to_eat);
    pthread_mutex_unlock(&philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_lock(&philo->m_eat_times);
    philo->eat_times++;
    pthread_mutex_unlock(&philo->m_eat_times);
    if (philo->eat_times == philo->args->max_meals)
    {
        pthread_mutex_lock(&philo->args->m_stop);
        philo->args->finish_eating++;
        pthread_mutex_unlock(&philo->args->m_stop);
        return (1);
    }
    return (0);
}

void	*routine(void *p_data)
{
    t_philo	*philo;

    philo = (t_philo *)p_data;
    if (philo->id % 2 == 0)
        ft_msleep(philo->args->time_to_eat / 2);
    while (philo->args->death_flag == 0)
    {
        pthread_mutex_lock(&philo->args->m_death);
        if (philo->args->death_flag)
        {
            pthread_mutex_unlock(&philo->args->m_death);
            break ;
        }
        pthread_mutex_unlock(&philo->args->m_death);
        if (eat(philo))
            break ;
        philo->state = SLEEPING;
        print_state("is sleeping", philo->args->time_to_sleep, philo);
        print_state("is thinking", 0, philo);
    }
    return (NULL);
}
