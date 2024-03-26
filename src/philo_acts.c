/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:45:17 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/26 20:08:30 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	ft_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks_mutex[philo->forks[0]]);
	ft_print_status(philo, FORK);
	pthread_mutex_lock(&philo->table->forks_mutex[philo->forks[1]]);
	ft_print_status(philo, FORK);
	ft_print_status(philo, EAT);
	pthread_mutex_lock(&philo->table->eat);
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&philo->table->eat);
	if (ft_stop_simulation_flag(philo->table) == 0)
	{
		philo->eat_count++;
		if (philo->eat_count == philo->table->must_eat_count)
		{
			pthread_mutex_lock(&philo->table->eat);
			philo->table->all_ate_count++;
			pthread_mutex_unlock(&philo->table->eat);
		}
	}
	ft_philo_sleep(philo, philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->forks_mutex[philo->forks[1]]);
	pthread_mutex_unlock(&philo->table->forks_mutex[philo->forks[0]]);
	ft_print_status(philo, SLEEP);
	ft_philo_sleep(philo, philo->table->time_to_sleep);
}

static void	*ft_one_philo_act(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks_mutex[philo->forks[0]]);
	ft_print_status(philo, FORK);
	ft_philo_sleep(philo, philo->table->time_to_die);
	ft_print_status(philo, DEAD);
	pthread_mutex_unlock(&philo->table->forks_mutex[philo->forks[0]]);
	return (NULL);
}

void	ft_philo_sleep(t_philo *philo, time_t sleep_time)
{
	time_t	start;

	start = ft_get_time() + sleep_time;
	while (ft_get_time() < start)
	{
		if (ft_stop_simulation_flag(philo->table) == 1)
			break ;
		usleep(100);
	}
}

static void	ft_philo_think(t_philo *philo, int status)
{
	time_t	start;

	pthread_mutex_lock(&philo->table->eat);
	start = (philo->table->time_to_die \
		- (ft_get_time() - philo->last_eat) \
		- philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->table->eat);
	if (start < 0)
		start = 0;
	if (start == 0 && status == 1)
		start = 1;
	if (start > 600)
		start = 200;
	if (status == 0)
		ft_print_status(philo, THINK);
	ft_philo_sleep(philo, start);
}

void	*ft_philo_act(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->must_eat_count == 0)
		return (NULL);
	pthread_mutex_lock(&philo->table->eat);
	philo->last_eat = ft_get_time();
	pthread_mutex_unlock(&philo->table->eat);
	while (ft_get_time() < philo->table->start_time)
		continue ;
	if (philo->table->philo_count == 1)
		return (ft_one_philo_act(philo));
	if (philo->id % 2)
		ft_philo_think(philo, 1);
	while (ft_stop_simulation_flag(philo->table) == 0)
	{
		ft_philo_eat(philo);
		ft_philo_think(philo, 0);
	}
	return (NULL);
}
