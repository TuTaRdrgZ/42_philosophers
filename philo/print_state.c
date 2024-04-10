/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:45:58 by bautrodr          #+#    #+#             */
/*   Updated: 2024/04/10 14:46:01 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_colors(t_philo *philo, char *action)
{
	if (!philo->args->death_flag && !philo->args->finish)
	{
		printf(Y "%ld " RST, get_timestamp());
		printf(M "%d " RST, philo->id);
		printf(C "%s\n" RST, action);
	}
}

void	print_state(char *action, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->printer);
	pthread_mutex_lock(&philo->args->m_death);
	print_colors(philo, action);
	pthread_mutex_unlock(&philo->args->m_death);
	pthread_mutex_unlock(&philo->args->printer);
}
