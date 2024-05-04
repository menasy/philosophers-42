/*
 ███▄ ▄███▓▓█████  ███▄    █  ▄▄▄        ██████▓██   ██▓
▓██▒▀█▀ ██▒▓█   ▀  ██ ▀█   █ ▒████▄    ▒██    ▒ ▒██  ██▒
▓██    ▓██░▒███   ▓██  ▀█ ██▒▒██  ▀█▄  ░ ▓██▄    ▒██ ██░
▒██    ▒██ ▒▓█  ▄ ▓██▒  ▐▌██▒░██▄▄▄▄██   ▒   ██▒ ░ ▐██▓░
▒██▒   ░██▒░▒████▒▒██░   ▓██░ ▓█   ▓██▒▒██████▒▒ ░ ██▒▓░
░ ▒░   ░  ░░░ ▒░ ░░ ▒░   ▒ ▒  ▒▒   ▓▒█░▒ ▒▓▒ ▒ ░  ██▒▒▒
░  ░      ░ ░ ░  ░░ ░░   ░ ▒░  ▒   ▒▒ ░░ ░▒  ░ ░▓██ ░▒░
░      ░      ░      ░   ░ ░   ░   ▒   ░  ░  ░  ▒ ▒ ░░
       ░      ░  ░         ░       ░  ░      ░  ░ ░
                                                ░ ░*/

#include "philo.h"

long	ft_atoi(const char *str)
{
	char		*cstr;
	int			i;
	int			sign;
	long		num;

	i = 0;
	num = 0;
	sign = 1;
	cstr = (char *)str;
	while ((cstr[i] >= 9 && cstr[i] <= 13) || cstr[i] == ' ')
		i++;
	if (cstr[i] == '-' || cstr[i] == '+')
	{
		if (cstr[i] == '-')
			sign *= -1;
		i++;
	}
	while (cstr[i] >= '0' && cstr[i] <= '9')
	{
		num = ((num * 10) + cstr[i] - '0');
		i++;
	}
	return (sign * num);
}

long long	ft_current_time(void)
{
	struct timeval	timeval;

	if (gettimeofday(&timeval, NULL) == -1)
		return (0);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

long long	ft_diff_time(t_philo *philo)
{
	long long	diff_time;

	diff_time = ft_current_time() - philo->data->first_time;
	return (diff_time);
}

int	ft_write_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->write_mutex);
	if (ft_is_dead(philo) != 0)
	{
		pthread_mutex_unlock(&philo->write_mutex);
		return (1);
	}
	printf("%lld %d %s\n", ft_diff_time(philo), philo->id, str);
	pthread_mutex_unlock(&philo->write_mutex);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
