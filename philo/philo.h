/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 11:38:05 by bautrodr          #+#    #+#             */
/*   Updated: 2024/04/14 00:53:25 by bautrodr         ###   ########.fr       */
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

typedef struct s_args
{
	int					philos_nb;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					max_meals;
	int					death_flag;
	int					finish_eating;
	int					finish;
	int					all_ready;
	pthread_mutex_t		printer;
	pthread_mutex_t		m_death;
	pthread_mutex_t		m_done;
	pthread_mutex_t		m_eat;
	pthread_mutex_t		m_stop;
	struct s_philo		*philo;
}						t_args;

typedef struct s_philo
{
	pthread_t			philo_pid;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		m_last_meal;
	pthread_mutex_t		m_eat_times;
	int					holding_left;
	int					holding_right;
	int					id;
	int					eat_times;
	int					alive;
	long				last_meal;
	t_args				*args;
}						t_philo;

void					wait_all_threads(t_args *args);
void					finish(t_args *args);
void					supervisor(void *p_data);
void					print_state(char *action, t_philo *philo);
void					*routine(void *p_data);
int						is_digit_str(char *str);
int						ft_strlen(char *str);
void					ft_memdel(void *ptr);
void					free_philos(t_args args);
long					ft_atoi(const char *str);
long					get_time_value(void);
time_t					get_timestamp(t_args *args);
time_t					get_timestampsuper(void);
void					ft_usleep(int ms);
int						init_data(t_args *args, char **argv, int argc);
int						init_philos(t_args *args);
int						ft_strcmp(const char *s1, const char *s2);
void					print_colors(t_philo *philo, char *action);
#endif
