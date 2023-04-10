/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjeon <seonjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:48:16 by seonjeon          #+#    #+#             */
/*   Updated: 2023/04/10 18:50:42 by seonjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo_proc(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2)
		usleep(100);
	while (ft_check_proc_flag(philo))
	{
		pthread_mutex_lock(&philo->arg->forks[philo->id].access);
		philo->arg->forks[philo->id].status = 1;
		ft_philo_stat_print(philo, FORK);
		if (philo->id == philo->next_id)
		{
			usleep(philo->arg->time_to_die * 1000);
			ft_philo_stat_print(philo, DIED);
			pthread_mutex_unlock(&philo->arg->forks[philo->id].access);
			break ;
		}
		ft_philo_eating(philo);
		if (philo->eat_count == 0)
			ft_make_zero_proc_flag(philo);
		ft_philo_sleeping(philo);
		ft_philo_thinking(philo);
	}
	return (NULL);
}

void	ft_check_philo_died(t_arg *arg, t_philo *philo)
{
	int	i;

	while (ft_check_proc_flag(philo))
	{
		i = 0;
		while (i < arg->num_of_philo)
		{
			pthread_mutex_lock(&philo[i].eat_mtx);
			if ((ft_get_time() - philo[i].last_eat_time) >= arg->time_to_die)
			{
				ft_philo_stat_print(&philo[i], DIED);
				pthread_mutex_unlock(&philo[i].eat_mtx);
				return ;
			}
			pthread_mutex_unlock(&philo[i].eat_mtx);
			i++;
		}
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
	ft_check_philo_died(arg, philo);
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
