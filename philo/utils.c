/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:43:25 by bautrodr          #+#    #+#             */
/*   Updated: 2024/02/08 11:31:57 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int is_digit(char c)
{
	return ((c >= '0' && c <= '9') || c == '+');
}

int	is_digit_str(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (-1);
		i++;
	}
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void		ft_memdel(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

long	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	result = 0;
	sign = 1;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + str[i++] - '0';
	return (result * sign);
}

long		get_time_value(void)
{
	t_timeval timestamp;

	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
}

void		ft_msleep(int milliseconds)
{
	long	time;

	time = get_time_value();
	while (get_time_value() < time + milliseconds)
		usleep(milliseconds);
}

void	print_error(char *str)
{
	printf(RED"%s"RST, str);
}
