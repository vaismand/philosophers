#include "philo.h"



int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		t_table	*table;

		table = malloc(sizeof(t_table));
		if (!table)
			ft_error_msg("Error: malloc failed\n", NULL);
		ft_init_vars(argc, argv, table);
		ft_init_table(table);
		ft_start_threads(table);
	}
	else
		ft_error_msg("Error: wrong number of arguments\n", NULL);
	return (0);
}
