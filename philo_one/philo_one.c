#include "philo_one.h"

int 		STATE = 1;

int 			number_of_philosophers = 2;
ulong			time_to_die = 1000 * 1000 * 10;
ulong			time_to_eat = 1000 * 1000 * 2;
ulong			time_to_sleep = 1000 * 1000 * 4;
int				number_of_times_each_philosopher_must_eat;
t_philo 		*philos;
char			*forks;

pthread_mutex_t	mutex;


void	died(int philo)
{
	ft_putnbr(get_time_stamp());
	ft_putstr(" ");
	ft_putnbr(philo);
	ft_putstr("  is died\n");
	STATE = 0;
	exit(-1);
}

int		check_die(t_philo *philo)
{
	ulong time = get_time_stamp();
	if (time - philo->last_eat > time_to_die)
		died(philo->id);
}


int	take_forks(t_philo *philo)
{
	int lfork;

	lfork = (philo->id < number_of_philosophers) ? philo->id : 0;
	if (philo->id - 1 == lfork || forks[philo->id - 1] || forks[lfork])
		return (0);
	forks[philo->id] = 1;
	forks[lfork] = 1;
	print_status(philo->id, TAKE_FORKS);
	return (1);
}

void	put_forks(t_philo *philo)
{
	int lfork;

	lfork = (philo->id < number_of_philosophers) ? philo->id : 0;
	forks[philo->id] = 0;
	forks[lfork] = 0;
}

void	sleeping(t_philo *philo)
{
	print_status(philo->id, SLEEPING);
	usleep(time_to_sleep);
	check_die(philo);
}

void	thinking(t_philo *philo)
{
	print_status(philo->id, THINKING);
}



void	eat(t_philo *philo)
{
	ulong time = get_time_stamp();
	print_status(philo->id, EATING);
	while (get_time_stamp() < (time + time_to_eat))
		;
	philo->last_eat = get_time_stamp();
	// 	check_
}

void	*philosopher(void *ph)
{
	t_philo *philo = (t_philo *)ph;
	while (STATE)
	{
		thinking(philo);
		pthread_mutex_lock(&mutex);
		check_die(philo);
		if (take_forks(philo))
		{
			eat(philo);
			put_forks(philo);
		}
		pthread_mutex_unlock(&mutex);
		sleeping(philo);
	}
	return (NULL);
}

void	init(char *argv[])
{
	int i;

	i = 0;
	philos = malloc(sizeof(t_philo) * number_of_philosophers);
	while (i < number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].last_eat = get_time_stamp();
		i++;
	}
	forks = malloc(sizeof(char) * number_of_philosophers);
	ft_bzero(forks, number_of_philosophers);
}

void	run()
{
	int i;

	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_create(&philos[i].thread, NULL, philosopher, (void *) &philos[i]);
		i++;
	}
	i = 0;
	while (i < number_of_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
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