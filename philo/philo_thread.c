/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbayrak <sbayrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:00:49 by sbayrak           #+#    #+#             */
/*   Updated: 2025/08/05 16:20:40 by sbayrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->die == 1)
	{
		pthread_mutex_unlock(&philo->data->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex);
	return (0);
}

static int	check_eat_limit(t_philo *philo, int eat_count)
{
	if (philo->data->nbr_eat != -1 && eat_count >= philo->data->nbr_eat)
	{
		pthread_mutex_lock(&philo->flag_mutex);
		philo->flag = 1;
		pthread_mutex_unlock(&philo->flag_mutex);
		return (1);
	}
	return (0);
}

static void	sleep_and_think(t_philo *philo)
{
	ft_printf(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
	ft_printf(philo, "is thinking");
	if (philo->data->nbr_philo % 2 == 1)
		usleep(100);
}

static void	*single_philo_action(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[0]);
	ft_printf(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(&philo->data->forks[0]);
	ft_printf(philo, "died");
	pthread_mutex_lock(&philo->data->mutex);
	philo->data->die = 1;
	pthread_mutex_unlock(&philo->data->mutex);
	return (NULL);
}

void	*philo_actions(void *arg)
{
	t_philo	*philo;
	int		eat_count;

	philo = (t_philo *)arg;
	eat_count = 0;
	if (philo->num % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (check_die(philo))
			return (NULL);
		if (philo->data->nbr_philo == 1)
			return (single_philo_action(philo));
		ft_eat(philo);
		eat_count++;
		if (check_eat_limit(philo, eat_count))
			break ;
		if (check_die(philo))
			return (NULL);
		sleep_and_think(philo);
	}
	return (NULL);
}
