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

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	int					left_fork;
	int					right_fork;
	int					must_eat_count;
	long long			last_eat;
	pthread_mutex_t		write_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		dead_mutex;
	pthread_t			thrd_no;
	t_data				*data;
}	t_philo;

typedef struct s_data
{
	int					eat_count;
	int					check_crate;
	int					nb_philo;
	int					check_die;
	int					must_eat;
	long long			time_to_die;
	long long			time_to_eat;
	long long			time_to_sleep;
	long long			first_time;
	pthread_mutex_t		*fork;
	t_philo				*philo;
}	t_data;

void					ft_full_free(t_data *data);
void					*ft_philo_handler(void *arg);
void					ft_finish_check(t_data *data);
void					ft_unlock_forks(t_data *data);
void					ft_init_philo_fork(t_data *data);
void					ft_start_simulation(t_data *data);
void					ft_error_0(char *str, t_data *data);
void					ft_error_1(char *str, t_data *data);
void					ft_arg_check(char **argv, t_data *data);
int						ft_isdigit(int c);
int						ft_eat(t_philo *philo);
int						ft_is_dead(t_philo *philo);
int						ft_sleep_think(t_philo *philo);
int						ft_is_eat_finish(t_philo *philo);
int						ft_wait(t_philo *philo, long sleep_time);
int						ft_write_message(t_philo *philo, char *str);
long					ft_atoi(const char *str);
long long				ft_current_time(void);
long long				ft_diff_time(t_philo *philo);
#endif
