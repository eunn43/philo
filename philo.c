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
	if (av[5] && ft_atoi(av[5], &arg->num_of_times))
		ret = 1;
	else
		arg->num_of_times = -1;
	if (ret)
		free(arg);
	return (arg);
}

int	main(int ac, char **av)
{
	t_arg	*arg;

	if (ac != 5 && ac != 6)
		return (1); // ac error
	arg = set_arg(av);
	if (arg == NULL)
		return (1);	// negative error
	
}
