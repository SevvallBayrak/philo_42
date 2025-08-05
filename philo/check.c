/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbayrak <sbayrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:00:49 by sbayrak           #+#    #+#             */
/*   Updated: 2025/07/30 12:28:13 by sbayrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_checkargs(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '+')
			j++;
		if (argv[i][j] == '\0')
			return (1);
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		if (ft_atoi(argv[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

static int	check_philo_death(t_philo *philo, int i, long long current_time)
{
	int	is_dead;

	pthread_mutex_lock(&philo[i].flag_mutex);
	is_dead = 0;
	if (philo->data->time_to_die <= current_time - philo->data->last_eat[i])
	{
		if (philo[i].flag != 1)
		{
			printf("%lld %d died\n", current_time - philo->data->current,
				philo[i].num);
			philo->data->die = 1;
		}
		is_dead = 1;
	}
	pthread_mutex_unlock(&philo[i].flag_mutex);
	return (is_dead);
}

static int	check_one_philo_death(t_philo *philo, int i)
{
	long long	current_time;

	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->die)
	{
		pthread_mutex_unlock(&philo->data->mutex);
		return (1);
	}
	current_time = get_time();
	if (check_philo_death(philo, i, current_time))
	{
		pthread_mutex_unlock(&philo->data->mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mutex);
	return (0);
}

void	*ft_check_death(t_philo *philo)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < philo->data->nbr_philo)
		{
			if (check_one_philo_death(philo, i))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	get_struct(int argc, char **argv, t_data *data)
{
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->nbr_eat = ft_atoi(argv[5]);
	else
		data->nbr_eat = -1;
}
