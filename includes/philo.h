#ifndef PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# define PHILO_H
# define USAGE "Usage: ./philo philo_num time_to_die time_to_eat time_to_sleep\n"
# define OPT "Optional arg: [number_of_time_each_philo_will_eat]\n"
# define EF "🍴"
# define ES "💤"
# define DD "💀"
typedef struct s_philo
{
	int				dead;
	int				index;
	size_t			l_eat;
	pthread_mutex_t	fork;
	pthread_t		th;
	struct s_table	*table;
}t_philo;

typedef struct s_table
{
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	int				dead;
	t_philo			*philo;
	unsigned long	time;
	pthread_t		th_id;
	unsigned long	t_philo;
	unsigned long	t_to_die;
	unsigned long	t_to_eat;
	unsigned long	t_to_sleep;
	unsigned long	t_food;
}t_table;
void			printer(t_philo philo, int status, int index);
t_table			fill_struct(int argc, char **argv, t_table *table);
unsigned long	ft_atoi(const char *str);
int				validate_args(t_table *table, int argc);
long			get_time(void);
#endif