/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:34:30 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/27 15:06:08 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_input(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0); 
			j++;
		}
		i++;
	}
	return (1);
}

static int check_positive_val(t_philo *philo)
{
	if  ((philo->phil_num <= 0) || (philo->t_die <= 0) || (philo->t_eat <= 0) 
		|| (philo->t_sleep <= 0))
		return (1);
	else
		return (0);
}

int	input_validation(int argc, char **argv, t_philo *philo)
{
	if (argc < 5 || argc > 6)
	{
		printf("\nUSAGE\n");
		printf("./philo [number_of_philosophers] [time_to_die] ");
		printf("[time_to_eat] [time_to_sleep]\n");
		printf("\nOPTIONAL:\n[number_of_times_each_philosopher_must_eat]\n\n");
		
	}
	else if (argc == 5 || argc == 6)
	{
		if (check_input(argv))
		{
			printf("values are valid\n");
			init_philo(argv, philo, argc);
			if (check_positive_val(philo) != 0)
				return (printf("INVALID INPUT\n"), 1);
			return (0);
		}
		else
			printf("INVALID INPUT\n");
	}
	return (1);
}
