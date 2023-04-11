/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjeon <seonjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:48:16 by seonjeon          #+#    #+#             */
/*   Updated: 2023/04/11 20:45:11 by seonjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo_proc(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2)
		usleep(1000);
	while (ft_check_proc_flag(philo))
	{
		if (ft_philo_get_left_fork(philo))
			break ;
		ft_philo_eating(philo);
		ft_philo_sleeping_and_thinking(philo);
	}
	return (NULL);
}

void	ft_check_philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->eat_mtx);
	if (ft_get_time() - philo->last_eat_time >= philo->arg->time_to_die)
		ft_philo_stat_print(philo, DIED);
	pthread_mutex_unlock(&philo->eat_mtx);
}

void	ft_check_philo_stat(t_arg *arg, t_philo *philo)
{
	int	i;
	int	eat_cnt;

	while (ft_check_proc_flag(philo))
	{
		i = 0;
		eat_cnt = INT_MAX;
		if (arg->num_of_times_to_eat == -1)
			eat_cnt = -1;
		while (ft_check_proc_flag(philo) && i < arg->num_of_philo)
		{
			ft_check_philo_died(&philo[i]);
			pthread_mutex_lock(&philo[i].eat_mtx);
			if (philo[i].eat_count < eat_cnt)
				eat_cnt = philo[i].eat_count;
			pthread_mutex_unlock(&philo[i].eat_mtx);
			i++;
		}
		if (eat_cnt >= arg->num_of_times_to_eat)
			ft_make_zero_proc_flag(philo);
	}
}

void	ft_pthread(t_arg *arg, t_philo *philo)
{
	pthread_t	*pthread;
	int			i;

	pthread = (pthread_t *)malloc(sizeof(pthread_t) * arg->num_of_philo);
	if (!pthread)
		return ;
	i = 0;
	arg->start_time = ft_get_time();
	while (i < arg->num_of_philo)
	{
		philo[i].last_eat_time = ft_get_time();
		if (pthread_create(&pthread[i], NULL, \
			ft_philo_proc, (void *) &philo[i]) < 0)
			return ;
		i++;
	}
	ft_check_philo_stat(arg, philo);
	i = 0;
	while (i < arg->num_of_philo)
		pthread_join(pthread[i++], NULL);
	free(pthread);
}

int	main(int ac, char **av)
{
	t_arg	*arg;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		return (1);
	arg = set_arg(av);
	if (arg == NULL)
		return (1);
	philo = init_philo(arg);
	if (philo == NULL)
	{
		free_arg(arg);
		return (1);
	}
	ft_pthread(arg, philo);
	free_philo(philo);
	return (0);
}
