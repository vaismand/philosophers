#include "philosophers.h"

void	ft_init_vars(int argc, char **argv, t_table *table)
{
	table->philo_count = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->must_eat_count = ft_atoi(argv[5]);
	else
		table->must_eat_count = -1;
	table->forks = NULL;
	table->philos = NULL;
	table->start = 0;
	table->dead = 0;
}

void	ft_init_table(t_table *table)
{
	int	i;

	table->forks = malloc(sizeof(int) * table->philo_count);
	if (!table->forks)
		ft_error_msg("Error: malloc failed\n", table);
	i = 0;
	while (i < table->philo_count)
		table->forks[i++] = FORK;
	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		ft_error_msg("Error: malloc failed\n", table);
	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].id = i + 1;
		table->philos[i].state = THINK;
		table->philos[i].eat_count = 0;
		table->philos[i].last_eat = 0;
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = (i + 1) % table->philo_count;
		table->philos[i].table = table;
		i++;
	}
}

