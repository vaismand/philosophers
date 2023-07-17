/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:45:17 by dvaisman          #+#    #+#             */
/*   Updated: 2023/07/17 14:50:14 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_philo_eat(t_philo *philo)
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
	philo->eat_count++;
	ft_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(philo->right);
	return (0);
}

void	*ft_philo_act(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_eat, philo->table);
	while (!philo->table->stop_cond)
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

int	ft_check_all_ate(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->philo_count)
	{
		if (philo[i].eat_count < philo->table->must_eat_count)
			return (0);
		i++;
	}
	return (1);
}

void	ft_check_death(t_philo *philo)
{
	int	i;

	while (!philo->table->stop_cond)
	{
		i = 0;
		while (i < philo->table->philo_count)
		{
			pthread_mutex_lock(&philo->table->eat);
			if (ft_get_time() - philo[i].last_eat > philo->table->time_to_die)
			{
				ft_print_status(&philo[i], DEAD);
				philo->table->stop_cond = 1;
				pthread_mutex_unlock(&philo->table->eat);
				break ;
			}
			pthread_mutex_unlock(&philo->table->eat);
			i++;
		}
		if (!philo->table->stop_cond && philo->table->must_eat_count > 0)
		{
			if (ft_check_all_ate(philo))
				philo->table->stop_cond = 1;
		}
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
	else if (status == DEAD)
	{
		printf("%lld %d died\n",
			ft_get_time() - philo->table->start_time, philo->id);
		pthread_mutex_unlock(&philo->table->stop);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->write);
	return (0);
}
