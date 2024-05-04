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

void	ft_start_simulation(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	data->first_time = ft_current_time();
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thrd_no, NULL,
				&ft_philo_handler, &data->philo[i]) != 0)
		{
			data->check_crate = 1;
			break ;
		}
		i++;
		usleep(50);
	}
	ft_finish_check(data);
	while (j < i)
	{
		pthread_join(data->philo[j].thrd_no, NULL);
		j++;
	}
}

void	ft_unlock_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_unlock(&data->fork[i]);
		i++;
	}
}

int	ft_is_eat_finish(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->data->eat_count == philo->data->nb_philo)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	return (0);
}

void	ft_finish_check(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == data->nb_philo)
			i = 0;
		pthread_mutex_lock(&data->philo->dead_mutex);
		if (ft_current_time() - data->philo[i].last_eat > data->time_to_die)
		{
			if (data->check_die == 0)
				printf("%lld %d is dead\n",
					ft_diff_time(data->philo), data->philo[i].id);
			data->check_die = 1;
			ft_unlock_forks(data);
			pthread_mutex_unlock(&data->philo->dead_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->philo->dead_mutex);
		if (ft_is_eat_finish(data->philo))
			break ;
		i++;
	}
}

void	ft_arg_check(char **argv, t_data *data)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit(argv[i][j]) == 0)
				ft_error_0("Error: Invalid argument!", data);
			j++;
		}
		i++;
	}
}
