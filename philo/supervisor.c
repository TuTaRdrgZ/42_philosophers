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

void	*supervisor(void *p_data)
{
	t_philo	*tmp;
	long	time;

	tmp = (t_philo *)p_data;
	while (tmp->next != NULL && tmp->alive)
	{
		time = get_time_value();
		if (tmp->first_meal != 0 && time
			- tmp->last_meal > tmp->args->time_to_die)
		{
			tmp->alive = 0;
			tmp->state = DEAD;
			print_state("died", 0, tmp);
		}
		if (tmp->args->total_meal == tmp->args->philos_nb)
		{
			tmp->alive = 0;
			tmp->state = DEAD;
		}
		tmp = tmp->next;
	}
	return (tmp);
}
