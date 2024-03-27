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

void    print_colors(t_philo *philo, char *action)
{
    if (!philo->args->death_flag && philo->args->philos_nb > 0)
    {
        printf(Y "%ld " RST, get_timestamp());
        printf(M "%d " RST, philo->id);
        printf(C "%s\n" RST, action);
    }
}

void	print_state(char *action, useconds_t delay, t_philo *philo)
{
    pthread_mutex_lock(&philo->args->printer);
    print_colors(philo, action);
    pthread_mutex_unlock(&philo->args->printer);
	if (delay > 0)
		ft_msleep(delay);
}

int	eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_state(W "has taken a fork" RST, 0, philo);
    pthread_mutex_lock(&philo->right_fork);
    print_state(W "has taken a fork" RST, 0, philo);
    print_state(B "is eating" RST, philo->args->time_to_eat, philo);
    philo->state = EATING;
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(&philo->right_fork);
    pthread_mutex_lock(&philo->m_eat_times);
    philo->eat_times++;
    philo->last_meal = get_timestamp();
    pthread_mutex_unlock(&philo->m_eat_times);
    if (philo->eat_times == philo->args->max_meals)
    {
        pthread_mutex_lock(&philo->args->m_eat);
        philo->args->finish_eating++;
        pthread_mutex_unlock(&philo->args->m_eat);
        return (1);
    }
    return (0);
}

void	*routine(void *p_data)
{
    t_philo	*philo;

    philo = (t_philo *)p_data;
    if (philo->id % 2 == 0)
        ft_msleep(philo->args->time_to_eat * 0.1);
    while (philo->alive && !philo->args->death_flag)
    {
        pthread_mutex_lock(&philo->args->m_time);
        philo->state = THINKING;
        pthread_mutex_unlock(&philo->args->m_time);
        if (eat(philo))
            break ;
        print_state("is sleeping", philo->args->time_to_sleep, philo);
        philo->state = SLEEPING;
        print_state("is thinking", 0, philo);
    }
    return (NULL);
}
