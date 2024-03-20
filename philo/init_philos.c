/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:07:12 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/20 09:16:12 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		free_philos(t_philo *head, t_args args)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	while (i < args.philos_nb - 1)
	{
		tmp = head;
		head = head->next;
		pthread_mutex_destroy(&tmp->fork);
		ft_memdel(tmp);
		i++;
	}
	pthread_mutex_destroy(args.printer);
	ft_memdel(args.printer);
	ft_memdel(head);
}

t_philo		*init_link(int id, t_args *arg)
{
	t_philo *philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = id;
	philo->alive = 1;
	philo->state = THINKING;
	philo->args = arg;
	philo->first_meal = 0;
	philo->eat_times = 0;
	philo->next = philo;
	pthread_mutex_init(&philo->fork, NULL);
	return (philo);
}

t_philo		*init_philos(t_args *args)
{
	t_philo	*philo;
	t_philo *new_philo;
	t_philo	*head;
	int		i;

	philo = init_link(1, args);
	if (!philo)
		return (NULL);
	head = philo;
	i = 1;
	while (i <= args->philos_nb - 1)
	{
		i++;
		new_philo = init_link(i, args);
		if (!new_philo)
			return (NULL);
		philo->next = new_philo;
		philo = new_philo;
	}
	philo->next = head;
	return (head);
}
