/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 17:02:47 by yorimek           #+#    #+#             */
/*   Updated: 2026/04/25 09:01:45 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;
	pthread_t	supervisor;

	if (argc != 5 && argc != 6)
		return (1);
	if (!ft_check_arg(argv, &data))
		return (2);
	if (ft_init_struct(&data, &philo))
	{
		ft_free_all(&philo, &data);
		return (1);
	}
	ft_lunch_routine(&data, &philo);
	pthread_create(&supervisor, NULL, ft_supervisor, philo);
	if (ft_wait(&philo, &supervisor))
	{
		ft_free_all(&philo, &data);
		return (1);
	}
	ft_free_all(&philo, &data);
	return (0);
}
