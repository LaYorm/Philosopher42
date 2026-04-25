/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 17:44:14 by yorimek           #+#    #+#             */
/*   Updated: 2026/04/25 10:25:24 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_utils_death(t_philo *philo)
{
	struct timeval	tv;
	long long		diff;

	pthread_mutex_lock(&philo->lock_meal);
	gettimeofday(&tv, NULL);
	diff = tv.tv_sec * 1000 + tv.tv_usec / 1000 - philo->last_meal;
	if (diff >= philo->data->to_die)
	{
		pthread_mutex_lock(&philo->data->lock_death);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->lock_death);
		if (ft_printf_action(philo, 4))
		{
			pthread_mutex_unlock(&philo->lock_meal);
			return (1);
		}
		pthread_mutex_unlock(&philo->lock_meal);
		return (1);
	}
	pthread_mutex_unlock(&philo->lock_meal);
	return (0);
}

int	ft_check_nb_meal(t_philo *philo)
{
	int	i;
	int	nb_reach_nb_meal;

	i = 0;
	nb_reach_nb_meal = 0;
	while (i < philo->data->nb_philo)
	{
		pthread_mutex_lock(&(philo[i]).lock_meal);
		if (philo[i].nb_meal >= philo[i].data->nb_to_eat)
			nb_reach_nb_meal++;
		pthread_mutex_unlock(&(philo[i]).lock_meal);
		i++;
	}
	if (nb_reach_nb_meal == philo->data->nb_philo)
	{
		pthread_mutex_lock(&(philo)->data->lock_death);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&(philo)->data->lock_death);
		return (1);
	}
	return (0);
}

void	*ft_supervisor(void *arg)
{
	t_philo	*curr_philo;
	int		i;
	int		nb_philo;

	curr_philo = arg;
	i = 0;
	nb_philo = curr_philo->data->nb_philo;
	while (i < curr_philo->data->nb_philo)
	{
		if (ft_utils_death(&(curr_philo[i])))
			return (NULL);
		if (curr_philo->data->nb_to_eat != -1)
			if (ft_check_nb_meal(curr_philo))
				return (NULL);
		i++;
		if (i == nb_philo)
			i = 0;
		usleep(500);
	}
	return (NULL);
}
