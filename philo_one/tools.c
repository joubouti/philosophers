#include "philo_one.h"


void	ft_putnbr(long n)
{
	char c;

	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	// if (n == -2147483648)
	// {
	// 	// write(1, "-2147483648", 11);
	// 	return ;
	// }
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

ulong	get_time_stamp()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return tv.tv_sec*(ulong)1000000+tv.tv_usec;
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

void	print_status(int philo, int status)
{
	pthread_mutex_lock(&g_print_mutex);
	ulong time = get_time_stamp();
	ft_putnbr(get_time_stamp());
	ft_putstr(" ");
	ft_putnbr(philo);
	if (status == TAKE_FORKS)
		ft_putstr(" has taken a fork\n");
	else if (status == EATING)
		ft_putstr(" is eating\n");
	else if (status == SLEEPING)
		ft_putstr(" is sleeping\n");
	else if (status == THINKING)
		ft_putstr(" is thinking\n");
	else if (status == DIED)
		ft_putstr(" died\n");
	else if (status == 5)
		ft_putstr(" tries to take forks\n");
	pthread_mutex_unlock(&g_print_mutex);
}