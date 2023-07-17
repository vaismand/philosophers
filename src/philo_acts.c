/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_acts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:45:17 by dvaisman          #+#    #+#             */
/*   Updated: 2023/07/17 12:42:28 by dvaisman         ###   ########.fr       */
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
	while (philo->table->must_eat_count != philo->eat_count \
	&& !philo->table->stop_cond)
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

void	ft_check_death(t_philo *philo)
{
	while (1)
	{
		if (ft_get_time() - philo->last_eat > philo->table->time_to_die)
		{
			pthread_mutex_lock(&philo->table->stop);
			philo->state = DEAD;
			ft_print_status(philo, DEAD);
			philo->table->stop_cond = 1;
			break ;
		}
		if (philo->table->must_eat_count != -1 \
		&& philo->eat_count == philo->table->must_eat_count)
		{
			pthread_mutex_lock(&philo->table->eat);
			philo->table->stop_cond = 1;
			break ;
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
