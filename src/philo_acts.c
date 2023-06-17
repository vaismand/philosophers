#include "philosophers.h"

int	ft_philo_eat(t_philo *philo)
{
	if (philo->table->forks[philo->left_fork] == FORK
		&& philo->table->forks[philo->right_fork] == FORK)
	{
		philo->table->forks[philo->left_fork] = EAT;
		philo->table->forks[philo->right_fork] = EAT;
		philo->state = EAT;
		philo->last_eat = ft_get_time();
		philo->eat_count++;
		ft_print_status(philo, EAT);
		ft_usleep(philo->table->time_to_eat);
		philo->table->forks[philo->left_fork] = FORK;
		philo->table->forks[philo->right_fork] = FORK;
		philo->state = SLEEP;
		ft_print_status(philo, SLEEP);
		return (1);
	}
	return (0);
}

void	*philo_act(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_philo_eat(philo))
			continue ;
		if (philo->state == SLEEP)
		{
			ft_print_status(philo, SLEEP);
			ft_usleep(philo->table->time_to_sleep);
			philo->state = THINK;
		}
		else if (philo->state == THINK)
			ft_print_status(philo, THINK);
	}
	return (NULL);
}

void	ft_start_threads(t_table *table)
{
	int			i;
	pthread_t	thread;

	i = 0;
	table->start = ft_get_time();
	while (i < table->philo_count)
	{
		if (pthread_create(&thread, NULL, philo_act, &table->philos[i]))
			ft_error_msg("Error: thread create failed\n", table);
		pthread_detach(thread);
		i++;
	}
}

void	ft_check_death(t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < table->philo_count)
		{
			if (table->philos[i].eat_count == table->must_eat_count)
				table->philos[i].state = DEAD;
			if (ft_get_time() - table->philos[i].last_eat > table->time_to_die)
			{
				ft_print_status(&table->philos[i], DEAD);
				table->dead = 1;
				return ;
			}
			i++;
		}
		if (table->dead)
			return ;
	}
}
