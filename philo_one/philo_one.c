/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 18:20:44 by ojoubout          #+#    #+#             */
/*   Updated: 2021/01/16 13:00:25 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	g_turn = 0;

int ft_error(char *err)
{
    write(2, err, ft_strlen(err));
    write(2, "\n", 1);
    return (EXIT_FAILURE);
}

void    ft_think(t_philo *philo)
{
    philo->stat = THINKING;
	ft_print_status(philo);
	// while (g_turn == 0 && (forks[philo->id - 1] || forks[philo->id % nb_of_philos]));
}

void    ft_take_forks(t_philo *philo)
{
    pthread_mutex_unlock(&mutex);

	// if (forks[philo->id - 1] || forks[philo->id % nb_of_philos])
	// {
    // 	pthread_mutex_lock(&mutex);
    // 	pthread_mutex_unlock(&mutex);
	// }

	// while (forks[philo->id - -1] || forks_mutex[philo->id % nb_of_philos])
	// {
	// }
	pthread_mutex_lock(&forks_mutex[philo->id - 1]);
	forks[philo->id - 1] = true;
	pthread_mutex_lock(&forks_mutex[philo->id % nb_of_philos]);
	forks[philo->id % nb_of_philos] = true;
	philo->stat = TAKE_FORKS;
	ft_print_status(philo);
    // pthread_mutex_unlock(&mutex);


}

void    ft_eat(t_philo *philo)
{
    philo->stat = EATING;
	philo->nb_of_eat++;
	ft_print_status(philo);
	usleep(time_to_eat);
	philo->last_eat = get_time_stamp();
}

void    ft_put_forks(t_philo *philo)
{
	philo->stat = PUTS_FORKS;
	ft_print_status(philo);
    pthread_mutex_unlock(&forks_mutex[philo->id - 1]);
    forks[philo->id - 1] = false;

    pthread_mutex_unlock(&forks_mutex[philo->id % nb_of_philos]);
    forks[philo->id % nb_of_philos] = false;



}

void    ft_sleep(t_philo *philo)
{
    philo->stat = SLEEPING;
	ft_print_status(philo);
	usleep(time_to_sleep);
}

void    *philosophers(void *ptr)
{
    t_philo *philo;

    philo = ptr;
    pthread_mutex_lock(&mutex);
    while (g_nb_of_eat == -1 || philo->nb_of_eat < g_nb_of_eat)
    {
        ft_think(philo);
        ft_take_forks(philo);
        ft_eat(philo);
        ft_put_forks(philo);
        ft_sleep(philo);
    }
	philo->stat = DONE;
    pthread_mutex_unlock(&mutex);
    return (NULL);
}

int    init()
{
    int i;

    // nb_of_philos = 2;
    // time_to_die = 4010 * 1000;
    // time_to_eat = 2000 * 1000;
    // time_to_sleep = 4000 * 1000;
    // g_nb_of_eat = 0;
    if (pthread_mutex_init(&mutex, NULL) ||
    pthread_mutex_init(&die_mutex, NULL) ||
    pthread_mutex_init(&print_mutex, NULL))
        return (ft_error("mutex init failed!"));
    // printf("size of bool: %lu\n", sizeof(bool));
    if (!(g_philos = malloc(sizeof(t_philo) * nb_of_philos)) ||
        !(forks = malloc(sizeof(bool) * nb_of_philos)) ||
        !(forks_mutex = malloc(sizeof(pthread_mutex_t) * nb_of_philos)))
        return (ft_error("malloc failed!"));
    i = 0;
	ft_bzero(forks, sizeof(bool) * nb_of_philos);

	// i++;
	while (i < nb_of_philos)
		if (pthread_mutex_init(&forks_mutex[i++], NULL))
			return (ft_error("mutex init failed!"));
	i = 0;
	g_start_time = get_time_stamp();
    pthread_mutex_lock(&mutex);
    while (i < nb_of_philos)
    {
        g_philos[i].id = i + 1;
        g_philos[i].stat = -1;
		g_philos[i].nb_of_eat = 0;
        g_philos[i].last_eat = g_start_time;
        if (pthread_create(&g_philos[i].thread, NULL, philosophers, &g_philos[i]))
            return (ft_error("pthread_create failed!"));
		usleep(100);
        i++;
    }    
    pthread_mutex_unlock(&mutex);

    return (EXIT_SUCCESS);
}

int    run()
{
    // pthread_mutex_lock(&die_mutex);
    // pthread_mutex_lock(&die_mutex);
	int	i;
	int	done_philos;

	done_philos = 0;
	while (done_philos < nb_of_philos)
	{
		i = 0;
		while (i < nb_of_philos)
		{
			if (g_philos[i].stat == DONE)
				done_philos++;
			else if ((get_time_stamp() - g_philos[i].last_eat > time_to_die) && g_philos[i].stat != EATING)
			{
				// printf(" %lu %lu %lu %lu %d\n", mc, g_philos[i].last_eat, mc - g_philos[i].last_eat, time_to_die, mc - g_philos[i].last_eat > time_to_die);
				
				// char c = g_philos[i].stat + 48;
				// write(1, &c, 1);
				g_philos[i].stat = DIED;
				ft_print_status(&g_philos[i]);
				return (EXIT_SUCCESS);
			}
			i++;
		}
	}
    return (EXIT_FAILURE);
}

int    finalize()
{
    return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	// argv = NULL;
	if (argc != 5 && argc != 6)
		return (ft_error("usage: ./philo_one number_of_philosophers"
		"time_to_die time_to_eat time_to_sleep "
		 "[number_of_times_each_philosopher_must_eat]"));
	nb_of_philos = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]) * 1000;
	time_to_eat = ft_atoi(argv[3]) * 1000;
	time_to_sleep = ft_atoi(argv[4]) * 1000;
	// printf("%lu\n", time_to_die);
	g_nb_of_eat = (argc == 6) ? ft_atoi(argv[5]) : -1;
	printf("%d %lu %lu %lu\n", nb_of_philos, time_to_die, time_to_eat, time_to_sleep);
	if (nb_of_philos < 0 || time_to_die < 0 || time_to_eat < 0 ||
	time_to_sleep < 0 || g_nb_of_eat < -1)
        return (EXIT_FAILURE);
    if (init() || run() || finalize())
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}