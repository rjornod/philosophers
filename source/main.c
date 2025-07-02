/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:17:45 by rojornod          #+#    #+#             */
/*   Updated: 2025/07/02 15:53:06 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor_thread(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->is_dead == 0)
	{
		printf("philospher is dead\n");
	}
	return (NULL);
}

// static void	*test_routine(void *arg)
// {
// 	t_philo	*philo ;
// 	int		i;

// 	philo = arg;
// 	i = 0;
// 	pthread_mutex_lock(philo->print);
// 	printf("*******************\n");
// 	printf("* starting thread *\n");
// 	//print_tmsp_ms(philo);
// 	printf("[id] %d\n", philo->id);
// 	philo->inc++;
// 	usleep(3);
// 	printf("* ending thread   *\n");
// 	pthread_mutex_unlock(philo->print);
// 	return (NULL);
// }

void	*main_routine(void *arg)
{
	t_philo	*philo;
	int		l_fork;

	philo = arg;
	while (philo->is_dead == 0)
	{
		l_fork = philo->id;
		pthread_mutex_lock(&philo->forks[l_fork]);
		pthread_mutex_lock(philo->print);
		printf("[%lld] %d has taken left fork\n", print_tmsp_ms(philo), philo->id);
		pthread_mutex_unlock(philo->print);
		pthread_mutex_lock(&philo->forks[(l_fork + 1) % philo->phil_num]);
		pthread_mutex_lock(philo->print);
		printf("[%lld] %d has taken right fork\n", print_tmsp_ms(philo), philo->id);
		pthread_mutex_unlock(philo->print);
		usleep(philo->t_eat * 1000);
		pthread_mutex_lock(philo->print);
		printf("[%lld] %d is eating\n", print_tmsp_ms(philo), philo->id);
		pthread_mutex_unlock(philo->print);
		pthread_mutex_unlock(&philo->forks[l_fork]);
		pthread_mutex_unlock(&philo->forks[(l_fork + 1) % philo->phil_num]);
	}
	// pthread_mutex_lock(philo->print);
	// printf("*******************\n");
	// printf("* starting thread *\n");
	// print_tmsp_ms(philo);
	// philo->inc++;
	// usleep(3);
	// printf("* ending thread   *\n");
	// pthread_mutex_unlock(&philo->print);
	return (NULL);
}

int	main_loop(t_philo *philo)
{
	int	i;

	philo->threads = malloc(sizeof(*philo->threads) * philo->phil_num);
	if (!philo->threads)
		return (0);
	i = 0;
	while (i < philo->phil_num)
	{
		philo[i].forks = philo->forks;
		pthread_mutex_init(&philo->forks[i], NULL);
		if (pthread_create(&philo->threads[i], NULL, &main_routine, &philo[i]) != 0)
			return (perror("error creating thread"), 1);
		i++;
	}
	i = 0;
	while (i < philo->phil_num)
	{
		if (pthread_join(philo->threads[i], NULL) != 0)
			return (perror("error joining threads"), 1);
		i++;
	}
	pthread_mutex_destroy(philo->print);
	free(philo->threads);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;

	philo = NULL;
	philo = input_validation(argc, argv);
	if (!philo)
		exit(EXIT_FAILURE);
	else
	{
		//pthread_mutex_init(&philo->print, NULL);
		philo->start = ms_time();
		main_loop(philo);
		//pthread_mutex_destroy(&philo->print);
	}
	return (free(philo), 0);
}

t_philo	*init_philo(char **argv, t_philo *philo, int argc)
{
	int				temp_phil_num;
	int				i;
	
	i = 0;
	temp_phil_num = ft_atoi(argv[1]);
	philo = malloc(sizeof(t_philo) * temp_phil_num);
	if (!philo)
		return (0);
	philo->forks = malloc(sizeof (pthread_mutex_t) * temp_phil_num);
	if (!philo->forks)
		return (NULL);
	pthread_mutex_init(philo->forks, NULL);
	philo->print = malloc(sizeof(*philo->print));
	if (!philo->print)
		return (NULL);
	pthread_mutex_init(philo->print, NULL);
	while (i < temp_phil_num)
	{
		philo[i].id = i;
		philo[i].phil_num = temp_phil_num;
		philo[i].t_die = ft_atoi(argv[2]);
		philo[i].t_eat = ft_atoi(argv[3]);
		philo[i].t_sleep = ft_atoi(argv[4]);
		philo[i].print = philo->print;
		philo[i].start = philo->start;
		if (argc == 6)
			philo[i].n_time_eat = ft_atoi(argv[5]);
		i++;
	}
	printf("[number of philos] %d\n", philo->phil_num);
	printf("[time to die] %d\n", philo->t_die);
	printf("[time to eat] %d\n", philo->t_eat);
	printf("[time to sleep] %d\n", philo->t_sleep);
	printf("[number of times to eat] %d\n", philo->n_time_eat);
	return (philo);
}
