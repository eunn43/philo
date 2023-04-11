/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjeon <seonjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:04:34 by seonjeon          #+#    #+#             */
/*   Updated: 2023/04/11 13:52:52 by seonjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_check_proc_flag(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->arg->proc_flag_mtx);
	ret = philo->arg->proc_flag;
	pthread_mutex_unlock(&philo->arg->proc_flag_mtx);
	return (ret);
}

void	ft_make_zero_proc_flag(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->proc_flag_mtx);
	philo->arg->proc_flag = 0;
	pthread_mutex_unlock(&philo->arg->proc_flag_mtx);
}

int	ft_atoi(const char *str, int *num)
{
	int					sign;
	long long			result;
	unsigned long long	i;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (1);
	while (str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i++] - '0';
	}
	result = sign * result;
	if (result > INT_MAX || result < 1)
		return (1);
	*num = result;
	return (0);
}
