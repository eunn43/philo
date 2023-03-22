#include "philo.h"
#include <stdio.h>

int	init_forks(t_arg **arg)
{
	int	i;

	(*arg)->forks = (pthread_mutex_t *)malloc(sizeof (pthread_mutex_t) * (*arg)->num_of_philo);
	if (!(*arg)->forks)
		return (1);
	i = 0;
	while (i < (*arg)->num_of_philo)
		pthread_mutex_init(&(*arg)->forks[i++], NULL);
	pthread_mutex_init(&(*arg)->print, NULL);
	return (0);
}

t_arg	*set_arg(char **av)
{
	t_arg	*arg;
	int		ret;

	arg = (t_arg *)malloc(sizeof(t_arg));
	if (arg == NULL)
		return (0);
	ret = 0;
	if (ft_atoi(av[1], &arg->num_of_philo) || ft_atoi(av[2], &arg->time_to_die) ||\
		ft_atoi(av[3], &arg->time_to_eat) || ft_atoi(av[4], &arg->time_to_sleep))
		ret = 1;
	if (av[5] && ft_atoi(av[5], &arg->num_of_times_to_eat))
		ret = 1;
	else
		arg->num_of_times_to_eat = -1;
	if (ret)
		free(arg);
	return (arg);
}

void	ft_philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->forks[philo->id]);
	philo->stat = FORK;
	ft_philo_stat_print(philo);
	pthread_mutex_lock(&philo->arg->forks[philo->next_id]);
	philo->stat = EATING;
	ft_philo_stat_print(philo);
	
	philo->eat_count++;
}

void	ft_philo_stat_print(t_philo *philo)
{
	if (philo->stat == FORK)
		printf("%d [%d] has taken a fork\n", philo->timestamp, philo->id);
	else if (philo->stat == EATING)
		printf("%d [%d] is eating\n", philo->timestamp, philo->id);
	else if (philo->stat == SLEEPING)
		printf("%d [%d] is sleeping\n", philo->timestamp, philo->id);
	else if (philo->stat == THINKING)
		printf("%d [%d] is thinking\n", philo->timestamp, philo->id);
	else if (philo->stat == DIED)
		printf("%d [%d] died\n", philo->timestamp, philo->id);
}

void	ft_philo_sleeping(t_philo *philo)
{
	philo->stat = SLEEPING;
	ft_philo_stat_print(philo);
}

void	ft_philo_thinking(t_philo *philo)
{
	philo->stat = THINKING;
	ft_philo_stat_print(philo);
}

void	*philo_proc(void *data)
{
	t_philo	*philo;
	int		ret;

	philo = (t_philo *)data;
	ret = 0;

	if (philo->id % 2 == 0)
		usleep(philo->arg->time_to_die / 2);
	while (philo->stat != DIED)
	{
		ft_philo_eating(philo);
		ft_philo_sleeping(philo);
		ft_philo_thinking(philo);
	}
	return ((void *)ret);
}

void	ft_pthread(t_arg *arg, t_philo *philo)
{
	pthread_t		*pthread;
	pthread_mutex_t	mtx;
	int				i;
	int				result;

	pthread = (pthread_t *)malloc(sizeof(pthread_t) * arg->num_of_philo);
	if (pthread)
		return ;
	i = 0;
	pthread_mutex_init(&mtx, NULL);
	while (i < arg->num_of_philo)
	{
		if (pthread_create(&pthread[i], NULL, philo_proc, (void *) &philo[i]) < 0)
			return ;	//error
		pthread_join(pthread[i], &result);
		i++;
	}
	pthread_mutex_destroy(&mtx);
}

int	main(int ac, char **av)
{
	t_arg	*arg;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		return (1); // ac error
	arg = set_arg(av);
	if (arg == NULL)
		return (1);	// negative error
	philo = init_philo(arg);
	if (philo == NULL)
		return (1);	//malloc error
	ft_pthread(arg, philo);
}