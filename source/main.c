/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:17:45 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/03 17:12:54 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int argc, char **argv)
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo));
	if (!philo)
		return (0);
	memset(philo, 0, sizeof(*philo));
	if (argc < 5 || argc > 6)
	{
		printf("\nUSAGE\n");
		printf("./philo [number_of_philosophers] [time_to_die] ");
		printf("[time_to_eat] [time_to_sleep]\n");
		printf("\nOPTIONAL:\n[number_of_times_each_philosopher_must_eat]\n\n");
		return (0);
	}
	else if (argc == 5 || argc == 6)
	{
		if (check_valid_input(argv))
		{
			printf("values are valid\n");
			init_philo(argv, philo, argc);
		}
		else
			return(printf("INVALID INPUT\n"));
	}
	while (1)
	{
		printf("%1.0f\n", ms_time());
	}

}

int	check_valid_input(char **argv)
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

//converts tv_sec and tv_usec to milisecond
double	ms_time(void)
{
	struct timeval tv;
	{
		gettimeofday(&tv, NULL);
		return (((double)tv.tv_sec) * 1000) + (double)(tv.tv_usec / 1000);
	};
}

int	init_philo(char **argv, t_philo *philo, int argc)
{
	philo->phil_num = ft_atoi(argv[1]);
	philo->t_die = ft_atoi(argv[2]);
	philo->t_eat = ft_atoi(argv[3]);
	philo->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->n_time_eat = ft_atoi(argv[5]);
	printf("[%3f][number of philos] %d\n", ms_time(), philo->phil_num);
	printf("[time to die] %d\n", philo->t_die);
	printf("[time to eat] %d\n", philo->t_eat);
	printf("[time to sleep] %d\n", philo->t_sleep);
	printf("[number of times to eat] %d\n", philo->n_time_eat);
	return (1);
}
