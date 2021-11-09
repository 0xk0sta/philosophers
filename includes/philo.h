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
# define ET "🤔"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAG "\x1b[35m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"
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
	size_t			total_e;
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
void			printer(t_philo philo, int status, size_t in);
int				fill_struct(int argc, char **argv, t_table *table);
unsigned long	ft_atoi(const char *str);
int				validate_args(t_table *table, int argc);
long			get_time(void);
#endif