/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 13:45:17 by dvaisman          #+#    #+#             */
/*   Updated: 2023/07/29 16:44:43 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_all_ate(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->table->philo_count)
	{
		if (philo->table->philos[i].eat_count <
			philo->table->must_eat_count)
			return ;
		i++;
	}
	pthread_mutex_lock(&philo->table->write);
	ft_print_status(philo, ALL_ATE);
	pthread_mutex_unlock(&philo->table->write);
	ft_exit_threads(philo->table);
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->left);
		ft_print_status(philo, FORK);
		pthread_mutex_lock(philo->right);
		ft_print_status(philo, FORK);
		ft_print_status(philo, EAT);
		philo->last_eat = ft_get_time();
		ft_usleep(philo->table->time_to_eat, philo->table);
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(&philo->left);
		if (philo->table->must_eat_count != -1)
			philo->eat_count++;
		if (philo->table->must_eat_count != -1 &&
			philo->eat_count == philo->table->must_eat_count)
			ft_check_all_ate(philo);
		ft_print_status(philo, SLEEP);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		ft_print_status(philo, THINK);
	}
	return (NULL);
}

int	ft_print_status(t_philo *philo, int status)
{
	long long	time;

	pthread_mutex_lock(&philo->table->write);
	time = ft_get_time() - philo->table->start_time;
	if (philo->table->stop_cond == 0)
	{
		printf("%lld %d ", time, philo->id + 1);
		if (status == FORK)
			printf("has taken a fork\n");
		else if (status == EAT)
			printf("is eating\n");
		else if (status == SLEEP)
			printf("is sleeping\n");
		else if (status == THINK)
			printf("is thinking\n");
		else if (status == DEAD)
			printf("died\n");
		else if (status == ALL_ATE)
			printf("All philosophers ate %d times\n",
				philo->table->must_eat_count);
	}
	pthread_mutex_unlock(&philo->table->write);
	return (0);
}
