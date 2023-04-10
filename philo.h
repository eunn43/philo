/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seonjeon <seonjeon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:02:07 by seonjeon          #+#    #+#             */
/*   Updated: 2023/04/10 18:51:24 by seonjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>	//usleep
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>	//gettimeofday
# include <pthread.h>
# include <limits.h>

enum	e_status
{
	INIT,
	FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct s_fork
{
	int				status;
	pthread_mutex_t	access;
}	t_fork;

typedef struct s_arg
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_to_eat;
	int				proc_flag;
	pthread_mutex_t	proc_flag_mtx;
	t_fork			*forks;
	pthread_mutex_t	print;
	long long		start_time;
}	t_arg;

typedef struct s_philo
{
	int				id;
	int				next_id;
	int				eat_count;
	long long		last_eat_time;
	pthread_mutex_t	eat_mtx;
	t_arg			*arg;
}	t_philo;

//color
# define CLIGHT_CYAN	"\x1b[96m"
# define CBLUE			"\x1b[34m"
# define CRED			"\x1b[31m"
# define CRESET			"\x1b[0m"

//philo
void		*ft_philo_proc(void *data);
// void		ft_check_philo_died(t_arg *arg, t_philo *philo);
void		ft_pthread(t_arg *arg, t_philo *philo);

//init
int			init_forks(t_arg **arg);
t_arg		*set_arg(char **av);
t_philo		*init_philo(t_arg *arg);
void		free_arg(t_arg *arg);
void		free_philo(t_philo *philo);

//philo_utils
void		ft_philo_doing(t_philo *philo, long long time);
void		ft_philo_stat_print(t_philo *philo, int stat);
void		ft_philo_eating(t_philo *philo);
void		ft_philo_sleeping(t_philo *philo);
void		ft_philo_thinking(t_philo *philo);

//utils
long long	ft_get_time(void);
int			ft_check_proc_flag(t_philo *philo);
void		ft_make_zero_proc_flag(t_philo *philo);
int			ft_atoi(const char *str, int *num);
#endif