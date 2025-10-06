/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:08:42 by daflynn           #+#    #+#             */
/*   Updated: 2025/10/06 20:40:41 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	for (int meal = 0; meal < 20; meal++)
	{
		printf("%ld %d is thinking\n", get_current_time() - philo->start_time, philo->id);
		usleep(200 * 1000);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(philo->left_fork);
		}
		printf("%ld %d is eating\n", get_current_time() - philo->start_time, philo->id);
		usleep(philo->time_to_eat * 1000);
		if (philo->id % 2 == 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		else
		{
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(philo->left_fork);
		}
		printf("%ld %d is sleeping\n", get_current_time() - philo->start_time, philo->id);
		usleep(philo->time_to_sleep * 1000);
		printf("%ld %d finished one cycle\n",get_current_time() - philo->start_time, philo->id);
	}
	return (NULL);
}

void	ft_init_conf(t_config *conf, int argc, char **argv)
{
	conf->num_philos = ft_atoi_positive(argv[1]);
	conf->time_to_die = ft_atoi_positive(argv[2]);
	conf->time_to_eat = ft_atoi_positive(argv[3]);
	conf->time_to_sleep = ft_atoi_positive(argv[4]);
	if (argc == 6)
		conf->times_must_eat = ft_atoi_positive(argv[5]);
	else
		conf->times_must_eat = -1;
	conf->philos = malloc(sizeof(t_philo) * conf->num_philos);
	conf->forks = malloc(sizeof(pthread_mutex_t) * conf->num_philos);
	conf->threads = malloc(sizeof(pthread_t) * conf->num_philos);
}

void	ft_init_philos(t_config *conf)
{
	int		i;
	long	start_time;

	i = 0;
	start_time = get_current_time();
	while (i < conf->num_philos)
	{
		conf->philos[i].id = i + 1;
		conf->philos[i].start_time = get_current_time();
		conf->philos[i].left_fork = &conf->forks[i];
		conf->philos[i].right_fork = &conf->forks[(i + 1) % conf->num_philos];
		conf->philos[i].time_to_eat = conf->time_to_eat;
		conf->philos[i].time_to_sleep = conf->time_to_sleep;
		i++;
	}
}

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	main(int argc, char **argv)
{
	t_config	conf;
	int			i;

	i = -1;
	if (argc < 5 || argc > 6)
		return (printf("WRONG: Invalid number of arguments entered"), 1);
	ft_init_conf(&conf, argc, argv);
	while (++i < conf.num_philos)
		pthread_mutex_init(&conf.forks[i], NULL);
	ft_init_philos(&conf);
	i = -1;
	while (++i < conf.num_philos)
		pthread_create(&conf.threads[i], NULL, philo_routine, &conf.philos[i]);
	i = -1;
	while (++i < conf.num_philos)
		pthread_join(conf.threads[i], NULL);
	i = -1;
	while (++i < conf.num_philos)
		pthread_mutex_destroy(&conf.forks[i]);
	free(conf.forks);
	free(conf.threads);
	free(conf.philos);
	return (0);
}
