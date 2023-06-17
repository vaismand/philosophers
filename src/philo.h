#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include "../lib/libft/libft.h"

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4

typedef struct s_philo
{
	int				id;
	int				state;
	int				eat_count;
	int				last_eat;
	int				left_fork;
	int				right_fork;
	pthread_t		thread;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				dead;
	int				start;
	int				*forks;
	pthread_mutex_t	write;
	t_philo			*philos;
}					t_table;

void	ft_exit(t_table *table);
void	ft_error_msg(char *msg, t_table *table);
void	ft_init_vars(int argc, char **argv, t_table *table);
void	ft_init_table(t_table *table);
void	ft_start_threads(t_table *table);
void	ft_check_death(t_table *table);
void	ft_take_forks(t_philo *philo);

#endif
