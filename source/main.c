/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:17:45 by rojornod          #+#    #+#             */
/*   Updated: 2025/07/11 16:59:47 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor_thread(void *arg)
{
	t_philo		*philo;
	long long	now;
	int			i;
	int 		nbr_phils_done;

	philo = arg;
	nbr_phils_done = 0;
	while (philo->is_dead == 0)
	{
		nbr_phils_done = 0;
		i = 0;
		while (i < philo->phil_num)
		{
			pthread_mutex_lock(&philo[i].meal_time_mutex);
			now = ms_time();		
			if ((now - (philo[i].time_of_last_meal)) > philo->t_die)
			{
				philo[i].is_dead = 1;
				pthread_mutex_lock(philo->print);
				printf(WHITE "%lld %d died\n" WHITE, print_tmsp_ms(philo), philo[i].id);
				pthread_mutex_unlock(philo->print);
				exit(EXIT_FAILURE);
			}
			pthread_mutex_unlock(&philo[i].meal_time_mutex);
			if (philo[i].num_times_eat != -1)
			{
				pthread_mutex_lock(&philo->meal_status_mutex);
				if (philo[i].phil_status == 1)
					nbr_phils_done++;
				pthread_mutex_unlock(&philo->meal_status_mutex);
				if (nbr_phils_done == philo->phil_num){
					pthread_mutex_lock(philo->print);
					printf("exit success\n");
					pthread_mutex_unlock(philo->print);
					exit(EXIT_SUCCESS);}
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}


void	*main_routine(void *arg)
{
	t_philo	*philo;
	int		l_fork;

	philo = arg;
	
	while (philo->num_times_eat < 0 || philo->meals_eaten < philo->num_times_eat)
	{
		usleep(100);
		l_fork = philo->id;

		if (philo->id % 2 == 0)
		{		
			pthread_mutex_lock(&philo->forks[l_fork] );
			pthread_mutex_lock(philo->print);
			printf(BLUE "%lld %d has taken a fork\n" WHITE, print_tmsp_ms(philo), philo->id);
			pthread_mutex_unlock(philo->print);
		}
		else
		{
			pthread_mutex_lock(&philo->forks[(l_fork + 1) % philo->phil_num]);
			pthread_mutex_lock(philo->print);
			printf(BLUE "%lld %d has taken a fork\n" WHITE, print_tmsp_ms(philo), philo->id);
			pthread_mutex_unlock(philo->print);
		}
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&philo->forks[(l_fork + 1) % philo->phil_num] );
			pthread_mutex_lock(philo->print);
			printf(BLUE "%lld %d has taken a fork\n" WHITE, print_tmsp_ms(philo), philo->id);
			pthread_mutex_unlock(philo->print);
		}
		else
		{
			pthread_mutex_lock(&philo->forks[l_fork]);
			pthread_mutex_lock(philo->print);
			printf(BLUE "%lld %d has taken a fork\n" WHITE, print_tmsp_ms(philo), philo->id);
			pthread_mutex_unlock(philo->print);
		}
		
		pthread_mutex_lock(&philo->meals_eaten_mutex);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->meals_eaten_mutex);
		
		pthread_mutex_lock(philo->print);
		printf(GREEN "%lld %d is eating\n" WHITE, print_tmsp_ms(philo), philo->id);
		pthread_mutex_unlock(philo->print);

		pthread_mutex_lock(&philo->meal_time_mutex);
		philo->time_of_last_meal = ms_time();
		pthread_mutex_unlock(&philo->meal_time_mutex);
		
		usleep(philo->t_eat * 1000);

		// pthread_mutex_lock(philo->print);
		// printf("[%d ate %d meals]\n" WHITE, philo->id, philo->meals_eaten);
		// pthread_mutex_unlock(philo->print);
				
		if (philo->id % 2 == 0)
		{
			pthread_mutex_unlock(&philo->forks[l_fork] );
			pthread_mutex_unlock(&philo->forks[(l_fork + 1) % philo->phil_num]);
		}
		else
		{
			pthread_mutex_unlock(&philo->forks[(l_fork + 1) % philo->phil_num]);
			pthread_mutex_unlock(&philo->forks[l_fork] );
		}
		if (philo->meals_eaten == philo->num_times_eat)
		{
			pthread_mutex_lock(&philo->meal_status_mutex);
			philo->phil_status = 1;
			pthread_mutex_unlock(&philo->meal_status_mutex);
			return (NULL);
		}
		pthread_mutex_lock(philo->print);
		printf(YELLOW "%lld %d is sleeping\n" WHITE, print_tmsp_ms(philo), philo->id);
		pthread_mutex_unlock(philo->print);

		usleep(philo->t_sleep * 1000);

		pthread_mutex_lock(philo->print);
		printf(RED "%lld %d is thinking\n" WHITE, print_tmsp_ms(philo), philo->id);
		pthread_mutex_unlock(philo->print);

		usleep(100);
	}
	return (NULL);
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
	i = 0;
	while (i < philo->phil_num)
	{
		if (pthread_create(&philo->threads[i], NULL, &main_routine, &philo[i]) != 0)
			return (perror("error creating thread"), 1);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_thread, philo);
	i = 0;
	while (i < philo->phil_num)
	{
		if (pthread_join(philo->threads[i], NULL) != 0)
			return (perror("error joining threads"), 1);
		i++;
	}
	pthread_join(monitor, NULL);
	//destroy all the mutexes after joining
	pthread_mutex_destroy(philo->print);
	free(philo->threads);
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo		*philo;
	t_data		*data;

	philo = NULL;
	data = malloc(sizeof data);
	memset(data, 0, sizeof(*data));
	philo = input_validation(argc, argv);
	if (!philo)
		exit(EXIT_FAILURE);
	else
	{
		//pthread_mutex_init(&philo->print, NULL);
		data->start = ms_time();
		main_loop(philo);
		//pthread_mutex_destroy(&philo->print);
	}
	return (free(philo), 0);
}

static t_philo *allocate(t_philo *philo, int phil_n)
{
	philo = malloc(sizeof(t_philo) * phil_n);
	if (!philo)
		return (0);
	philo->data = malloc(sizeof(t_data));
	if (!philo->data)
		return (free(philo), NULL);
	philo->forks = malloc(sizeof (pthread_mutex_t) * phil_n);
	if (!philo->forks)
		return (free(philo->data), free(philo), NULL);
	return (philo);
} 

t_philo	*init_philo(char **argv, t_philo *philo, int argc)
{
	int				temp_phil_num;
	int				i;
	long long		start;
	
	i = 0;
	temp_phil_num = ft_atoi(argv[1]);
	philo = allocate(philo, temp_phil_num);
	if (!philo)
		exit(EXIT_FAILURE);
	pthread_mutex_init(philo->forks, NULL);
	philo->print = malloc(sizeof(*philo->print));
	if (!philo->print)
		return (NULL);
	pthread_mutex_init(philo->print, NULL);
	start =  ms_time();
	while (i < temp_phil_num)
	{
		philo[i].id = i;
		philo[i].phil_num = temp_phil_num;
		philo[i].t_die = ft_atoi(argv[2]);
		philo[i].t_eat = ft_atoi(argv[3]);
		philo[i].t_sleep = ft_atoi(argv[4]);
		philo[i].print = philo->print;
		philo[i].start = start;
		philo[i].is_dead = 0;
		philo[i].meals_eaten = 0;
		philo[i].time_of_last_meal = ms_time();
		philo[i].phil_status = 0;
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
