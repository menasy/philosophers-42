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

void	ft_init(char **argv, t_data *data)
{
	if (argv[1] && argv[2] && argv[3] && argv[4])
	{
		data->nb_philo = ft_atoi(argv[1]);
		data->time_to_die = ft_atoi(argv[2]);
		data->time_to_eat = ft_atoi(argv[3]);
		data->time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
		{
			data->must_eat = ft_atoi(argv[5]);
			if (data->must_eat <= 0)
				ft_error_0("Error: Invalid argument!", data);
		}
		else
			data->must_eat = -1;
	}
	else
		ft_error_0("Error: Invalid argument!", data);
	if (data->nb_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		ft_error_0("Error: Invalid argument!", data);
	data->check_die = 0;
	data->check_crate = 0;
	data->eat_count = 0;
}

void	ft_init_philo_fork(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	data->fork = malloc (sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->philo || !data->fork)
		ft_error_1("Error: Memory problem!", data);
	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].must_eat_count = data->must_eat;
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->nb_philo;
		data->philo[i].data = data;
		pthread_mutex_init(&data->fork[i], NULL);
		pthread_mutex_init(&data->fork[data->philo[i].left_fork], NULL);
		pthread_mutex_init(&data->fork[data->philo[i].right_fork], NULL);
		pthread_mutex_init(&data->philo[i].meal_mutex, NULL);
		pthread_mutex_init(&data->philo[i].dead_mutex, NULL);
		pthread_mutex_init(&data->philo[i].write_mutex, NULL);
	}
}

int	main(int ac, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		ft_error_0("Error: Memory problem!", data);
	if (!(ac == 5 || ac == 6))
		ft_error_0("Error: Invalid argument!", data);
	ft_arg_check(argv, data);
	ft_init(argv, data);
	ft_init_philo_fork(data);
	ft_start_simulation(data);
	ft_full_free(data);
}
