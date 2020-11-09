#include "philo_one.h"
#include <stdio.h>
int 		STATE = 1;

int 			number_of_philosophers = 3;
ulong			time_to_die = 1000 * 1000 * 7;
ulong			time_to_eat = 1000 * 1000 * 2;
ulong			time_to_sleep = 1000 * 1000 * 7;
int				number_of_times_each_philosopher_must_eat;
t_philo 		*philos;
char			*forks;
char			*p_status;
pthread_t	    shinigami;

pthread_mutex_t	mutex;


void	died(t_philo *philo, ulong time, ulong leat)
{
	int i;

	i = 0;
	// g_print_mutex = PTHREAD_MUTEX_INITIALIZER;
	STATE = 0;
	pthread_detach(shinigami);
	while (i < number_of_philosophers)
	{
		pthread_detach(philos[i].thread);
		i++;
	}
	print_status(philo->id, DIED);
	// pthread_mutex_lock(&g_print_mutex);
	// 	printf("%lu %lu %lu %d\n", time, leat, time_to_die, philo->id);
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
			if (time > leat && ((time - leat) > time_to_die) && p_status[i] != 'E')
				died(&philos[i], time, leat);
			i++;
		}
	}
	return (NULL);
}


int	take_forks(t_philo *philo)
{
	int lfork;

	lfork = (philo->id < number_of_philosophers) ? philo->id : 0;

	// print_status(philo->id, 5);
	if ((philo->id - 1) == lfork || forks[philo->id - 1] || forks[lfork])
		return (0);
	forks[philo->id - 1] = 1;
	forks[lfork] = 1;
	print_status(philo->id, TAKE_FORKS);
	return (1);
}

void	put_forks(t_philo *philo)
{
	int lfork;

	lfork = (philo->id < number_of_philosophers) ? philo->id : 0;
	forks[philo->id - 1] = 0;
	forks[lfork] = 0;
}

void	sleeping(t_philo *philo)
{
	if (p_status[philo->id - 1] != 'S')
	{
		p_status[philo->id - 1] = 'S';
		print_status(philo->id, SLEEPING);
		usleep(time_to_sleep);
	// check_die(philo);
	}
}

void	thinking(t_philo *philo)
{
	if (p_status[philo->id - 1] != 'T')
	{
		p_status[philo->id - 1] = 'T';
		print_status(philo->id, THINKING);
	}
}



void	eat(t_philo *philo)
{

	if (p_status[philo->id - 1] != 'E')
	{
		philo->last_eat = get_time_stamp();
		p_status[philo->id - 1] = 'E';

		print_status(philo->id, EATING);
		// while (get_time_stamp() < (time + time_to_eat))
		// 	;
		usleep(time_to_eat);
		philo->last_eat = get_time_stamp();
	}
	// 	check_
}

void	*philosopher(void *ph)
{
	t_philo *philo = (t_philo *)ph;
	while (STATE)
	{
		thinking(philo);
		pthread_mutex_lock(&mutex);
		// check_die(philo);
		if (take_forks(philo))
		{
			pthread_mutex_unlock(&mutex);
			eat(philo);
			put_forks(philo);
			sleeping(philo);
		}
		else
			pthread_mutex_unlock(&mutex);
		
	}
	return (NULL);
}

void	init(char *argv[])
{
	int i;

	i = 0;
	philos = malloc(sizeof(t_philo) * number_of_philosophers);

    if (pthread_mutex_init(&mutex, NULL) != 0 || pthread_mutex_init(&g_print_mutex, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        exit(1);
    }
	while (i < number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].last_eat = get_time_stamp();
		i++;
	}
	forks = malloc(sizeof(char) * number_of_philosophers);
	p_status = malloc(sizeof(char) * number_of_philosophers);
	ft_bzero(forks, number_of_philosophers);
	ft_bzero(p_status, number_of_philosophers);

}

void	run()
{
	int i;

	i = 0;
	// g_print_mutex = PTHREAD_MUTEX_INITIALIZER;
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
	free(philos);
	free(forks);
}

int main(int argc, char *argv[])
{
	init(argv);
	run();
	finit();
	return (0);
}