#include "philo.h"

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
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		ft_error_msg("Error: malloc failed\n", table);
	table->start_time = ft_get_time();
	table->dead = 0;
	pthread_mutex_init(&table->write, NULL);
}

void	ft_init_table(t_table *table)
{
	int	i;

	i = 0;
	while (i++ < table->philo_count)
	{
		table->philos[i].id = i + 1;
		table->philos[i].eat_count = 0;
		table->philos[i].state = THINK;
		table->philos[i].last_eat = ft_get_time();
		table->philos[i].table = table;
	}
	pthread_mutex_init(&table->stop, NULL);
	pthread_mutex_init(&table->eat, NULL);
	pthread_mutex_lock(&table->eat);
}
