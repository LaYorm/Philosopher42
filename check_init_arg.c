/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_init_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:54:48 by yorimek           #+#    #+#             */
/*   Updated: 2026/04/24 12:57:36 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_all_num(char *arg)
{
	while (*arg)
	{
		if (*arg > '9' || *arg < '0')
			return (0);
		arg++;
	}
	return (1);
}

int	ft_atoi(char *arg)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (!ft_all_num(arg))
		return (-1);
	while (arg[i])
	{
		res = res * 10 + (arg[i] - 48);
		i++;
	}
	if (res > 2147483647)
		return (-1);
	return (res);
}

int	ft_check_arg(char **argv, t_data *data)
{
	int	i;
	int	temp;

	i = 1;
	while (argv[i])
	{
		temp = ft_atoi(argv[i]);
		if (temp < 0 || (temp == 0 && i == 1))
			return (0);
		if (i == 1 && temp > 0)
			data->nb_philo = temp;
		else if (i == 2 && temp >= 0)
			data->to_die = temp;
		else if (i == 3 && temp >= 0)
			data->to_eat = temp;
		else if (i == 4 && temp >= 0)
			data->to_sleep = temp;
		else if (i == 5 && temp >= 0)
			data->nb_to_eat = temp;
		i++;
	}
	if (i == 5)
		data->nb_to_eat = -1;
	return (1);
}
