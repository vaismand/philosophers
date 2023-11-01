/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:39:26 by dvaisman          #+#    #+#             */
/*   Updated: 2023/10/31 20:30:31 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*ft_init_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!forks)
		ft_error_msg("Error: malloc failed\n", table);
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
			ft_error_msg("Error: mutex init failed\n", table);
		i++;
	}
	return (forks);
}

static void	ft_get_forks(t_philo *philo)
{
	philo->forks[0] = philo->id;
	philo->forks[1] = (philo->id + 1) % philo->table->philo_count;
	if (philo->id % 2)
	{
		philo->forks[0] = (philo->id + 1) % philo->table->philo_count;
		philo->forks[1] = philo->id;
	}
}

void	ft_init_vars(int argc, char **argv, t_table *table)
{
	if (ft_check_args(argc, argv))
	{
		free(table);
		ft_error_msg("Error: wrong arguments\n", NULL);
	}
	table->philo_count = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	table->all_ate_count = 0;
	table->stop_cond = 0;
	if (argc == 6)
		table->must_eat_count = ft_atoi(argv[5]);
	else
		table->must_eat_count = -1;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_count);
	if (!table->philos)
		ft_error_msg("Error: malloc failed\n", table);
	table->start_time = ft_get_time();
	if (pthread_mutex_init(&table->write, NULL) != 0)
		ft_error_msg("Error: mutex init failed\n", table);
	table->forks_mutex = ft_init_forks(table);
	if (!table->forks_mutex)
		ft_error_msg("Error: malloc failed\n", table);
}

void	ft_init_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].id = i;
		table->philos[i].eat_count = 0;
		table->philos[i].state = THINK;
		table->philos[i].last_eat = ft_get_time();
		table->philos[i].table = table;
		ft_get_forks(&table->philos[i]);
		i++;
	}
	if (pthread_mutex_init(&table->stop, NULL) != 0)
		ft_error_msg("Error: mutex init failed\n", table);
	if (pthread_mutex_init(&table->eat, NULL) != 0)
		ft_error_msg("Error: mutex init failed\n", table);
}
