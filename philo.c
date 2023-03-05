#include "philo.h"
#include <stdio.h>

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

void	ft_pthread(t_arg *arg, t_philo *philo)
{
	pthread_t		*pthread;
	pthread_mutex_t	mtx;
	int				i;

	pthread = (pthread_t *)malloc(sizeof(pthread_t) * arg->num_of_philo);
	if (pthread)
		return ;
	i = 0;
	pthread_mutex_init(&mtx, NULL);
	while (i < arg->num_of_philo)
	{
		if (pthread_create(&pthread[i], NULL, func, (void *)philo[i]) < 0)
			return ;	//error
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
	
}