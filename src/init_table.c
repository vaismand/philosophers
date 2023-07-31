/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:39:26 by dvaisman          #+#    #+#             */
/*   Updated: 2023/07/31 14:29:59 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
}

void	ft_init_table(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
	{
		table->philos[i].id = i + 1;
		table->philos[i].eat_count = 0;
		table->philos[i].state = THINK;
		table->philos[i].last_eat = ft_get_time();
		table->philos[i].table = table;
		if (i == table->philo_count - 1)
			pthread_mutex_init(&table->philos[0].left, NULL);
		else
			pthread_mutex_init(&table->philos[i + 1].left, NULL);
		if (i == 0)
			table->philos[i].right = \
			&table->philos[table->philo_count - 1].left;
		else
			table->philos[i].right = &table->philos[i - 1].left;

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
		table->philos[i].last_eat = ft_get_time();
		if (pthread_create(&table->philos[i].thread, NULL, \
		ft_philo_act, &table->philos[i]) != 0)
			ft_error_msg("Error: thread creation failed\n", table);
		i++;
	}
	ft_check_death(table, table->philos);
	pthread_mutex_unlock(&table->write);
	ft_exit_threads(table);
}

void	ft_exit_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_destroy(&table->philos[i].left);
		i++;
	}
	pthread_mutex_destroy(&table->write);
	pthread_mutex_destroy(&table->stop);
	pthread_mutex_destroy(&table->eat);
	free(table->philos);
	free(table);
}
