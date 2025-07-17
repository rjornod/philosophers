/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:17:45 by rojornod          #+#    #+#             */
/*   Updated: 2025/07/17 17:02:39 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor_thread(void *arg)
{
	t_philo		*philo;
	long long	now;
	int			i;
	int 		nbr_phils_done;
	int			num;

	philo = arg;
	num = philo->phil_num;
	pthread_mutex_lock(&philo->data->dead_mutex);
	philo->data->dead = 0;
	pthread_mutex_unlock(&philo->data->dead_mutex);
	while (1)
	{
		nbr_phils_done = 0;
		i = 0;
		while (i < num)
		{
			pthread_mutex_lock(&philo[i].meal_time_mutex);
			now = ms_time();		
			if ((now - (philo[i].time_of_last_meal)) > philo->t_die && philo[i].phil_status != 1)
			{
				pthread_mutex_lock(&philo->data->dead_mutex);
				philo->data->dead = 1;
				pthread_mutex_unlock(&philo->data->dead_mutex);
				
				pthread_mutex_lock(philo->print);
				printf(WHITE "%lld %d died\n" WHITE, print_tmsp_ms(philo), philo[i].id);
				pthread_mutex_unlock(philo->print);
				
				return (printf("returning dead monitor\n"),NULL);
			}
			pthread_mutex_unlock(&philo[i].meal_time_mutex);
			if (philo[i].num_times_eat != -1)
			{					
				pthread_mutex_lock(&philo[i].meal_status_mutex);
				
				if (philo[i].phil_status == 1)
				{
					pthread_mutex_lock(philo->print);
					nbr_phils_done++;
					pthread_mutex_unlock(philo->print);
				}
				pthread_mutex_unlock(&philo[i].meal_status_mutex);
				if (nbr_phils_done == num)
				{
					// pthread_mutex_lock(&philo->data->dead_mutex);
					// philo->data->dead = 1;
					// pthread_mutex_unlock(&philo->data->dead_mutex);
					pthread_mutex_lock(philo->print);
					printf("%lld exit success\n", print_tmsp_ms(philo));
					pthread_mutex_unlock(philo->print);
					return (NULL);
				}
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

static bool philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	printf("[%d] checking\n", philo->data->dead);
	if (philo->data->dead == 1)
	{
		printf("returning philo_dead\n");
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return (false);
}

// static bool	is_philo_done(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->meal_status_mutex);
// 	if (philo->meals_eaten == philo->num_times_eat)
// 	{
// 		philo->phil_status = 1;
// 		pthread_mutex_unlock(&philo->meal_status_mutex);
		
// 		return (true);
// 	}
// 	pthread_mutex_unlock(&philo->meal_status_mutex);
// 	return (false);
// }

void	*main_routine(void *arg)
{
	t_philo	*philo;
	int		l_fork;

	philo = arg;
	
	if (philo->id % 2 != 0)
		usleep(philo->t_die * 1000 / 2);
		
	while (philo->num_times_eat < 0 || philo->meals_eaten < philo->num_times_eat)
	{
		if (philo->meals_eaten == philo->num_times_eat)
		{
			pthread_mutex_lock(&philo->meal_status_mutex);
			philo->phil_status = 1;
			
			pthread_mutex_unlock(&philo->meal_status_mutex);
			return (printf("philo is done\n"), NULL);
		}
		
		
		if (philo_dead(philo))
			return (printf("returning2\n"), NULL);
			
		l_fork = philo->id;

		if (philo->id % 2 == 0)
		{
			
			
			pthread_mutex_lock(&philo->forks[l_fork] );
			if (philo_dead(philo))
			{
				pthread_mutex_unlock(&philo->forks[l_fork] );
				return (printf("returning dead main 4\n"),NULL);
			}
			pthread_mutex_lock(philo->print);
			printf(BLUE "%lld %d has taken a fork\n" WHITE, print_tmsp_ms(philo), philo->id);
			pthread_mutex_unlock(philo->print);
			
			if (philo_dead(philo))
			{
				pthread_mutex_unlock(&philo->forks[l_fork] );
				return (printf("returning dead main 4\n"),NULL);
			}
			
			pthread_mutex_lock(&philo->forks[(l_fork + 1) % philo->phil_num] );
			if (philo_dead(philo))
			{
				pthread_mutex_unlock(&philo->forks[(l_fork + 1) % philo->phil_num]);
				return (printf("returning dead main taken one fork 3\n"),NULL);
			}
			
			pthread_mutex_lock(philo->print);
			printf(BLUE "%lld %d has taken a fork\n" WHITE, print_tmsp_ms(philo), philo->id);
			pthread_mutex_unlock(philo->print);
			
			if (philo_dead(philo))
			{
				pthread_mutex_unlock(&philo->forks[l_fork]);
				pthread_mutex_unlock(&philo->forks[(l_fork + 1) % philo->phil_num]);
				exit(EXIT_FAILURE);
				return (printf("returning dead main taken one fork 3\n"),NULL);
			}
		}
		else
		{
			pthread_mutex_lock(&philo->forks[(l_fork + 1) % philo->phil_num]);
			if (philo_dead(philo))
			{
				pthread_mutex_unlock(&philo->forks[(l_fork + 1) % philo->phil_num]);
				return (printf("returning dead main taken one fork 3\n"),NULL);
			}

			pthread_mutex_lock(philo->print);
			printf(BLUE "%lld %d has taken a fork\n" WHITE, print_tmsp_ms(philo), philo->id);
			if (philo_dead(philo))
			{
				pthread_mutex_unlock(&philo->forks[(l_fork + 1) % philo->phil_num]);
				return (printf("returning dead main taken one fork 3\n"),NULL);
			}
			pthread_mutex_unlock(philo->print);
			
			pthread_mutex_lock(&philo->forks[l_fork]);
			if (philo_dead(philo))
			{
				pthread_mutex_unlock(&philo->forks[(l_fork + 1) % philo->phil_num]);
				pthread_mutex_unlock(&philo->forks[l_fork] );
				return (printf("returning dead main 4\n"),NULL);
			}
			pthread_mutex_lock(philo->print);
			printf(BLUE "%lld %d has taken a fork\n" WHITE, print_tmsp_ms(philo), philo->id);
			if (philo_dead(philo))
			{
				pthread_mutex_unlock(&philo->forks[(l_fork + 1) % philo->phil_num]);
				pthread_mutex_unlock(&philo->forks[l_fork] );
				return (printf("returning dead main 4\n"),NULL);
			}
			pthread_mutex_unlock(philo->print);
		}
		
		pthread_mutex_lock(&philo->meals_eaten_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meals_eaten_mutex);
		if (philo_dead(philo))
				return (printf("returning dead main 6\n"),NULL);
				
		pthread_mutex_lock(philo->print);
		if (philo_dead(philo))
				return (printf("returning dead main 6\n"),NULL);

		printf(GREEN "%lld %d is eating\n" WHITE, print_tmsp_ms(philo), philo->id);
		pthread_mutex_unlock(philo->print);

		pthread_mutex_lock(&philo->meal_time_mutex);
		philo->time_of_last_meal = ms_time();
		pthread_mutex_unlock(&philo->meal_time_mutex);
		
		usleep(philo->t_eat * 1000);
		
		if (philo->id % 2 == 0)
		{
			if (philo_dead(philo))
				return (printf("returning dead main 6\n"),NULL);
			pthread_mutex_unlock(&philo->forks[l_fork] );
			if (philo_dead(philo))
				return (printf("returning dead main 6\n"),NULL);
			pthread_mutex_unlock(&philo->forks[(l_fork + 1) % philo->phil_num]);
			if (philo_dead(philo))
				return (printf("returning dead main 7\n"),NULL);
		}
		else
		{
			if (philo_dead(philo))
				return (printf("returning dead main 6\n"),NULL);
			pthread_mutex_unlock(&philo->forks[(l_fork + 1) % philo->phil_num]);
			if (philo_dead(philo))
				return (printf("returning dead main 6\n"),NULL);
			pthread_mutex_unlock(&philo->forks[l_fork] );
			if (philo_dead(philo))
				return (printf("returning dead main 8\n"),NULL);
		}

		
		if (philo_dead(philo))
				return (printf("returning dead main 1\n"),NULL);
		pthread_mutex_lock(philo->print);
		printf(YELLOW "%lld %d is sleeping\n" WHITE, print_tmsp_ms(philo), philo->id);
		pthread_mutex_unlock(philo->print);

		usleep(philo->t_sleep * 1000);

		if (philo_dead(philo))
				return (printf("returning dead main 1\n"),NULL);
		pthread_mutex_lock(philo->print);
		printf(RED "%lld %d is thinking\n" WHITE, print_tmsp_ms(philo), philo->id);
		pthread_mutex_unlock(philo->print);

		if (philo_dead(philo))
				return (printf("returning dead main 6\n"),NULL);
				
		if (philo->meals_eaten == philo->num_times_eat)
		{
			pthread_mutex_lock(&philo->meal_status_mutex);
			philo->phil_status = 1;
			pthread_mutex_unlock(&philo->meal_status_mutex);
			return ( NULL);
		}
		//p(100);
	}
	return (printf("returning3\n"), NULL);
}

int	main_loop(t_philo *philo)
{
	int	i;
	pthread_t monitor;

	philo->threads = malloc(sizeof(*philo->threads) * philo->phil_num);
	if (!philo->threads)
		return (0);
	i = 0;
	
	while (i < philo->phil_num)
	{
		pthread_mutex_init(&philo[i].meal_time_mutex, NULL);
		philo[i].forks = philo->forks;
		pthread_mutex_init(&philo->forks[i], NULL);
		
		i++;
	}
	init_start_time(philo);
	i = 0;
	while (i < philo->phil_num)
	{
		if (pthread_create(&philo->threads[i], NULL, &main_routine, &philo[i]) != 0)
			return (perror("error creating thread"), 1);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_thread, philo);
	if (!pthread_join(monitor, NULL))
		printf("successfully joined monitor\n");
	i = 0;
	int num;
	num = philo->phil_num;
	printf("joining threads\n");
	while (i < num)
	{
		if (pthread_join(philo->threads[i], NULL) != 0)
			return (perror("error joining threads"), 0);
		printf("joined thread\n");
		i++;
	}
	//destroy all the mutexes after joining
	printf("cleaning\n");
	cleanup(philo);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	//t_data		*data;

	philo = NULL;
	
	philo = input_validation(argc, argv);
	if (!philo)
		exit(EXIT_FAILURE);
	else
	{
		philo->data = malloc(sizeof *philo->data);
		memset(philo->data, 0, sizeof(*philo->data));
		
		philo->data->start = ms_time();
		if (main_loop(philo) == 1)
			exit(EXIT_SUCCESS);
		//pthread_mutex_destroy(&philo->print);
		//free(philo->data);
	}
	return (0);
}




