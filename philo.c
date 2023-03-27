#include "philo.h"
#include <stdio.h>

int	init_forks(t_arg **arg)
{
	int	i;

	(*arg)->forks = (t_fork *)malloc(sizeof(t_fork) * (*arg)->num_of_philo);
	if (!(*arg)->forks)
		return (1);
	i = 0;
	while (i < (*arg)->num_of_philo)
	{
		(*arg)->forks[i].status = 0;
		pthread_mutex_init(&(*arg)->forks[i].access, NULL);
		i++;
	}
	pthread_mutex_init(&(*arg)->print, NULL);
	return (0);
}

void	free_arg(t_arg *arg)
{
	int	i;

	i = 0;
	while (i < arg->num_of_philo)
		pthread_mutex_destroy(&arg->forks[i++].access);
	free(arg->forks);
	pthread_mutex_destroy(&arg->print);
	free(arg);
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
	else if (!av[5])
		arg->num_of_times_to_eat = -1;
	if (ret)
	{
		free(arg);
		return (0);
	}
	ret = init_forks(&arg);
	if (ret)
	{
		free_arg(arg);
		return (0);
	}
	arg->proc_flag = 1;
	return (arg);
}

long long	ft_get_ms_time()
{
	struct timeval	tv;
	long long		ret;

	gettimeofday(&tv, NULL);
	ret = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ret);
}

void	ft_philo_stat_print(t_philo *philo, int	stat)
{
	struct timeval	timestamp;
	long long		time;

	if (philo->arg->proc_flag == 0)
		return ;
	pthread_mutex_lock(&philo->arg->print);
	gettimeofday(&timestamp, NULL);
	//time = timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000;
	time = timestamp.tv_usec;
	if (philo->arg->proc_flag && stat == FORK)
		printf("%lld  %d  has taken a fork\n", time, philo->id + 1);
	else if (philo->arg->proc_flag && stat == EATING)
		printf("%lld  %d  is eating\n", time, philo->id + 1);
	else if (philo->arg->proc_flag && stat == SLEEPING)
		printf("%lld  %d  is sleeping\n", time, philo->id + 1);
	else if (philo->arg->proc_flag && stat == THINKING)
		printf("%lld  %d  is thinking\n", time, philo->id + 1);
	else if (philo->arg->proc_flag && stat == DIED)
	{
		printf("%lld  %d  died\n", time, philo->id + 1);
		philo->arg->proc_flag = 0;
	}
	pthread_mutex_unlock(&philo->arg->print);

}

//void	ft_philo_eating(t_philo *philo)
//{
//	pthread_mutex_lock(&philo->arg->mtx);
//	if (philo->arg->forks[philo->id] == 0)
//		philo->arg->forks[philo->id] = 1;
//	pthread_mutex_unlock(&philo->arg->mtx);
//	pthread_mutex_lock(&philo->arg->mtx);
//	if (philo->arg->forks[philo->id] == 0)
//		philo->arg->forks[philo->next_id] = 1;
//	pthread_mutex_unlock(&philo->arg->mtx);
//	//philo->stat = FORK;
//	ft_philo_stat_print(philo, FORK);
//	if (philo->arg->forks[philo->id] && philo->arg->forks[philo->next_id])
//	{
//		//philo->stat = EATING;
//		ft_philo_stat_print(philo, EATING);
//		usleep(philo->arg->time_to_eat);
//		philo->last_eat_time = ft_get_ms_time();
//		philo->eat_count++;
//	}
//	pthread_mutex_lock(&philo->arg->mtx);
//	philo->arg->forks[philo->id] = 0;
//	philo->arg->forks[philo->next_id] = 0;
//	pthread_mutex_unlock(&philo->arg->mtx);
//}

void	ft_philo_eating_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->forks[philo->next_id].access);
	if (philo->arg->forks[philo->next_id].status == 0)
		philo->arg->forks[philo->next_id].status = 1;
	pthread_mutex_lock(&philo->arg->forks[philo->id].access);
	if (philo->arg->forks[philo->id].status == 0)
		philo->arg->forks[philo->id].status = 1;
	if (philo->arg->forks[philo->id].status && philo->arg->forks[philo->next_id].status)
	{
		ft_philo_stat_print(philo, FORK);
		ft_philo_stat_print(philo, EATING);
		usleep(philo->arg->time_to_sleep);
		philo->last_eat_time = ft_get_ms_time();
		philo->eat_count++;
		philo->arg->forks[philo->id].status = 0;
		philo->arg->forks[philo->next_id].status = 0;
	}
	pthread_mutex_unlock(&philo->arg->forks[philo->next_id].access);
	pthread_mutex_unlock(&philo->arg->forks[philo->id].access);
}

void	ft_philo_eating_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->forks[philo->id].access);
	if (philo->arg->forks[philo->id].status == 0)
		philo->arg->forks[philo->id].status = 1;
	pthread_mutex_lock(&philo->arg->forks[philo->next_id].access);
	if (philo->arg->forks[philo->next_id].status == 0)
		philo->arg->forks[philo->next_id].status = 1;
	if (philo->arg->forks[philo->id].status && philo->arg->forks[philo->next_id].status)
	{
		ft_philo_stat_print(philo, FORK);
		ft_philo_stat_print(philo, EATING);
		usleep(philo->arg->time_to_sleep);
		philo->last_eat_time = ft_get_ms_time();
		philo->eat_count++;
		philo->arg->forks[philo->id].status = 0;
		philo->arg->forks[philo->next_id].status = 0;
	}
	pthread_mutex_unlock(&philo->arg->forks[philo->id].access);
	pthread_mutex_unlock(&philo->arg->forks[philo->next_id].access);
}

void	ft_philo_sleeping(t_philo *philo)
{
	//philo->stat = SLEEPING;
	ft_philo_stat_print(philo, SLEEPING);
	usleep(philo->arg->time_to_sleep);
}

void	ft_philo_thinking(t_philo *philo)
{
	//philo->stat = THINKING;
	ft_philo_stat_print(philo, THINKING);
}

void	*ft_philo_proc(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2)
		usleep(philo->arg->time_to_eat);
	while (philo->arg->proc_flag)
	{
		if (philo->id % 2)
			ft_philo_eating_odd(philo);
		else
			ft_philo_eating_even(philo);
		ft_philo_sleeping(philo);
		ft_philo_thinking(philo);
	}
	return (NULL);
}

void	ft_check_philo_died(t_arg *arg, t_philo *philo)
{
	int			i;
	int			min_cnt;
	long long	cur_ms;

	while (arg->proc_flag)
	{
		i = 0;
		if (arg->num_of_times_to_eat == -1)
			min_cnt = INT_MIN;
		else
			min_cnt = INT_MAX;
		while (i < arg->num_of_philo)
		{
			cur_ms = ft_get_ms_time();
			//printf("diff ms : %lld\n", cur_ms - philo[i].last_eat_time);
			if ((cur_ms - philo[i].last_eat_time) >= arg->time_to_die)
			{
				//philo[i].stat = DIED;
				ft_philo_stat_print(&philo[i], DIED);
				break ;
			}
			if (philo[i].eat_count < min_cnt)
				min_cnt = philo[i].eat_count;
			i++;
		}
		if (min_cnt >= arg->num_of_times_to_eat)
			arg->proc_flag = 0;
	}
}

void	free_philo(t_philo *philo)
{
	free_arg(philo->arg);
	free(philo);
}

void	ft_pthread(t_arg *arg, t_philo *philo)
{
	pthread_t		*pthread;
	int				i;

	pthread = (pthread_t *)malloc(sizeof(pthread_t) * arg->num_of_philo);
	if (!pthread)
		return ;
	i = 0;
	while (i < arg->num_of_philo)
	{
		philo[i].last_eat_time = ft_get_ms_time();
		if (pthread_create(&pthread[i], NULL, ft_philo_proc, (void *) &philo[i]) < 0)
			return ;	//error
		i++;
	}
	ft_check_philo_died(arg, philo);
	i = 0;
	while (i < arg->num_of_philo)
		pthread_join(pthread[i++], NULL);
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
	free_philo(philo);
}