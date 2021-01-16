#include "philo_three.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putnbr(long n)
{
	char c;

	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		write(1, "-", 1);
	}
	if (n / 10)
		ft_putnbr(n / 10);
	c = n % 10 + 48;
	write(1, &c, 1);
}

micro_second_t	get_time_stamp()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return tv.tv_sec*(micro_second_t)1000000+tv.tv_usec;
}

void	ft_putstr(char *s)
{
	while (*s)
		write(1, s++, 1);
}

void	*ft_bzero(void *s, size_t n)
{
	return (memset(s, 0, n));
}

void	ft_print_status(t_philo *philo)
{
	// pthread_mutex_lock(&print_mutex);
	sem_wait(print_sem);
	// micro_second_t time = get_time_stamp();
	ft_putnbr((get_time_stamp() - g_start_time) / 1000);
	ft_putstr(" ");
	ft_putnbr(philo->id);
	if (philo->stat == TAKE_FORKS)
		ft_putstr(" has taken the forks 🍴\n");
	else if (philo->stat == EATING)
		ft_putstr(" is eating 🍝\n");
	else if (philo->stat == SLEEPING)
		ft_putstr(" is sleeping 😴\n");
	else if (philo->stat == THINKING)
		ft_putstr(" is thinking 🤔\n");
	else if (philo->stat == PUTS_FORKS)
		ft_putstr(" has put the forks 🍽\n");
	else if (philo->stat == DIED)
	{
		// write(1, " ", 1);
		// ft_putnbr(get_time_stamp() - philo->last_eat);
		// write(1, " ", 1);
		// ft_putnbr();
		ft_putstr(" died\n");
		return ;
	}
	sem_post(print_sem);

}