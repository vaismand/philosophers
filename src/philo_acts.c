/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:45:17 by dvaisman          #+#    #+#             */
/*   Updated: 2023/07/31 15:06:03 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_eat(t_philo *philo)
{
	while (philo->table->stop_cond != 1)
	{
		pthread_mutex_lock(&philo->left);
		ft_print_status(philo, FORK);
		pthread_mutex_lock(philo->right);
		ft_print_status(philo, FORK);
		pthread_mutex_lock(&philo->table->eat);
		philo->state = EAT;
		ft_print_status(philo, EAT);
		philo->last_eat = ft_get_time();
		pthread_mutex_unlock(&philo->table->eat);
		ft_usleep(philo->table->time_to_eat, philo->table);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->left);
		pthread_mutex_unlock(philo->right);
		return (0);
	}
	return (1);
}

void	*ft_philo_act(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_eat, philo->table);
	while (philo->table->stop_cond != 1 && \
		philo->table->all_ate_count != philo->table->must_eat_count)
	{
		ft_philo_eat(philo);
		philo->state = SLEEP;
		ft_print_status(philo, SLEEP);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		philo->state = THINK;
		ft_print_status(philo, THINK);
	}
	return (NULL);
}

void	ft_check_death(t_table *table, t_philo *philo)
{
	int	i;

	while (!table->all_ate_count)
	{
		i = -1;
		while (++i < table->philo_count && !table->stop_cond)
		{
			pthread_mutex_lock(&table->eat);
			if (ft_get_time() - philo[i].last_eat >= table->time_to_die)
			{
				ft_print_status(&philo[i], DEAD);
				table->stop_cond = 1;
			}
			pthread_mutex_unlock(&philo->table->eat);
		}
		if (table->stop_cond == 1)
			break ;
		i = 0;
		while (table->must_eat_count != -1 && i < table->philo_count && \
			philo[i].eat_count >= table->must_eat_count)
			i++;
		if (i == table->philo_count)
			table->all_ate_count = i;
	}
}

int	ft_print_status(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->table->write);
	if (status == FORK)
		printf("%lld %d has taken a fork\n",
			ft_get_time() - philo->table->start_time, philo->id);
	else if (status == EAT)
		printf("%lld %d is eating\n",
			ft_get_time() - philo->table->start_time, philo->id);
	else if (status == SLEEP)
		printf("%lld %d is sleeping\n",
			ft_get_time() - philo->table->start_time, philo->id);
	else if (status == THINK)
		printf("%lld %d is thinking\n",
			ft_get_time() - philo->table->start_time, philo->id);
	else if (status == ALL_ATE)
		printf("All philosophers ate %d times\n", philo->table->must_eat_count);
	else if (status == DEAD)
	{
		printf("%lld %d died\n",
			ft_get_time() - philo->table->start_time, philo->id);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->write);
	return (0);
}
