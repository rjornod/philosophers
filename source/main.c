/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:17:45 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/23 18:16:59 by rojornod         ###   ########.fr       */
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
	if (input_validation(argc, argv, philo) != 0)
		exit(EXIT_FAILURE);
	else
		printf("time is %lld\n", ms_time());
		//loop goes here
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
long long	ms_time(void)
{
	struct timeval te;
	{
		gettimeofday(&te, NULL);
		return (te.tv_sec * 1000LL + te.tv_usec / 1000);
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
	printf("[%lld][number of philos] %d\n", ms_time(), philo->phil_num);
	printf("[time to die] %d\n", philo->t_die);
	printf("[time to eat] %d\n", philo->t_eat);
	printf("[time to sleep] %d\n", philo->t_sleep);
	printf("[number of times to eat] %d\n", philo->n_time_eat);
	return (1);
}
