/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:09:25 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/20 09:29:57 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_routine(t_args *args, t_philo *head)
{
	int		i;
	t_philo	*philo;

	i = 0;
	args->initial_time = get_time_value();
	philo = head;
	while (i < args->philos_nb)
	{
		pthread_create(&philo->philo_pid, NULL, routine, philo);
		pthread_detach(philo->philo_pid);
		philo = philo->next;
		i++;
	}
}

int main(int argc, char **argv)
{
	t_philo	*head;
	t_args   args;
	pthread_t	supervisor_pid;

	supervisor_pid = 0;
	if (argc == 5 || argc == 6)
	{
		if (!init_data(&args, argv, argc))
		{
			head = init_philos(&args);
			pthread_create(&supervisor_pid, NULL, supervisor, head);
			init_routine(&args, head);
			pthread_join(supervisor_pid, NULL);
			free_philos(head, args);
            return (0);
		}
		return (1);
	}
	else
	{
		print_error("Wrong input:\n"G"Correct input: ./philo <N-philos> <die-time>\
 <eat-time> <think-time> [<max-eat-count>]\n"RST);
		return (1);
	}
	return (0);
}
