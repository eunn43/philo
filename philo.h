#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>	//usleep
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>	//gettimeofday
# include <pthread.h>
# include <limits.h>
# include <string.h>	//memset

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
	int	status;
	pthread_mutex_t access;
}	t_fork;

typedef struct s_arg
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_to_eat;
	int				proc_flag;
	t_fork			*forks;
	pthread_mutex_t	print;
}	t_arg;

typedef struct s_philo
{
	int			id;
	int			next_id;
	//int			stat;
	long long	last_eat_time;
	int			eat_count;
	t_arg		*arg;
}	t_philo;
//philo

//utils
int		ft_atoi(const char *str, int *num);
//philo_tuils
t_philo	*init_philo(t_arg *arg);
#endif