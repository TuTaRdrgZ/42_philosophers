/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:12:37 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/21 10:12:46 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_value(void)
{
	t_timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
}

void	ft_msleep(int milliseconds)
{
	long	time;

	time = get_time_value();
	while (get_time_value() < time + milliseconds)
		usleep(milliseconds);
}

void	print_error(char *str)
{
	printf(RED "%s" RST, str);
}
