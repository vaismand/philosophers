#include "philo.h"

/*int	ft_philo_eat(t_philo *philo)
{
	if (philo->table->forks[philo->left_fork] == FORK
		&& philo->table->forks[philo->right_fork] == FORK)
	{
		philo->table->forks[philo->left_fork] = EAT;
		philo->table->forks[philo->right_fork] = EAT;
		philo->state = EAT;
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
}*/

