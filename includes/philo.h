/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucassehairi <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:15:57 by lucasseha         #+#    #+#             */
/*   Updated: 2021/08/04 15:16:00 by lucasseha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> 
# include <pthread.h> 
# include <unistd.h> 
# include <stdlib.h> 
# include <sys/time.h>
# include <stdbool.h> 
# include "structs.h"

/*
// INIT.C
*/

void			fork_dispatch(t_table *table);
t_philo			*init_philos(t_data data);
int				init_data(t_data *data, int ac, char **av);
pthread_mutex_t	*init_forks(t_data data);

/*
// TOOLS.C
*/

unsigned long	realtime(void);
unsigned long	instanttime(t_table *table);
void			safe_sleep(t_table *table, char type);
bool			watcher(t_table *table);
void			monitor(t_table *table, int index, char *msg);

/*
// PHILO_LIFE.C
*/

int				if_take_one_fork(t_table *table, int index);
int				if_take_two_fork(t_table *table, int index);
int				is_eating(t_table *table, int index);
int				is_sleep(t_table *table, int index);
void			*philo_life(void *tab);

/*
// LIBFT.C
*/

int				ft_atoi(const char *str);
size_t			ft_strlen(const char *str);
void			*ft_free_safe(void *ptr);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_isdigit(int c);

/*
// MAIN.C
*/

int				destroy(t_table *table);
int				arg_checker(int ac, char**av);
int				value_checker(int ac, char **av);
int				diner_launcher(t_table *table);

#endif 
