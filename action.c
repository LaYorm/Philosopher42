/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 10:30:04 by yorimek           #+#    #+#             */
/*   Updated: 2026/04/25 10:49:23 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_fork_even(t_philo *philo, struct timeval tv)
{
	if (pthread_mutex_lock(philo->left_fork))
		return (1);
	ft_printf_action(philo, 0);
	if (pthread_mutex_lock(philo->right_fork))
		return (1);
	ft_printf_action(philo, 0);
	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	if (pthread_mutex_lock(&philo->lock_meal))
		return (1);
	philo->last_meal = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	ft_printf_action(philo, 1);
	philo->nb_meal++;
	if (pthread_mutex_unlock(&philo->lock_meal))
		return (1);
	usleep(philo->data->to_eat * 1000);
	if (pthread_mutex_unlock(philo->left_fork))
		return (1);
	if (pthread_mutex_unlock(philo->right_fork))
		return (1);
	ft_printf_action(philo, 2);
	usleep(philo->data->to_sleep * 1000);
	ft_printf_action(philo, 3);
	return (0);
}

int	ft_fork_odd(t_philo *philo, struct timeval tv)
{
	if (pthread_mutex_lock(philo->right_fork))
		return (1);
	ft_printf_action(philo, 0);
	if (pthread_mutex_lock(philo->left_fork))
		return (1);
	ft_printf_action(philo, 0);
	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	if (pthread_mutex_lock(&philo->lock_meal))
		return (1);
	philo->last_meal = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	ft_printf_action(philo, 1);
	philo->nb_meal++;
	if (pthread_mutex_unlock(&philo->lock_meal))
		return (1);
	usleep(philo->data->to_eat * 1000);
	if (pthread_mutex_unlock(philo->right_fork))
		return (1);
	if (pthread_mutex_unlock(philo->left_fork))
		return (1);
	ft_printf_action(philo, 2);
	usleep(philo->data->to_sleep * 1000);
	ft_printf_action(philo, 3);
	return (0);
}
