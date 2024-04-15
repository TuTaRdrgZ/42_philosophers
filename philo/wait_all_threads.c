/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all_threads.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 10:42:12 by bautrodr          #+#    #+#             */
/*   Updated: 2024/04/13 10:42:21 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_args *args)
{
	int	ret;

	ret = 0;
	while (ret)
	{
		pthread_mutex_lock(&args->m_stop);
		ret = args->all_ready;
		pthread_mutex_unlock(&args->m_stop);
	}
}
