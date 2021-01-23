/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 18:20:44 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/20 18:28:12 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	g_turn = 0;

void	ft_set_stat(t_philo *philo, int stat)
{
	if (philo->stat != DIED)
		philo->stat = stat;
}

void	*philosophers(void *ptr)
{
	t_philo *philo;

	philo = ptr;
	pthread_mutex_lock(&g_mutex);
	while (g_stat && (g_nb_of_eat == -1 || philo->nb_of_eat < g_nb_of_eat))
	{
		ft_think(philo);
		ft_take_forks(philo);
		ft_eat(philo);
		ft_put_forks(philo);
		ft_sleep(philo);
	}
	ft_set_stat(philo, DONE);
	pthread_mutex_unlock(&g_mutex);
	return (NULL);
}

int		run(void)
{
	int	i;
	int	done_philos;

	done_philos = 0;
	while (done_philos < g_nb_of_philos)
	{
		i = 0;
		done_philos = 0;
		while (i < g_nb_of_philos)
		{
			if (g_philos[i].stat == DONE)
				done_philos++;
			else if ((get_time_stamp() - g_philos[i].last_eat > g_time_to_die)
			&& g_philos[i].stat != EATING)
			{
				g_stat = false;
				g_philos[i].stat = DIED;
				ft_print_status(&g_philos[i]);
				return (EXIT_SUCCESS);
			}
			i++;
		}
	}
	pthread_mutex_lock(&g_print_mutex);
	return (EXIT_SUCCESS);
}

int		finalize(void)
{
	free(g_philos);
	free(g_forks_mutex);
	return (EXIT_SUCCESS);
}

int		main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ft_error("usage: ./philo_one number_of_philosophers"
		"g_time_to_die g_time_to_eat g_time_to_sleep "
		"[number_of_times_each_philosopher_must_eat]"));
	g_nb_of_philos = ft_atoi(argv[1]);
	g_time_to_die = ft_atoi(argv[2]) * 1000;
	g_time_to_eat = ft_atoi(argv[3]) * 1000;
	g_time_to_sleep = ft_atoi(argv[4]) * 1000;
	g_nb_of_eat = (argc == 6) ? ft_atoi(argv[5]) : -1;
	if (g_nb_of_philos < 0 || g_time_to_die < 0 || g_time_to_eat < 0 ||
	g_time_to_sleep < 0 || g_nb_of_eat < -1)
		return (EXIT_FAILURE);
	if (init() || run() || finalize())
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
