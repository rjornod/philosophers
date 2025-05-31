#include "../include/philo.h"

int main(int argc, char **argv)
{
	t_philo	*philo;

	philo = malloc(sizeof(*philo));
	if (!philo)
		return (0);
	memset(philo, 0, sizeof(*philo));
	if (argc < 5 || argc > 6)
	{
		printf("\nUSAGE\n");
		printf("./philo [number_of_philosophers] [time_to_die] ");
		printf("[time_to_eat] [time_to_sleep]\n");
		printf("\nOPTIONAL:\n[number_of_times_each_philosopher_must_eat]\n\n");
		return (0);
	}
	else if (argc == 5 || argc == 6)
	{
		if (check_valid_input(argv))
		{
			printf("values are valid\n");
			init_philo(argv, philo, argc);
		}
		else
			return(printf("INVALID INPUT\n"));
	}

}

int	check_valid_input(char **argv)
{
	int	i;
	int	j;

	
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0); 
			j++;
		}
		i++;
	}
	return (1);
}

int	init_philo(char **argv, t_philo *philo, int argc)
{
	philo->phil_num = ft_atoi(argv[1]);
	philo->t_die = ft_atoi(argv[2]);
	philo->t_eat = ft_atoi(argv[3]);
	philo->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->n_time_eat = ft_atoi(argv[5]);
	printf("[number of philos] %d\n", philo->phil_num);
	printf("[time to die] %d\n", philo->t_die);
	printf("[time to eat] %d\n", philo->t_eat);
	printf("[time to sleep] %d\n", philo->t_sleep);
	printf("[number of times to eat] %d\n", philo->n_time_eat);
	return (1);
}
