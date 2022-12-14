/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miskirik <miskirik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 00:59:25 by miskirik          #+#    #+#             */
/*   Updated: 2022/10/28 14:59:11 by miskirik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo_loop(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->size == 1 && !ft_philo_check(philo))
	{
		if (pthread_mutex_lock(philo->mutex_left_fork))
			return (NULL);
		ft_philo_print(philo, "has taken a fork", 0);
		while (!ft_philo_check(philo))
		{
		}
		pthread_mutex_unlock(philo->mutex_left_fork);
	}
	else
	{
		while (!ft_philo_eat(philo)
			&& !ft_philo_sleep(philo)
			&& !ft_philo_think(philo));
	}
	return (NULL);
}

int	ft_philo_eat(t_philo *philo)
{
	if (ft_philo_check(philo))
		return (1);
	while (ft_philo_try_take_forks(philo))
		if (ft_philo_check(philo))
			return (1);
	ft_philo_print(philo, "is eating", 0);
	philo->last_eat_time = ft_get_time();
	if (ft_philo_wait(philo, philo->table->eat_duration))
		return (1);
	philo->eaten_meals += 1;
	if (philo->table->must_eat == philo->eaten_meals)
	{
		if (pthread_mutex_lock(&philo->table->mutex_full))
			return (-2);
		philo->table->full_count += 1;
		pthread_mutex_unlock(&philo->table->mutex_full);
	}
	*philo->left_fork = 0;
	*philo->right_fork = 0;
	return (0);
}

int	ft_philo_try_take_forks(t_philo *philo)
{
	int	result;

	result = 1;
	if (pthread_mutex_lock(philo->mutex_left_fork) || \
		pthread_mutex_lock(philo->mutex_right_fork))
		return (-2);
	if (!*philo->right_fork && !*philo->left_fork)
	{
		*philo->left_fork = 1;
		ft_philo_print(philo, "has taken a fork", 0);
		*philo->right_fork = 1;
		ft_philo_print(philo, "has taken a fork", 0);
		result = 0;
	}
	else
	{
		usleep(100);
	}
	pthread_mutex_unlock(philo->mutex_right_fork);
	pthread_mutex_unlock(philo->mutex_left_fork);
	return (result);
}

int	ft_philo_sleep(t_philo *philo)
{
	if (ft_philo_check(philo))
		return (1);
	ft_philo_print(philo, "is sleeping", 0);
	return (ft_philo_wait(philo, philo->table->sleep_duration));
}

int	ft_philo_think(t_philo *philo)
{
	if (ft_philo_check(philo))
		return (1);
	ft_philo_print(philo, "is thinking", 0);
	return (0);
}
