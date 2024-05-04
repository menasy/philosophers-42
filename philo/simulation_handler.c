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

void	*ft_philo_handler(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	philo->last_eat = ft_current_time();
	if (philo->id % 2 == 0)
		usleep(50);
	while (1)
	{
		pthread_mutex_lock(&philo->meal_mutex);
		if (philo->data->eat_count == philo->data->nb_philo)
		{
			pthread_mutex_unlock(&philo->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philo->meal_mutex);
		if (ft_is_dead(philo))
			return (0);
		if (ft_eat(philo))
			return (0);
		if (ft_sleep_think(philo))
			return (0);
	}
	return (NULL);
}

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
	ft_write_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
	ft_write_message(philo, "has taken a fork");
	philo->last_eat = ft_current_time();
	pthread_mutex_unlock(&philo->dead_mutex);
	ft_write_message(philo, "is eating");
	if (ft_wait(philo, philo->data->time_to_eat))
		return (1);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->must_eat_count--;
	if (philo->must_eat_count == 0)
	{
		philo->data->eat_count++;
		pthread_mutex_unlock(&philo->meal_mutex);
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
	return (0);
}

int	ft_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	if (philo->data->eat_count == philo->data->nb_philo)
	{
		pthread_mutex_unlock(&philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&philo->dead_mutex);
	if (philo->data->check_die == 1)
	{
		pthread_mutex_unlock(&philo->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->dead_mutex);
	return (0);
}

int	ft_sleep_think(t_philo *philo)
{
	if (ft_write_message(philo, "is sleeping"))
		return (1);
	if (ft_wait(philo, philo->data->time_to_sleep))
		return (1);
	if (ft_write_message(philo, "is thinking"))
		return (1);
	return (0);
}

int	ft_wait(t_philo *philo, long wait_time)
{
	long	now;

	now = ft_current_time();
	while (ft_current_time() - now < wait_time)
	{
		usleep(200);
		if (ft_is_dead(philo) == 1)
			return (1);
	}
	return (0);
}
