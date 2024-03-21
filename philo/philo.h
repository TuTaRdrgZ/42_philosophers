/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:38:05 by bautrodr          #+#    #+#             */
/*   Updated: 2024/03/21 10:19:26 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define RST "\033[0m"    /* Reset to default color */
# define RED "\033[1;31m" /* Bold Red */
# define G "\033[1;32m"   /* Bold Green */
# define Y "\033[1;33m"   /* Bold Yellow */
# define B "\033[1;34m"   /* Bold Blue */
# define M "\033[1;35m"   /* Bold Magenta */
# define C "\033[1;36m"   /* Bold Cyan */
# define W "\033[1;37m"   /* Bold White */

typedef struct timeval	t_timeval;

enum					e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

typedef struct s_args
{
	int					philos_nb;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meals;
	int					death_flag;
	int					total_meal;
	long				initial_time;
	pthread_mutex_t		*printer;
}						t_args;

typedef struct s_philo
{
	pthread_t			philo_pid;
	pthread_mutex_t		fork;
	int					id;
	int					alive;
	int					eat_times;
	int					first_meal;
	long				last_meal;
	enum e_state		state;
	t_args				*args;
	struct s_philo		*next;
}						t_philo;

void					*supervisor(void *p_data);
void					print_error(char *str);
void					print_state(char *action, useconds_t delay,
							t_philo *philo);
void					*routine(void *p_data);
void					ft_msleep(int milliseconds);
int						is_digit_str(char *str);
int						ft_strlen(char *str);
void					ft_memdel(void *ptr);
void					free_philos(t_philo *head, t_args args);
long					ft_atoi(const char *str);
long					get_time_value(void);
int						init_data(t_args *args, char **argv, int argc);
t_philo					*init_philos(t_args *args);
#endif
