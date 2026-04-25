/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 16:14:24 by yorimek           #+#    #+#             */
/*   Updated: 2026/04/25 14:39:08 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_check_death(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->lock_death))
		return (-1);
	if (philo->data->is_dead)
	{
		pthread_mutex_unlock(&philo->data->lock_death);
		return (1);
	}
	if (pthread_mutex_unlock(&philo->data->lock_death))
		return (-1);
	return (0);
}

int	ft_printf_action(t_philo *philo, t_status i)
{
	long long		time;

	if (pthread_mutex_lock(&philo->data->lock_write))
		return (1);
	time = ft_get_time() - philo->data->time_start;
	if (ft_check_death(philo) && i == DEAD)
		printf("%lld %d died\n", time, philo->id);
	else
	{
		if (!ft_check_death(philo))
		{
			if (i == TAKE_FORK)
				printf("%lld %d has taken a fork\n", time, philo->id);
			else if (i == EAT)
				printf("%lld %d is eating\n", time, philo->id);
			else if (i == SLEEP)
				printf("%lld %d is sleeping\n", time, philo->id);
			else if (i == THINK)
				printf("%lld %d is thinking\n", time, philo->id);
		}
	}
	if (pthread_mutex_unlock(&philo->data->lock_write))
		return (1);
	return (0);
}

void	*ft_routine(void *arg)
{
	t_philo			*curr_philo;
	struct timeval	tv;

	curr_philo = arg;
	tv.tv_sec = 0;
	if (curr_philo->data->nb_philo == 1)
	{
		ft_printf_action(curr_philo, TAKE_FORK);
		ft_usleep(curr_philo->data->to_die, curr_philo);
		return (NULL);
	}
	if (!(curr_philo->id % 2))
		usleep(500);
	while (!ft_check_death(curr_philo))
	{
		if (!(curr_philo->id % 2))
			if (ft_fork_even(curr_philo, tv))
				return (NULL);
		if (curr_philo->id % 2)
			if (ft_fork_odd(curr_philo, tv))
				return (NULL);
	}
	return (NULL);
}

int	ft_lunch_routine(t_data *data, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&(*philo)[i].philo, NULL, ft_routine, &(*philo)[i]))
			return (1);
		i++;
	}
	return (0);
}
