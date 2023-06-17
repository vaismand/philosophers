#include "philosophers.h"

void	ft_error_msg(char *msg, t_table *table)
{
	ft_putstr_fd(msg, 2);
	if (table)
		ft_exit(table);
	exit(1);
}

void	ft_exit(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->write);
	free(table->forks);
	free(table->philos);
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
