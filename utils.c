#include "philo.h"

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
	if (result > INT_MAX || result < INT_MIN)
		return (1);
	*num = result;
	return (0);
}