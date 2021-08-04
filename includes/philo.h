#ifndef PHILO_H
# define PHILO_H

#include <stdio.h> 
#include <pthread.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/time.h>
#include <stdbool.h> 
#include "structs.h"


/*
// INIT.C 
*/ 

int     init_data(t_data *data, int ac, char **av);
pthread_mutex_t     *init_forks(t_data data);
t_philo     *init_philos(t_data data);
int     diner_launcher(t_table *table);
void    fork_dispatch(t_table *table);
int     arg_checker(int ac, char**av);
int     value_checker(int ac, char **av);


/*
// EAT_PROCESS.C 
*/ 

int     if_take_one_fork(t_table *table, int index);
int     if_take_two_fork(t_table *table, int index);
int     is_eating(t_table *table, int index);

/*
// TOOLS.C 
*/ 

unsigned long realtime();
unsigned long instanttime(t_table *table);
int     ret_index(t_table *table);
void    safe_sleep(t_table *table, char type);
bool    dead_or_not(t_table *table, int index, unsigned long time);
bool    watcher(t_table *table);
void     monitor(t_table *table, int index, char *msg);



/*
// PHILO_LIFE.C 
*/ 

int     is_sleep(t_table *table, int index);
int     philo_dead(t_table *table, int index);
void     *philo_life(void *tab);
void    philo_end_eat(t_table *table, int index);


/*
// LIBFT.C
*/ 

int     ft_atoi(const char *str);
size_t		ft_strlen(const char *str);
void	*ft_free_safe(void *ptr);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int c);



int     destroy(t_table *table);

#endif 