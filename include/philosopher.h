/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yorimek <yorimek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 17:26:32 by yorimek           #+#    #+#             */
/*   Updated: 2026/04/25 14:22:42 by yorimek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

//-------------INLCUDES------------//
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

//-----------STRUCTURES------------//
typedef struct s_data
{
	int				nb_philo;
	int				to_die;
	int				to_eat;
	int				to_sleep;
	int				nb_to_eat;
	int				is_dead;
	long long		time_start;
	pthread_mutex_t	lock_death;
	pthread_mutex_t	lock_write;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				starv;
	long long		last_meal;
	int				nb_meal;
	t_data			*data;
	pthread_t		philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	lock_meal;
}	t_philo;

typedef enum e_status
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
}	t_status;

//---------CHECK_INIT_ARG----------//
int			ft_all_num(char *arg);
int			ft_atoi(char *arg);
int			ft_check_arg(char **argv, t_data *data);

//---------init_structure------------//
int			ft_init_data(t_data *data);
int			ft_init_philo(t_philo **philo, t_data *data);
int			ft_init_struct(t_data *data, t_philo **philo);

//---------utils.c------------//
void		ft_free_all(t_philo **philo, t_data *data);
int			ft_wait_end_thread(t_philo **philo, pthread_t *supervisor);
void		ft_usleep(long long time, t_philo *philo);
long long	ft_get_time(void);
void		ft_time_to_think(t_philo *philo);

//----------routine.c--------------//
int			ft_lunch_routine(t_data *data, t_philo **philo);
int			ft_printf_action(t_philo *philo, t_status i);
int			ft_check_death(t_philo *philo);
void		*ft_routine(void *arg);

//----------action.c--------------//
int			ft_fork_even(t_philo *philo, struct timeval tv);
int			ft_fork_odd(t_philo *philo, struct timeval tv);

//----------supervisor.c--------------//
void		*ft_supervisor(void *arg);
int			ft_check_nb_meal(t_philo *philo);
int			ft_utils_death(t_philo *philo);

#endif
