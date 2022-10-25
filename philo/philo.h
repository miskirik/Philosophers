/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miskirik <miskirik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:28:05 by miskirik          #+#    #+#             */
/*   Updated: 2022/10/25 20:03:53 by miskirik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	int					size;
	int					must_eat;
	unsigned long long	die_duration;
	unsigned long long	eat_duration;
	unsigned long long	sleep_duration;
	unsigned long long	start_time;
	t_philo				*philo;
	int					*fork;
	int					full_count;
	int					death;
	int					total_eat;
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		mutex_full;
	pthread_mutex_t		mutex_death;
	pthread_mutex_t		*mutex_fork;
}	t_table;

typedef struct s_philo
{
	int					id;
	int					meat;
	int					eaten_meals;
	int					is_dead;
	unsigned long long	last_eat_time;
	pthread_t			thread;
	int					*left_fork;
	int					*right_fork;
	pthread_mutex_t		*mutex_left_fork;
	pthread_mutex_t		*mutex_right_fork;
	t_table				*table;
}	t_philo;

long				ft_atol(const char *str);
unsigned long long	ft_get_time(void);
int					ft_check_args(int argc, char **argv);
void				ft_table_init(t_table *table, int argc, char **argv);
void				ft_table_free(t_table *table);
void				ft_table_loop(t_table *table);
void				ft_table_init_args(t_table *table, int argc, char **argv);
void				*ft_philo_loop(void *philo);
void				ft_philo_init(t_philo *philo, t_table *table, int id);
int					ft_philo_eat(t_philo *philo);
int					ft_philo_try_take_forks(t_philo *philo);
int					ft_philo_sleep(t_philo *philo);
int					ft_philo_think(t_philo *philo);
int					ft_philo_check(t_philo *philo);
int					ft_philo_wait(t_philo *philo, unsigned long long wait_time);
void				ft_philo_print(t_philo *philo, char *stat, int kill);

#endif
