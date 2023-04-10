/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjeon <seonjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:07:02 by seonjeon          #+#    #+#             */
/*   Updated: 2023/04/10 18:36:19 by seonjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_arg **arg)
{
	int	i;

	(*arg)->forks = (t_fork *)malloc(sizeof(t_fork) * (*arg)->num_of_philo);
	if (!(*arg)->forks)
		return (1);
	pthread_mutex_init(&(*arg)->proc_flag_mtx, NULL);
	i = 0;
	while (i < (*arg)->num_of_philo)
	{
		(*arg)->forks[i].status = 0;
		pthread_mutex_init(&(*arg)->forks[i++].access, NULL);
	}
	pthread_mutex_init(&(*arg)->print, NULL);
	return (0);
}

t_arg	*set_arg(char **av)
{
	t_arg	*arg;
	int		ret;

	arg = (t_arg *)malloc(sizeof(t_arg));
	if (!arg)
		return (0);
	ret = 0;
	if (ft_atoi(av[1], &arg->num_of_philo) || \
		ft_atoi(av[2], &arg->time_to_die) || \
		ft_atoi(av[3], &arg->time_to_eat) || \
		ft_atoi(av[4], &arg->time_to_sleep))
		ret = 1;
	if (av[5] && (ft_atoi(av[5], &arg->num_of_times_to_eat) == 1))
		ret = 1;
	else if (!av[5])
		arg->num_of_times_to_eat = -1;
	arg->proc_flag = 1;
	arg->forks = NULL;
	arg->start_time = 0;
	if (ret == 0 && init_forks(&arg) == 0)
		return (arg);
	free_arg(arg);
	return (0);
}

t_philo	*init_philo(t_arg *arg)
{
	t_philo	*philo;
	int		i;

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
		philo[i].eat_count = arg->num_of_times_to_eat;
		philo[i].last_eat_time = 0;
		pthread_mutex_init(&philo[i].eat_mtx, NULL);
		philo[i].arg = arg;
		i++;
	}
	return (philo);
}

void	free_arg(t_arg *arg)
{
	int	i;

	if (arg->forks)
	{
		i = 0;
		while (i < arg->num_of_philo)
			pthread_mutex_destroy(&arg->forks[i++].access);
		free(arg->forks);
		pthread_mutex_destroy(&arg->proc_flag_mtx);
		pthread_mutex_destroy(&arg->print);
	}
	free(arg);
}

void	free_philo(t_philo *philo)
{
	int	i;
	int	len;

	i = 0;
	len = philo->arg->num_of_philo;
	free_arg(philo->arg);
	while (i < len)
	{
		philo->arg = NULL;
		pthread_mutex_destroy(&philo[i++].eat_mtx);
	}
	free(philo);
}
