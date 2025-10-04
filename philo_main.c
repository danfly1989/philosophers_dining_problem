/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 09:41:53 by daflynn           #+#    #+#             */
/*   Updated: 2025/10/04 12:28:01 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// Parse string to positive integer
// returns -1 on error (invalid input, negative, or overflow_
int	ft_atoi_positive(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	// skip whitespace
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	// check for sign. No negatives allowed
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	// check if there is at least one digit
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	// convert to integer
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		// check for overflow (int MAX is 2147483647)
		if (result > 2147483647)
			return (-1);
		i++;
	}
	// check for trailing garbage
	if (str[i] != '\0')
		return (-1);
	return (result);
}

int	main(int argc, char **argv)
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_times_eat;

	// check argument count
	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments\n");
		printf("Usage: ./philo number of philos, time to die, time to eat");
		return (1);
	}
	// parse and validate arguments
	num_philos = ft_atoi_positive(argv[1]);
	time_to_die = ft_atoi_positive(argv[2]);
	time_to_eat = ft_atoi_positive(argv[3]);
	time_to_sleep = ft_atoi_positive(argv[4]);
	if (argc == 6)
		num_times_eat = ft_atoi_positive(argv[5]);
	else
		num_times_eat = -1; //-1 means unlimited
	// validate all arguments are positive
	if (num_philos <= 0 || time_to_die <= 0 || time_to_eat <= 0
		|| time_to_sleep <= 0)
	{
		printf("Error: All arguments must be positive integers\n");
		return (-1);
	}
	// validate optional argument if provided
	if (argc == 6 && num_times_eat <= 0)
	{
		printf("Error: All arguments must be positive integers\n");
		return (1);
	}
	// print parsed values
	printf("Number of philosophers: %d\n", num_philos);
	printf("Time to die: %d ms\n", time_to_die);
	printf("Time to eat: %d ms\n", time_to_eat);
	printf("Time to sleep: %d ms\n", time_to_sleep);
	if (num_times_eat != -1)
		printf("Number of times each must eat: %d\n", num_times_eat);
	else
		printf("Number of times each must eat: unlimited\n");
	return (0);
}
