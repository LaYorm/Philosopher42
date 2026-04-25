/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 15:30:20 by yorimek           #+#    #+#             */
/*   Updated: 2026/04/25 12:29:58 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

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
