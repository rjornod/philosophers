/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:17:45 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/27 15:31:54 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void *monitor_thread(void *arg)
{
	t_philo *philo;

	philo = arg;
	if (philo->is_dead == 0)
	{
		printf("philospher is dead\n");
	}
	return (NULL);
}

static void *test_routine(void *arg)
{
	t_philo	*philo ;
	int		i;
	
	philo = arg;
	i = 0;
	pthread_mutex_lock(&philo->print);
	printf("*******************\n");
	printf("* starting thread *\n");
	print_tmsp_ms(philo);
	philo->inc++;
	usleep(3);
	printf("* ending thread   *\n");
	pthread_mutex_unlock(&philo->print);
	return (NULL);
}



int	main_loop(t_philo *philo)
{
	int			i;
	pthread_t 	*main_thread;

	main_thread = malloc(sizeof(*main_thread) * philo->phil_num);
	i = 0;
	while (i < philo->phil_num)
	{
		if (pthread_create(&main_thread[i], NULL, &test_routine, philo) != 0)
			return (perror("error creating thread"), 1);
		i++;
	}
	i = 0;
	while (i < philo->phil_num)
	{
		if (pthread_join(main_thread[i], NULL) != 0)
			return (perror("error joining threads"), 1);
		i++;
	}
	free(main_thread);
	return (1);
}

int main(int argc, char **argv)
{
	t_philo		*philo;
	// pthread_t 	t1;
	// pthread_t 	t2;
	//pthread_t 	monitor;

	philo = malloc(sizeof(*philo));
	if (!philo)
		return (0);
	memset(philo, 0, sizeof(*philo));
	if (input_validation(argc, argv, philo) != 0)
		exit(EXIT_FAILURE);
	else
	{
		pthread_mutex_init(&philo->print, NULL);
		philo->start = ms_time();
		// if (pthread_create(&monitor, NULL, &test_routine, NULL) != 0)
		// 	return (perror("error creating thread"), 1);
		// if (pthread_create(&monitor, NULL, &test_routine, NULL) != 0)
		// 	return (perror("error creating thread"), 1);
		// if (pthread_create(&t1, NULL, &test_routine, NULL) != 0)
		// 	return (perror("error creating thread"), 1);
		// if (pthread_create(&t2, NULL, &test_routine, NULL) != 0)
		// 	return (perror("error creating thread"), 1);

		// if (pthread_join(t1, NULL) != 0)
		// 	return (perror("error joining thread"), 1);
		// if (pthread_join(t2, NULL) != 0) 
		// 	return (perror("error joining thread"), 1);
		main_loop(philo);
		pthread_mutex_destroy(&philo->print);
		print_tmsp_ms(philo);
		printf("total threads are [%d]\n", philo->inc);
	}
	return (free(philo), 0);
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
