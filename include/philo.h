/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:17:42 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/24 17:38:52 by rojornod         ###   ########.fr       */
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
	int	phil_num;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_time_eat;
}	t_philo;

//initializing
int	input_validation(int argc, char **argv, t_philo *philo);
int	check_valid_input(char **argv);
int	init_philo(char **argv, t_philo *philo, int argc);
int	ft_atoi(const char *str);

//time of day
long long	ms_time(void);

