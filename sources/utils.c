/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:30:20 by yorimek           #+#    #+#             */
/*   Updated: 2026/04/25 13:26:37 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

long long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time,t_philo *philo)
{
	long long	time_start;

	time_start = ft_get_time();
	while (ft_get_time() - time_start < time)
	{
		if (ft_check_death(philo))
			break;
		usleep(500);
	}
}

int	ft_wait(t_philo **philo, pthread_t *supervisor)
{
	int	i;

	i = 0;
	if (pthread_join(*supervisor, NULL))
		return (1);
	while (i < (*philo)->data->nb_philo)
	{
		if (pthread_join((*philo)[i].philo, NULL))
			return (1);
		i++;
	}
	return (0);
}

void	ft_free_all(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->lock_death);
	pthread_mutex_destroy(&data->lock_write);
	free (*philo);
	free (data->forks);
}
