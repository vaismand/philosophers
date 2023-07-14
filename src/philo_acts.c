#include "philo.h"

int	ft_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left);
	ft_print_status(philo, FORK);
	pthread_mutex_lock(philo->right);
	ft_print_status(philo, FORK);
	philo->state = EAT;
	ft_print_status(philo, EAT);
	philo->last_eat = ft_get_time();
	ft_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(philo->right);
	philo->eat_count++;
	if (philo->eat_count == philo->table->must_eat_count)
	{
		pthread_mutex_unlock(&philo->table->eat);
		return (1);
	}
	return (0);
}

void	*ft_philo_act(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (ft_philo_eat(philo))
			break ;
		ft_print_status(philo, SLEEP);
		philo->state = SLEEP;
		ft_usleep(philo->table->time_to_sleep, philo->table);
		ft_print_status(philo, THINK);
		philo->state = THINK;
	}
	return (NULL);
}

void	ft_check_death(t_philo *philo)
{
	while (1)
	{
		if (philo->state != EAT
			&& ft_get_time() - philo->last_eat > philo->table->time_to_die)
		{
			philo->state = DEAD;
			ft_print_status(philo, DEAD);
			pthread_mutex_unlock(philo->right);
			pthread_mutex_unlock(&philo->left);
			pthread_mutex_unlock(&philo->table->write);
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