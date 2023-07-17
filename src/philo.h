/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 12:39:29 by dvaisman          #+#    #+#             */
/*   Updated: 2023/07/17 14:46:07 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DEAD 4

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				state;
	pthread_t		thread;
	long long		last_eat;
	pthread_mutex_t	*right;
	pthread_mutex_t	left;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				stop_cond;
	t_philo			*philos;
	long long		start_time;
	pthread_mutex_t	write;
	pthread_mutex_t	stop;
	pthread_mutex_t	eat;
}					t_table;

int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_strlen(char *s);
int			ft_print_status(t_philo *philo, int status);
int			ft_check_args(int argc, char **argv);
int			ft_check_all_ate(t_philo *philo);
void		ft_usleep(long long time, t_table *table);
void		ft_exit_threads(t_table *table);
void		ft_error_msg(char *msg, t_table *table);
void		ft_init_vars(int argc, char **argv, t_table *table);
void		ft_init_table(t_table *table);
void		ft_putstr_fd(char *s, int fd);
void		ft_start_threads(t_table *table);
void		*ft_philo_act(void *arg);
void		ft_check_death(t_philo *philo);
long long	ft_get_time(void);

#endif
