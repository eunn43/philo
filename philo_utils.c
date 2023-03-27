#include "philo.h"

t_philo *init_philo(t_arg *arg)
{
    t_philo *philo;
    int     i;

    philo = (t_philo *)malloc(sizeof(t_philo) * arg->num_of_philo);
    if (!philo)
        return (0);
    i = 0;
    while (i < arg->num_of_philo)
    {
        philo[i].id = i;
		philo[i].next_id = i + 1;
		if (i + 1 == arg->num_of_philo)
			philo[i].next_id = 0;
		//philo[i].stat = INIT;
        philo[i].eat_count = 0;
		philo[i].arg = arg;
        i++;
    }
    return (philo);
}