/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:30:20 by yorimek           #+#    #+#             */
/*   Updated: 2026/04/25 14:24:40 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	ft_time_to_think(t_philo *philo)
{
	long long	time_to_think;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;

	time_to_die = philo->data->to_die;
	time_to_eat = philo->data->to_eat;
	time_to_sleep = philo->data->to_sleep;
	ft_printf_action(philo, THINK);
	time_to_think = (time_to_die - (time_to_eat + time_to_sleep)) / 2;
	if (time_to_think > 0)
		ft_usleep(time_to_think, philo);
}

long long	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time, t_philo *philo)
{
	long long	time_start;

	time_start = ft_get_time();
	while (ft_get_time() - time_start < time)
	{
		if (ft_check_death(philo))
			break ;
		usleep(500);
	}
}

int	ft_wait_end_thread(t_philo **philo, pthread_t *supervisor)
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
