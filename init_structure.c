/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:57:40 by yorimek           #+#    #+#             */
/*   Updated: 2026/04/24 17:32:37 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_init_data(t_data *data)
{
	int				i;
	struct timeval	tv;

	i = 0;
	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	data->time_start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	data->is_dead = 0;
	if (pthread_mutex_init(&data->lock_death, NULL))
		return (1);
	if (pthread_mutex_init(&data->lock_write, NULL))
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	ft_init_philo(t_philo **philo, t_data *data)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!(*philo))
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].starv = 0;
		(*philo)[i].last_meal = data->time_start;
		(*philo)[i].nb_meal = 0;
		(*philo)[i].data = data;
		(*philo)[i].left_fork = &data->forks[i];
		(*philo)[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		if (pthread_mutex_init(&(*philo)[i].lock_meal, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	ft_init_struct(t_data *data, t_philo **philo)
{
	if (ft_init_data(data))
		return (1);
	if (ft_init_philo(philo, data))
		return (1);
	return (0);
}
