/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjeon <seonjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:04:13 by seonjeon          #+#    #+#             */
/*   Updated: 2023/03/31 18:24:23 by seonjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_doing(t_philo *philo, long long time)
{
	long long	cur_time;

	cur_time = ft_get_time();
	while (philo->arg->proc_flag)
	{
		if (ft_get_time() - cur_time >= time)
			return ;
		usleep(time * 100);
	}
}

void	ft_philo_stat_print(t_philo *philo, int stat)
{
	long long		time;

	if (philo->arg->proc_flag == 0)
		return ;
	pthread_mutex_lock(&philo->arg->print);
	time = ft_get_time() - philo->arg->start_time;
	if (philo->arg->proc_flag && stat == FORK)
		printf("%lld  %d  has taken a fork\n", time, philo->id + 1);
	else if (philo->arg->proc_flag && stat == EATING)
		printf(CLIGHT_CYAN "%lld  %d  is eating\n" CRESET, time, philo->id + 1);
	else if (philo->arg->proc_flag && stat == SLEEPING)
		printf("%lld  %d  is sleeping\n", time, philo->id + 1);
	else if (philo->arg->proc_flag && stat == THINKING)
		printf(CBLUE "%lld  %d  is thinking\n" CRESET, time, philo->id + 1);
	else if (philo->arg->proc_flag && stat == DIED)
	{
		printf(CRED "%lld  %d  died\n" CRESET, time, philo->id + 1);
		philo->arg->proc_flag = 0;
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
		ft_philo_stat_print(philo, EATING);
		philo->last_eat_time = ft_get_time();
		philo->eat_count++;
		ft_philo_doing(philo, philo->arg->time_to_eat);
		philo->last_eat_time = ft_get_time();
	}
	philo->arg->forks[philo->id].status = 0;
	philo->arg->forks[philo->next_id].status = 0;
	pthread_mutex_unlock(&philo->arg->forks[philo->next_id].access);
	pthread_mutex_unlock(&philo->arg->forks[philo->id].access);
}

void	ft_philo_sleeping(t_philo *philo)
{
	ft_philo_stat_print(philo, SLEEPING);
	ft_philo_doing(philo, philo->arg->time_to_sleep);
}

void	ft_philo_thinking(t_philo *philo)
{
	ft_philo_stat_print(philo, THINKING);
}
