/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojoubout <ojoubout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:40:37 by ojoubout          #+#    #+#             */
/*   Updated: 2020/03/03 10:30:46 by ojoubout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <stdio.h>

void	finit();

char		STATE = 1;
int 		number_of_philosophers = 5;
ulong		time_to_die = 1000 * 1000 * 7.1;
ulong		time_to_eat = 1000 * 1000 * 2;
ulong		time_to_sleep = 1000 * 1000 * 7;
int			number_of_times_each_philosopher_must_eat;

t_philo		*philos;
pthread_t	shinigami;
// char		*p_status;

sem_t		*forks;
sem_t		*one_at_time;

void	died(t_philo *philo, ulong time, ulong leat)
{
	int i;

	i = 0;
	STATE = 0;
	print_status(philo->id, DIED);
	while (i < number_of_philosophers)
	{
		pthread_detach(philos[i].thread);
		i++;
	}
	pthread_detach(shinigami);
	if (number_of_philosophers == 1)
		finit();
	// pthread_mutex_lock(&g_print_mutex);
		// printf("%lu %lu %lu %d\n", time, leat, time_to_die, philo->id);
	// pthread_mutex_unlock(&g_print_mutex);
	
	// exit(-1);
}

void	*check_die()
{
	int		i;
	ulong	time;
	ulong	leat;

	while (STATE)
	{
		i = 0;
		while (i < number_of_philosophers)
		{
			time = get_time_stamp();
			leat = philos[i].last_eat;
			if (time > leat && ((time - leat) > time_to_die))
				died(&philos[i], time, leat);
			i++;
		}
	}
	return (NULL);
}

int	take_forks(t_philo *philo)
{
	// int lfork;

	// lfork = (philo->id < number_of_philosophers) ? philo->id : 0;

	// // print_status(philo->id, 5);
	// if ((philo->id - 1) == lfork || forks[philo->id - 1] || forks[lfork])
	// 	return (0);
	// forks[philo->id - 1] = 1;
	// forks[lfork] = 1;
	sem_wait(forks);
	sem_wait(forks);
	print_status(philo->id, TAKE_FORKS);
	return (1);
}

void	put_forks(t_philo *philo)
{
	// int lfork;

	// lfork = (philo->id < number_of_philosophers) ? philo->id : 0;
	// forks[philo->id - 1] = 0;
	// forks[lfork] = 0;
	sem_post(forks);
	sem_post(forks);
}

void	sleeping(t_philo *philo)
{
	print_status(philo->id, SLEEPING);
	usleep(time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_status(philo->id, THINKING);
}

void	eat(t_philo *philo)
{

	philo->last_eat = get_time_stamp();
	print_status(philo->id, EATING);
	// while (get_time_stamp() < (time + time_to_eat))
	// 	;
	usleep(time_to_eat);
	philo->last_eat = get_time_stamp();

}

void	*philosopher(void	*ph)
{
	t_philo *philo = (t_philo *)ph;
	while (STATE)
	{
		thinking(philo);
		// pthread_mutex_lock(&mutex);
		sem_wait(one_at_time);
		// check_die(philo);
		if (take_forks(philo))
		{
			// pthread_mutex_unlock(&mutex);
			sem_post(one_at_time);
			eat(philo);
			put_forks(philo);
			sleeping(philo);
		}
		else
			sem_post(one_at_time);
			// pthread_mutex_unlock(&mutex);
		
	}
	return (NULL);

}



void	init(char *argv[])
{
	int i;

	i = 0;
	philos = malloc(sizeof(t_philo) * number_of_philosophers);
	sem_unlink("number_forks");
	sem_unlink("one_at_time");
	sem_unlink("print_sem");

    if ((forks = sem_open("number_forks", O_CREAT, S_IRWXG, number_of_philosophers)) == SEM_FAILED ||
	(one_at_time = sem_open("one_at_time", O_CREAT, S_IRWXG, 1)) == SEM_FAILED ||
	(g_print_sem = sem_open("print_sem", O_CREAT, S_IRWXG, 1)) == SEM_FAILED)
    {
        write(1, "failed to open semaphore\n", 26);
        STATE = 0;
    }
	while (i < number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].last_eat = get_time_stamp();
		i++;
	}
	// p_status = malloc(sizeof(char) * number_of_philosophers);
	// ft_bzero(p_status, number_of_philosophers);

}

void	run()
{
	int i;

	if (STATE == 0)
		return ;
	i = 0;
	// g_print_mutex = PTHREAD_MUTEX_INITIALIZER;
	// forks = sem_open("number_forks", O_CREAT, S_IRWXG, 5);
	while (i < number_of_philosophers)
	{
		pthread_create(&philos[i].thread, NULL, philosopher, (void *) &philos[i]);
		i++;
	}
	pthread_create(&shinigami, NULL, check_die, NULL);
	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(shinigami, NULL);
}

void	finit()
{

	// free(forks);
	sem_unlink("number_forks");
	sem_unlink("one_at_time");
	sem_unlink("print_sem");
	// sem_post(forks);
	sem_close(forks);
	sem_close(one_at_time);
	sem_close(g_print_sem);
	free(philos);
	// sem_post(forks);
}


int main(int argc, char *argv[])
{
	init(argv);
	run();
	finit();
	return (0);
}

// void	*philosopher(void *philo)
// {
// 		printf("ENTERED\n");

// 	sem_wait(forks);
// 	printf("CALLED\n");
// 	 while (1);
// 	sem_post(forks);
// 	return (NULL);
// }


// int main()
// {
// 	t_philo 		philos[5];
// 	sem_unlink("sem_philo");
// 	forks = sem_open("number_forks", O_CREAT, S_IRWXG, 5);
// 	// 	sem_close(sem);
// 	for (int i = 0; i < 5 ; i++)
// 		pthread_create(&philos[i].thread, NULL, philosopher, (void *) &philos[i]);
// 	for (int i = 0; i < 5 ; i++)
// 		pthread_join(philos[i].thread, NULL);
	
// 	return (0);
// }

// pthread_t t;

// int g = 0;
// void	*test()
// {
// 	while (1)
// 	{
// 		if (g == 1032590)
// 			pthread_detach(t);
// 		printf("%d\n", g++);
// 	}
// 	return NULL;
// }
// int main()
// {
// 	pthread_create(&t, NULL, test, NULL);
// 	pthread_join(t, NULL);
// 	return (0);
// }