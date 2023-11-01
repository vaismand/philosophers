/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:39:13 by dvaisman          #+#    #+#             */
/*   Updated: 2023/10/31 20:45:50 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error_msg(char *msg, t_table *table)
{
	ft_putstr_fd(msg, 2);
	if (table)
		ft_exit_threads(table);
	exit(1);
}

int	ft_check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = -1;
		while (argv[i][++j])
			if (!ft_isdigit(argv[i][j]))
				return (1);
		i++;
	}
	return (0);
}

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long long time, t_table *table)
{
	long long	start;

	start = ft_get_time();
	while (ft_get_time() - start < time)
		usleep(table->philo_count * 100);
}

int	ft_print_status(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->table->write);
	if (ft_stop_simulation_flag(philo->table) == 1)
	{
		pthread_mutex_unlock(&philo->table->write);
		return (1);
	}
	if (status == DEAD)
		printf("%lld %d died\n",
			ft_get_time() - philo->table->start_time, philo->id + 1);
	else if (status == ALL_ATE)
		printf("All philosophers ate %d times\n", philo->table->must_eat_count);
	else if (status == FORK)
		printf("%lld %d has taken a fork\n",
			ft_get_time() - philo->table->start_time, philo->id + 1);
	else if (status == EAT)
		printf("%lld %d is eating\n",
			ft_get_time() - philo->table->start_time, philo->id + 1);
	else if (status == SLEEP)
		printf("%lld %d is sleeping\n",
			ft_get_time() - philo->table->start_time, philo->id + 1);
	else if (status == THINK)
		printf("%lld %d is thinking\n",
			ft_get_time() - philo->table->start_time, philo->id + 1);
	pthread_mutex_unlock(&philo->table->write);
	return (0);
}
