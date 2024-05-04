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

void	ft_error_0(char *str, t_data *data)
{
	printf("\033[0;31m%s\n\033[0m", str);
	free(data);
	exit(1);
}

void	ft_error_1(char *str, t_data *data)
{
	printf("\033[0;31m%s\n\033[0m", str);
	free(data->fork);
	free(data->philo);
	free(data);
	exit(1);
}

void	ft_full_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->philo[i]
			.data->fork[data->philo->left_fork]);
		pthread_mutex_destroy(&data->philo[i]
			.data->fork[data->philo->right_fork]);
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&data->philo[i].write_mutex);
		pthread_mutex_destroy(&data->philo[i].meal_mutex);
		pthread_mutex_destroy(&data->philo[i].dead_mutex);
		i++;
	}
	free(data->fork);
	free(data->philo);
	if (data->check_crate)
	{
		free(data);
		printf("\033[0;31mError: Thread crate problem !\n\033[0m");
		exit (1);
	}
	free(data);
	exit(0);
}
