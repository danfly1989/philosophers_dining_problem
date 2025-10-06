/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_positive.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daflynn <daflynn@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:50:51 by daflynn           #+#    #+#             */
/*   Updated: 2025/10/06 11:18:41 by daflynn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_positive(char *str)
{
	int result;
	int i;

	result = 0;
	i = 0;
	if(str[0] == '-')
		return -1;
	while(str[i] == '+' || str[i] == ' ' || str[i] == '\t')
		i++;
	while(str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i]-'0'); 
		i++;
	}

	if (result <= 0 || str[i] != '\0')
		return -1;
	else
		return result;
}
