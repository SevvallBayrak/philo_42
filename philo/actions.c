/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbayrak <sbayrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:00:49 by sbayrak           #+#    #+#             */
/*   Updated: 2025/08/05 16:54:28 by sbayrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	get_fork_order(t_philo *philo, int *first, int *second)
{
	if (philo->num == philo->data->nbr_philo)
	{
		*first = 0;
		*second = philo->num - 1;
	}
	else
	{
		*first = philo->num - 1;
		*second = philo->num % philo->data->nbr_philo;
	}
}

static int	take_first_fork(t_philo *philo, int fork_idx)
{
	pthread_mutex_lock(&philo->data->forks[fork_idx]);
	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->die)
	{
		pthread_mutex_unlock(&philo->data->mutex);
		pthread_mutex_unlock(&philo->data->forks[fork_idx]);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->mutex);
	ft_printf(philo, "has taken a fork");
	return (1);
}

static int	take_second_fork(t_philo *philo, int first_fork, int second_fork)
{
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->die)
	{
		pthread_mutex_unlock(&philo->data->mutex);
		pthread_mutex_unlock(&philo->data->forks[second_fork]);
		pthread_mutex_unlock(&philo->data->forks[first_fork]);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->mutex);
	ft_printf(philo, "has taken a fork");
	return (1);
}

static int	take_forks(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	get_fork_order(philo, &first_fork, &second_fork);
	if (!take_first_fork(philo, first_fork))
		return (0);
	if (!take_second_fork(philo, first_fork, second_fork))
		return (0);
	return (1);
}

void	ft_eat(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

	if (!take_forks(philo))
		return ;
	get_fork_order(philo, &first_fork, &second_fork);
	ft_printf(philo, "is eating");
	pthread_mutex_lock(&philo->data->mutex);
	philo->data->last_eat[philo->num - 1] = get_time();
	pthread_mutex_unlock(&philo->data->mutex);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[first_fork]);
	pthread_mutex_unlock(&philo->data->forks[second_fork]);
}
