/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:34:30 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/23 18:02:27 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/// @brief 
/// @param argc the argument count
/// @param argv the argument vector
/// @param philo struct containing philo data
/// @return 
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
		if (check_valid_input(argv))
		{
			printf("values are valid\n");
			init_philo(argv, philo, argc);
			return (0);
		}
		else
			printf("INVALID INPUT\n");
	}
	return (1);
}
