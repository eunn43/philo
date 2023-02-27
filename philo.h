#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>		//usleep
#include <stdio.h>
#include <sys/time.h>	//gettimeofday

enum	e_status
{
	FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED
};

typedef struct s_philo
{
	int	status;
	
}	t_philo;

#endif