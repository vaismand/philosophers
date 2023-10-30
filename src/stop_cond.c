/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_cond.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:04:19 by dvaisman          #+#    #+#             */
/*   Updated: 2023/10/23 13:09:16 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_set_stop_flag(t_table *table, int state)
{
	pthread_mutex_lock(&table->stop);
	table->stop_cond = state;
	pthread_mutex_unlock(&table->stop);
}

int	ft_stop_simulation_flag(t_table *table)
{
	int	stop;

	stop = 0;
	pthread_mutex_lock(&table->stop);
	if (table->stop_cond == 1)
		stop = table->stop_cond;
	pthread_mutex_unlock(&table->stop);
	return (stop);
}

static int	ft_philo_die(t_philo *philo)
{
	time_t	time;

	time = ft_get_time();
	pthread_mutex_lock(&philo->table->eat);
	if (time - philo->last_eat > philo->table->time_to_die)
	{
		ft_print_status(philo, DEAD);
		ft_set_stop_flag(philo->table, 1);
		pthread_mutex_unlock(&philo->table->eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->eat);
	return (0);
}

static int	ft_check_death(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		if (ft_philo_die(&table->philos[i]))
			return (1);
		if (table->must_eat_count != -1)
		{
			pthread_mutex_lock(&table->eat);
			if (table->all_ate_count == table->philo_count)
			{
				ft_print_status(&table->philos[i], ALL_ATE);
				ft_set_stop_flag(table, 1);
				pthread_mutex_unlock(&table->eat);
				return (1);
			}
			pthread_mutex_unlock(&table->eat);
		}
		i++;
	}
	return (0);
}

void	*ft_monitor_stop(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	if (table->must_eat_count == 0)
		return (NULL);
	ft_set_stop_flag(table, 0);
	usleep(table->time_to_die * 300);
	while (1)
	{
		if (ft_check_death(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
