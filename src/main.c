/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:39:19 by dvaisman          #+#    #+#             */
/*   Updated: 2023/07/17 12:39:19 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_start_threads(t_table *table)
{
	int	i;

	table->start_time = ft_get_time() + (table->philo_count * 2 * 10);
	i = 0;
	while (i < table->philo_count)
	{
		table->philos[i].last_eat = ft_get_time();
		if (pthread_create(&table->philos[i].thread, NULL, \
		ft_philo_act, &table->philos[i]) != 0)
			ft_error_msg("Error: thread creation failed\n", table);
		i++;
	}
	if (table->philo_count > 1)
	{
		if (pthread_create(&table->stop_thread, NULL, \
		ft_monitor_stop, table) != 0)
			ft_error_msg("Error: thread creation failed\n", table);
	}
	return (0);
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
	if (table->philo_count > 1)
		pthread_join(table->stop_thread, NULL);
	i = 0;
	while (i < table->philo_count)
	{
		pthread_mutex_destroy(&table->forks_mutex[i]);
		i++;
	}
	pthread_mutex_destroy(&table->write);
	pthread_mutex_destroy(&table->stop);
	pthread_mutex_destroy(&table->eat);
	free(table->philos);
	free(table);
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc == 5 || argc == 6)
	{
		table = malloc(sizeof(t_table));
		if (!table)
			ft_error_msg("Error: malloc failed\n", NULL);
		ft_init_vars(argc, argv, table);
		ft_init_table(table);
		ft_start_threads(table);
		ft_exit_threads(table);
	}
	else
		ft_error_msg("Error: wrong number of arguments\n", NULL);
	return (0);
}
