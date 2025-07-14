/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:34:30 by rojornod          #+#    #+#             */
/*   Updated: 2025/07/14 12:23:53 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_positive_val(char **argv, int argc)
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_philosophers;
	int	number_times_to_eat;

	number_of_philosophers = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		number_times_to_eat = ft_atoi(argv[5]);
		if (number_times_to_eat <= 0)
			return (0);
	}
	if ((number_of_philosophers <= 0) || (time_to_die <= 0)
		|| (time_to_eat <= 0)
		|| (time_to_sleep <= 0))
		return (0);
	else
		return (1);
}

static int	check_input(char **argv, int argc)
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
	if (check_positive_val(argv, argc) != 1)
		return (0);
	return (1);
}

t_philo	*input_validation(int argc, char **argv)
{
	t_philo	*philo;

	philo = NULL;
	if (argc < 5 || argc > 6)
	{
		printf("\nUSAGE\n");
		printf("./philo [number_of_philosophers] [time_to_die] ");
		printf("[time_to_eat] [time_to_sleep]\n");
		printf("\nOPTIONAL:\n[number_of_times_each_philosopher_must_eat]\n\n");
	}
	else if (argc == 5 || argc == 6)
	{
		if (check_input(argv, argc))
		{
			printf("values are valid\n");
			philo = init_philo(argv, philo, argc);
			return (philo);
		}
		else
			printf("invalid input, try again\n");
	}
	return (NULL);
}
