/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:17:38 by rojornod          #+#    #+#             */
/*   Updated: 2025/07/04 16:12:44 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result * sign);
}

long long	time_since_last_meal(long long last_meal)
{
	long long	now;

	now = ms_time();
	return (now - last_meal);
}

//converts tv_sec and tv_usec to milisecond
//use this for time since last meal etc
long long	ms_time(void)
{
	struct timeval	te;

	gettimeofday(&te, NULL);
	return (te.tv_sec * 1000LL + te.tv_usec / 1000);
}

long long	print_tmsp_ms(t_philo *philo)
{
	long long	end;

	end = ms_time();
	return (end - philo->start);
}
