/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:58:40 by rojornod          #+#    #+#             */
/*   Updated: 2025/07/17 11:51:01 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static t_philo *allocate(t_philo *philo, int phil_n)
{
	philo = malloc(sizeof(t_philo) * phil_n);
	if (!philo)
		return (0);
	philo->data = malloc(sizeof(*philo->data));
	if (!philo->data)
		return (free(philo), NULL);
	philo->forks = malloc(sizeof (pthread_mutex_t) * phil_n);
	if (!philo->forks)
		return (free(philo->data), free(philo), NULL);
	philo->print = malloc(sizeof(*philo->print));
	if (!philo->print)
		return (free(philo->data), free(philo->forks), free(philo), NULL);
	return (philo);
} 

t_philo	*init_philo(char **argv, t_philo *philo, int argc)
{
	int				temp_phil_num;
	int				i;
	//long long		start;
	
	i = 0;
	temp_phil_num = ft_atoi(argv[1]);
	philo = allocate(philo, temp_phil_num);
	if (!philo)
		exit(EXIT_FAILURE);
	pthread_mutex_init(philo->forks, NULL);
	pthread_mutex_init(philo->print, NULL);
	pthread_mutex_init(&philo->data->dead_mutex, NULL);
	// start =  ms_time();
	while (i < temp_phil_num)
	{
		philo[i].id = i;
		philo[i].phil_num = temp_phil_num;
		philo[i].t_die = ft_atoi(argv[2]);
		philo[i].t_eat = ft_atoi(argv[3]);
		philo[i].t_sleep = ft_atoi(argv[4]);
		philo[i].print = philo->print;
		//philo[i].start = start;
		philo[i].is_dead = 0;
		philo[i].meals_eaten = 0;
		philo[i].time_of_last_meal = ms_time();
		philo[i].phil_status = 0;
		philo[i].data = philo->data;
		if (argc == 6)
			philo[i].num_times_eat = ft_atoi(argv[5]);
		else
			philo[i].num_times_eat = -1;
		pthread_mutex_init(&philo[i].meals_eaten_mutex, NULL);
		pthread_mutex_init(&philo[i].meal_status_mutex, NULL);
		i++;
	}
	printf("[is dead] %d\n", philo->is_dead);
	printf("[number of philos] %d\n", philo->phil_num);
	printf("[time to die] %d\n", philo->t_die);
	printf("[time to eat] %d\n", philo->t_eat);
	printf("[time to sleep] %d\n", philo->t_sleep);
	printf("[number of times to eat] %d\n", philo->num_times_eat);
	return (philo);
}

void	init_start_time(t_philo *philo)
{
	int			i;
	long long	start;

	i = 0;
	start =  ms_time();
	while (i < philo->phil_num)
	{
		philo[i].start = start;
		i++;
	}
}

