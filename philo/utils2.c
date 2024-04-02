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

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

long	get_time_value(void)
{
	t_timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
}

void	ft_usleep(int ms)
{
	long int	time;

	time = get_time_value();
	while (get_time_value() - time < ms)
		usleep(100);
}

time_t	get_timestamp(void)
{
	static time_t	start_time = 0;
	struct timeval	t;

	if (start_time == 0)
	{
		gettimeofday(&t, NULL);
		start_time = ((t.tv_sec * 1000) + t.tv_usec / 1000);
	}
	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000 + t.tv_usec / 1000) - start_time);
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
