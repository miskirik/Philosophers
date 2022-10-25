/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miskirik <miskirik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:34:28 by miskirik          #+#    #+#             */
/*   Updated: 2022/10/25 18:42:34 by miskirik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_table_init_args(t_table *table, int argc, char **argv)
{
	table->size = ft_atol(argv[1]);
	table->die_duration = ft_atol(argv[2]);
	table->eat_duration = ft_atol(argv[3]);
	table->sleep_duration = ft_atol(argv[4]);
	if (argc == 6)
		table->must_eat = ft_atol(argv[5]);
	else
		table->must_eat = -1;
	table->start_time = ft_get_time();
	if (table->must_eat == 0)
		table->full_count = table->size;
	else
		table->full_count = 0;
	table->death = 0;
}

void	ft_table_init(t_table *table, int argc, char **argv)
{
	int	i;

	ft_table_init_args(table, argc, argv);
	pthread_mutex_init(&table->mutex_print, NULL);
	pthread_mutex_init(&table->mutex_full, NULL);
	pthread_mutex_init(&table->mutex_death, NULL);
	table->philo = malloc(sizeof(t_philo) * table->size);
	table->fork = malloc(sizeof(int) * table->size);
	table->mutex_fork = malloc(sizeof(pthread_mutex_t) * table->size);
	if (!table->philo || !table->mutex_fork)
		exit(0);
	i = 0;
	while (i < table->size)
	{
		ft_philo_init(&table->philo[i], table, i);
		table->fork[i] = 0;
		pthread_mutex_init(&table->mutex_fork[i], NULL);
		i++;
	}
}

void	ft_table_loop(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->size)
	{
		pthread_create(&table->philo[i].thread, \
		NULL, &ft_philo_loop, &table->philo[i]);
		i++;
	}
	i = 0;
	while (i < table->size)
	{
		pthread_join(table->philo[i].thread, NULL);
		i++;
	}
}

void	ft_table_free(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->size)
	{
		pthread_mutex_destroy(&table->mutex_fork[i]);
		i++;
	}
	pthread_mutex_destroy(&table->mutex_death);
	free(table->philo);
	free(table->mutex_fork);
	free(table);
}
