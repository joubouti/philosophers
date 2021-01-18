#include "philo_one.h"

void	ft_write(char *str, int len, char *buff, int *pos)
{
	int i;

	i = 0;
	while (i < len)
	{
		buff[*pos + i] = str[i];
		i++;
	}
	buff[*pos + i] = 0;
	*pos += i;
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putnbr(long n, char *buff, int *pos)
{
	char c;

	if (n == 0)
	{
		ft_write("0", 1, buff, pos);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		ft_write("-", 1, buff, pos);
	}
	if (n / 10)
		ft_putnbr(n / 10, buff, pos);
	c = n % 10 + 48;
	ft_write(&c, 1, buff, pos);

}

micro_second_t	get_time_stamp()
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return tv.tv_sec*(micro_second_t)1000000+tv.tv_usec;
}

void	ft_putstr(char *s, char *buff, int *pos)
{
	ft_write(s, ft_strlen(s), buff, pos);
}

void	*ft_bzero(void *s, size_t n)
{
	return (memset(s, 0, n));
}

void	ft_print_status(t_philo *philo)
{
	char	buff[64];
	int		pos;

	pos = 0;
	pthread_mutex_lock(&print_mutex);
	pthread_mutex_unlock(&print_mutex);
	// micro_second_t time = get_time_stamp();
	ft_putnbr((get_time_stamp() - g_start_time) / 1000, buff, &pos);
	ft_putstr(" ", buff, &pos);
	ft_putnbr(philo->id, buff, &pos);
	if (philo->stat == TAKE_FORKS)
		ft_putstr(" has taken the forks\n", buff, &pos);
	else if (philo->stat == EATING)
		ft_putstr(" is eating\n", buff, &pos);
	else if (philo->stat == SLEEPING)
		ft_putstr(" is sleeping\n", buff, &pos);
	else if (philo->stat == THINKING)
		ft_putstr(" is thinking\n", buff, &pos);
	else if (philo->stat == PUTS_FORKS)
		ft_putstr(" has put the forks\n", buff, &pos);
	else if (philo->stat == DIED)
	{
		// write(1, " ", 1);
		// ft_putnbr(get_time_stamp() - philo->last_eat);
		// write(1, " ", 1);
		// ft_putnbr();
		ft_putstr(" died\n", buff, &pos);
		pthread_mutex_lock(&print_mutex);
	}
	write(1, buff, ft_strlen(buff));
	// pthread_mutex_unlock(&print_mutex);
}