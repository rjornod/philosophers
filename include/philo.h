/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:17:42 by rojornod          #+#    #+#             */
/*   Updated: 2025/07/03 14:53:06 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				dead;
	long long		start;
} 	t_data;

typedef struct s_philo
{
	int				id;
	int				phil_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_time_eat;
	int				is_dead;
	int				inc;
	long long		start;
	int				phil_status;
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

//threads
void				*monitor_thread(void *arg);

int					main_loop(t_philo *philo);
#endif