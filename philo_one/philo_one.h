#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef unsigned long ulong;
typedef struct	s_philo
{
	int			id;
	pthread_t	thread;
	ulong		last_eat;
}				t_philo;
enum status{TAKE_FORKS, EATING, SLEEPING, THINKING, DIED};

pthread_mutex_t	g_print_mutex;


void	ft_putnbr(long n);
void	ft_putstr(char *str);
ulong	get_time_stamp();
void	*ft_bzero(void *s, size_t n);
void	print_status(int philo, int status);

#endif