/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:17:42 by rojornod          #+#    #+#             */
/*   Updated: 2025/07/04 16:14:23 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# define RED "\e[91m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define WHITE "\x1b[0m"

typedef struct s_data
{
	int				dead;
	long long		start;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				phil_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_times_eat;
	int				is_dead;
	long long		start;
	int				phil_status;
	int				time_of_last_meal;
	int				meals_eaten;
	pthread_mutex_t	meals_eaten_mutex;
	pthread_t		*threads;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	t_data			*data;
}	t_philo;

//initializing
t_philo				*input_validation(int argc, char **argv);
t_philo				*init_philo(char **argv, t_philo *philo, int argc);
int					ft_atoi(const char *str);

//time of day
long long			ms_time(void);
long long			print_tmsp_ms(t_philo *philo);
long long			time_since_last_meal(long long last_meal);

//threads
void				*monitor_thread(void *arg);

int					main_loop(t_philo *philo);
#endif