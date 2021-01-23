/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:50:13 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/20 18:08:31 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_think(t_philo *philo)
{
	ft_set_stat(philo, THINKING);
	ft_print_status(philo);
}

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_unlock(&g_mutex);
	pthread_mutex_lock(&g_forks_mutex[philo->id - 1]);
	pthread_mutex_lock(&g_forks_mutex[philo->id % g_nb_of_philos]);
	ft_set_stat(philo, TAKE_FORKS);
	ft_print_status(philo);
}

void	ft_eat(t_philo *philo)
{
	ft_set_stat(philo, EATING);
	philo->nb_of_eat++;
	ft_print_status(philo);
	philo->last_eat = get_time_stamp();
	usleep(g_time_to_eat - 20000);
	while (get_time_stamp() - philo->last_eat < g_time_to_eat)
		;
}

void	ft_put_forks(t_philo *philo)
{
	ft_set_stat(philo, PUTS_FORKS);
	pthread_mutex_unlock(&g_forks_mutex[philo->id - 1]);
	pthread_mutex_unlock(&g_forks_mutex[philo->id % g_nb_of_philos]);
}

void	ft_sleep(t_philo *philo)
{
	t_micro_second_t begin;

	ft_set_stat(philo, SLEEPING);
	ft_print_status(philo);
	begin = get_time_stamp();
	usleep(g_time_to_sleep - 20000);
	while (get_time_stamp() - begin < g_time_to_sleep)
		;
}
