/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 17:50:13 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/20 19:16:45 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	ft_think(t_philo *philo)
{
	ft_set_stat(philo, THINKING);
	ft_print_status(philo);
	sem_wait(g_one_at_time);
}

void	ft_take_forks(t_philo *philo)
{
	sem_wait(g_forks_sem);
	sem_wait(g_forks_sem);
	ft_set_stat(philo, TAKE_FORKS);
	ft_print_status(philo);
	sem_post(g_one_at_time);
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
	sem_post(g_forks_sem);
	sem_post(g_forks_sem);
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
