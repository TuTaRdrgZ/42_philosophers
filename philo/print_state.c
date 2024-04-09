#include "philo.h"

void    print_colors(t_philo *philo, char *action)
{
    if (!philo->args->death_flag && philo->args->philos_nb > 0)
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
