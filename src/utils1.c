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
		usleep(table->philo_count * 50);
}
