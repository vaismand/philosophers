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
	if (pthread_mutex_init(&table->write, NULL) != 0)
		ft_error_msg("Error: mutex init failed\n", table);
	
}

void	ft_init_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].id = i + 1;
		table->philos[i].eat_count = 0;
		table->philos[i].state = THINK;
		table->philos[i].last_eat = ft_get_time();
		table->philos[i].table = table;
		if (pthread_mutex_init(&table->philos[i + 1].left, NULL) != 0)
			ft_error_msg("Error: mutex init failed\n", table);
		if (i == 0)
			table->philos[i].right = &table->philos[table->philo_count - 1].left;
		else
			table->philos[i].right = &table->philos[i - 1].left;
		i++;
	}
	if (pthread_mutex_init(&table->stop, NULL) != 0)
		ft_error_msg("Error: mutex init failed\n", table);
	if (pthread_mutex_init(&table->eat, NULL) != 0)
		ft_error_msg("Error: mutex init failed\n", table);
}

void	ft_start_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_create(&table->philos[i].thread, NULL, ft_philo_act,
			&table->philos[i]);
		i++;
	}
	ft_check_death(table->philos);
	ft_exit(table);
}
