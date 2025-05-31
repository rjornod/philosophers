#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct s_philo
{
	int	phil_num;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	n_time_eat;
}	t_philo;

//initializing
int	check_valid_input(char **argv);
int	init_philo(char **argv, t_philo *philo, int argc);
int	ft_atoi(const char *str);
