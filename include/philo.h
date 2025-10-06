#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	long				start_time;
}					t_philo;

typedef struct s_config
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	t_philo			*philos;
}					t_config;

int					ft_atoi_positive(char *str);
void	ft_init_conf(t_config *conf, int argc, char **argv);
long    get_current_time(void);

#endif
