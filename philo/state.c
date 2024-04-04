/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:51:44 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/28 16:47:49 by bautrodr         ###   ########.fr       */
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

void	print_state(char *action, t_philo *philo)
{
    pthread_mutex_lock(&philo->args->printer);
    print_colors(philo, action);
    pthread_mutex_unlock(&philo->args->printer);
}

int	eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_state(W "has taken a fork" RST, philo);
    pthread_mutex_lock(&philo->right_fork);
    print_state(W "has taken a fork" RST, philo);
	pthread_mutex_lock(&philo->m_state);
    philo->state = EATING;
	pthread_mutex_unlock(&philo->m_state);
    print_state(B "is eating" RST, philo);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(&philo->right_fork);
    pthread_mutex_lock(&philo->m_eat_times);
    philo->eat_times++;
    philo->last_meal = get_timestamp();
    pthread_mutex_unlock(&philo->m_eat_times);
    ft_usleep(philo->args->time_to_eat);
    if (philo->eat_times == philo->args->max_meals)
    {
        pthread_mutex_lock(&philo->args->m_eat);
        philo->args->finish_eating++;
        pthread_mutex_unlock(&philo->args->m_eat);
        return (1);
    }
    return (0);
}

int philo_sleep(t_philo *philo)
{
    pthread_mutex_lock(&philo->args->m_death);
    if (philo->args->death_flag)
        return (1);
    pthread_mutex_unlock(&philo->args->m_death);
    pthread_mutex_lock(&philo->m_state);
    philo->state = SLEEPING;
    pthread_mutex_unlock(&philo->m_state);
    print_state(G "is sleeping" RST, philo);
    ft_usleep(philo->args->time_to_sleep);
    return (0);
}

int think(t_philo *philo)
{
    pthread_mutex_lock(&philo->args->m_death);
    if (philo->args->death_flag)
        return (1);
    pthread_mutex_unlock(&philo->args->m_death);
    pthread_mutex_lock(&philo->m_state);
    philo->state = THINKING;
    pthread_mutex_unlock(&philo->m_state);
    print_state(C "is thinking" RST, philo);
    return (0);
}

void	*routine(void *p_data)
{
    t_philo	*philo;

    philo = (t_philo *)p_data;
    if (philo->id % 2 == 0)
        ft_usleep(philo->args->time_to_eat * 0.1);
    while (1)
    {
        pthread_mutex_lock(&philo->args->m_death);
        if (philo->args->death_flag)
        {
            pthread_mutex_unlock(&philo->args->m_death);
            return (NULL);
        }
        pthread_mutex_unlock(&philo->args->m_death);
        if (eat(philo))
            break ;
        if (philo_sleep(philo))
            break ;
        if (think(philo))
            break ;
    }
    return (NULL);
}
