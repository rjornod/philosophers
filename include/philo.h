/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:17:42 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/27 15:26:44 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>


typedef struct s_philo
{
	int				phil_num;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_time_eat;
	int				is_dead;
	int 			inc;
	long long		start;
	
	pthread_mutex_t	print;
	pthread_mutex_t r_fork;
	pthread_mutex_t l_fork;
}	t_philo;

//initializing
int			input_validation(int argc, char **argv, t_philo *philo);
int			init_philo(char **argv, t_philo *philo, int argc);
int			ft_atoi(const char *str);

//time of day
long long	ms_time(void);
void		print_tmsp_ms(t_philo *philo);

//threads
void		 *monitor_thread(void *arg);