/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbayrak <sbayrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 14:00:49 by sbayrak           #+#    #+#             */
/*   Updated: 2025/05/23 12:00:00 by sbayrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_on_error(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
	if (data->last_eat)
		free(data->last_eat);
}

int	init_str(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nbr_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	data->last_eat = malloc(sizeof(long long) * data->nbr_philo);
	if (!data->philos || !data->forks || !data->last_eat)
	{
		cleanup_on_error(data);
		write(2, "Error: Memory allocation failed\n", 32);
		return (1);
	}
	i = -1;
	while (++i < data->nbr_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0
			|| pthread_mutex_init(&data->philos[i].flag_mutex, NULL) != 0)
		{
			write(2, "Error: Mutex initialization failed\n", 35);
			return (1);
		}
		data->philos[i].data = data;
		data->philos[i].num = i + 1;
		data->philos[i].flag = 0;
	}
	return (0);
}

static void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		data->last_eat[i] = get_time();
		pthread_create(&data->philos[i].ph, NULL, philo_actions,
			&data->philos[i]);
		i++;
	}
}

static void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_join(data->philos[i].ph, NULL);
		i++;
	}
}

void	*ft_init_philo(t_data *data)
{
	data->current = get_time();
	data->die = 0;
	if (pthread_mutex_init(&data->mutex, NULL) != 0)
	{
		write(2, "Error: Main mutex initialization failed\n", 40);
		return (NULL);
	}
	create_threads(data);
	pthread_create(&data->death_checker, NULL,
		(void *(*)(void *))ft_check_death, data->philos);
	pthread_join(data->death_checker, NULL);
	join_threads(data);
	return (NULL);
}
