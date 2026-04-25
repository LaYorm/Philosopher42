/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 10:30:04 by yorimek           #+#    #+#             */
/*   Updated: 2026/04/25 14:22:02 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	ft_fork_even(t_philo *philo, struct timeval tv)
{
	if (pthread_mutex_lock(philo->left_fork))
		return (1);
	ft_printf_action(philo, TAKE_FORK);
	if (pthread_mutex_lock(philo->right_fork))
		return (1);
	ft_printf_action(philo, TAKE_FORK);
	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	if (pthread_mutex_lock(&philo->lock_meal))
		return (1);
	philo->last_meal = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	ft_printf_action(philo, EAT);
	philo->nb_meal++;
	if (pthread_mutex_unlock(&philo->lock_meal))
		return (1);
	ft_usleep(philo->data->to_eat, philo);
	if (pthread_mutex_unlock(philo->left_fork))
		return (1);
	if (pthread_mutex_unlock(philo->right_fork))
		return (1);
	ft_printf_action(philo, SLEEP);
	ft_usleep(philo->data->to_sleep, philo);
	ft_time_to_think(philo);
	return (0);
}

int	ft_fork_odd(t_philo *philo, struct timeval tv)
{
	if (pthread_mutex_lock(philo->right_fork))
		return (1);
	ft_printf_action(philo, TAKE_FORK);
	if (pthread_mutex_lock(philo->left_fork))
		return (1);
	ft_printf_action(philo, TAKE_FORK);
	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	if (pthread_mutex_lock(&philo->lock_meal))
		return (1);
	philo->last_meal = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	ft_printf_action(philo, EAT);
	philo->nb_meal++;
	if (pthread_mutex_unlock(&philo->lock_meal))
		return (1);
	ft_usleep(philo->data->to_eat, philo);
	if (pthread_mutex_unlock(philo->right_fork))
		return (1);
	if (pthread_mutex_unlock(philo->left_fork))
		return (1);
	ft_printf_action(philo, SLEEP);
	ft_usleep(philo->data->to_sleep, philo);
	ft_time_to_think(philo);
	return (0);
}
