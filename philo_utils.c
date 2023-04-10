/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjeon <seonjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:04:13 by seonjeon          #+#    #+#             */
/*   Updated: 2023/04/10 19:15:13 by seonjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_doing(t_philo *philo, long long time)
{
	long long	cur_time;

	cur_time = ft_get_time();
	while (ft_check_proc_flag(philo))
	{
		if (ft_get_time() - cur_time >= time)
			return ;
		usleep(100);
	}
}

void	ft_philo_stat_print(t_philo *philo, int stat)
{
	long long		time;

	if (ft_check_proc_flag(philo) == 0)
		return ;
	pthread_mutex_lock(&philo->arg->print);
	time = ft_get_time() - philo->arg->start_time;
	if (stat == FORK)
		printf("%lld %d has taken a fork\n", time, philo->id + 1);
	else if (stat == EATING)
		printf(CLIGHT_CYAN "%lld %d is eating\n" CRESET, time, philo->id + 1);
	else if (stat == SLEEPING)
		printf("%lld %d is sleeping\n", time, philo->id + 1);
	else if (stat == THINKING)
		printf(CBLUE "%lld %d is thinking\n" CRESET, time, philo->id + 1);
	else if (stat == DIED)
	{
		printf(CRED "%lld %d died\n" CRESET, time, philo->id + 1);
		ft_make_zero_proc_flag(philo);
	}
	pthread_mutex_unlock(&philo->arg->print);
}

void	ft_philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->forks[philo->next_id].access);
	philo->arg->forks[philo->next_id].status = 1;
	ft_philo_stat_print(philo, FORK);
	if (philo->arg->forks[philo->id].status && \
		philo->arg->forks[philo->next_id].status)
	{
		pthread_mutex_lock(&philo->eat_mtx);
		ft_philo_stat_print(philo, EATING);
		philo->eat_count--;
		philo->last_eat_time = ft_get_time();
		pthread_mutex_unlock(&philo->eat_mtx);
		ft_philo_doing(philo, philo->arg->time_to_eat);
	}
	philo->arg->forks[philo->id].status = 0;
	philo->arg->forks[philo->next_id].status = 0;
	pthread_mutex_unlock(&philo->arg->forks[philo->next_id].access);
	pthread_mutex_unlock(&philo->arg->forks[philo->id].access);
}

void	ft_philo_sleeping(t_philo *philo)
{
	if (ft_check_proc_flag(philo) == 0)
		return ;
	ft_philo_stat_print(philo, SLEEPING);
	ft_philo_doing(philo, philo->arg->time_to_sleep);
}

void	ft_philo_thinking(t_philo *philo)
{
	if (ft_check_proc_flag(philo) == 0)
		return ;
	ft_philo_stat_print(philo, THINKING);
}
