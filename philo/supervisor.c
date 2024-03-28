/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:01:09 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/28 16:25:47 by bautrodr         ###   ########.fr       */
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
    free(args->philo);
}

void	supervisor(void *p_args)
{
	int	    i;
    t_args  *args;

    args = (t_args *)p_args;
	i = 0;
	while (1)
	{
        /*printf("------------------------------------------\n");
        printf("           philo %d\n", args->philo[i].id);
        printf("           last_meal: %ld\n", args->philo[i].last_meal);
        printf("           time_to_die: %d\n", args->time_to_die);
        printf("           last meal + time_to_die: %ld\n", args->philo[i].last_meal + args->time_to_die);
        printf("           time: %ld\n", get_timestamp());*/
        pthread_mutex_unlock(&args->m_time);
        pthread_mutex_lock(&args->m_time);
        if (args->philo[i].last_meal + args->time_to_die <= get_timestamp() && args->philo[i].state != EATING)
        {
            pthread_mutex_lock(&args->m_death);
            args->death_flag = 1;
			printf(RED "Philo %d died\n" RST, args->philo[i].id);
            pthread_mutex_unlock(&args->m_death);
            pthread_mutex_unlock(&args->m_time);
            break ;
        }
        if (args->finish_eating == args->philos_nb)
        {
            printf(G "All philos ate %d times\n" RST, args->max_meals);
            break ;
        }
        if (i == args->philos_nb - 1)
            i = 0;
        else
            i++;
        usleep(100);
	}
	finish(args);
}
