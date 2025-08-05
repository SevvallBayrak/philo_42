/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbayrak <sbayrak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:00:00 by sbayrak           #+#    #+#             */
/*   Updated: 2025/07/31 18:39:10 by sbayrak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				num;
	pthread_t		ph;
	int				flag;
	pthread_mutex_t	flag_mutex;
}					t_philo;

typedef struct s_data
{
	t_philo			*philos;
	pthread_mutex_t	mutex;
	pthread_mutex_t	*forks;
	int				nbr_philo;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				nbr_eat;
	long long		*last_eat;
	long long		current;
	int				die;
	pthread_t		death_checker;
}					t_data;

int				ft_atoi(const char *str);
long long		get_time(void);
int				ft_checkargs(char **argv);
void			get_struct(int argc, char **argv, t_data *data);
void			ft_printf(t_philo *philo, char *s);
void			ft_usleep(int time);
void			*philo_actions(void *arg);
void			*ft_check_death(t_philo *philo);
int				init_str(t_data *data);
void			*ft_init_philo(t_data *data);
void			ft_eat(t_philo *philo);

#endif