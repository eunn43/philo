#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>		//usleep
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

typedef struct s_arg
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_to_eat;
	pthread_mutex_t	*print;
	pthread_mutex_t	*forks;
}	t_arg;

typedef struct s_philo
{
	int		id;
	int		next_id;
	int		stat;
	timeval	timestamp;
	int		eat_count;
	t_arg	*arg;
}	t_philo;
//philo

//utils
int		ft_atoi(const char *str, int *num);
//philo_tuils
t_philo	*init_philo(t_arg *arg);
#endif