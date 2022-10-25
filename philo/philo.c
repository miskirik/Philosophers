/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miskirik <miskirik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 07:41:07 by miskirik          #+#    #+#             */
/*   Updated: 2022/10/25 20:08:54 by miskirik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_init(t_philo *philo, t_table *table, int id)
{
	philo->table = table;
	philo->id = id;
	philo->last_eat_time = table->start_time;
	philo->eaten_meals = 0;
	philo->left_fork = &table->fork[id];
	philo->right_fork = &table->fork[(id + 1) % table->size];
	philo->mutex_left_fork = &table->mutex_fork[id];
	philo->mutex_right_fork = &table->mutex_fork[(id + 1) % table->size];
}

int	ft_philo_check(t_philo *philo)
{
	if (philo->table->full_count == philo->table->size)
		return (1);
	if (philo->table->death)
		return (1);
	if (ft_get_time() - philo->last_eat_time > philo->table->die_duration)
	{
		if (pthread_mutex_lock(&philo->table->mutex_death))
			exit(0);
		ft_philo_print(philo, "died", 1);
		pthread_mutex_unlock(&philo->table->mutex_death);
		return (1);
	}
	return (0);
}

int	ft_philo_wait(t_philo *philo, unsigned long long wait_time)
{
	unsigned long long	time;

	time = ft_get_time();
	while (ft_get_time() - time < wait_time)
	{
		if (ft_philo_check(philo))
			return (1);
		usleep(100);
	}
	return (0);
}

void	ft_philo_print(t_philo *philo, char *status, int kill)
{
	if (pthread_mutex_lock(&philo->table->mutex_print))
		exit(0);
	if (!philo->table->death)
	{
		printf("%llu %d %s\n",
			(ft_get_time() - philo->table->start_time),
			philo->id + 1, status);
		if (kill)
			philo->table->death = 1;
	}
	pthread_mutex_unlock(&philo->table->mutex_print);
}
