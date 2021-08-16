/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusehair <lusehair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 15:15:57 by lucasseha         #+#    #+#             */
/*   Updated: 2021/08/16 18:32:45 by lusehair         ###   ########.fr       */
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

void			fork_dispatch(s_table *table);
s_philo			*inis_philos(s_data data);
int				inis_data(s_data *data, int ac, char **av);
pthread_mutex_t	*init_forks(s_data data);

/*
// TOOLS.C
*/

unsigned long	realtime(void);
unsigned long	instanttime(s_table *table);
void			safe_sleep(s_table *table, char type);
bool			watcher(s_table *table);
void			monitor(s_table *table, int index, char *msg);

/*
// PHILO_LIFE.C
*/

int				if_take_one_fork(s_table *table, int index);
int				if_take_two_fork(s_table *table, int index);
int				is_eating(s_table *table, int index);
int				is_sleep(s_table *table, int index);
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
// MUTEX.C
*/

int             m_isdead(s_table *table, char mode);
int		        m_numeat(s_table *table, int index, char mode, char arg);

/*
// MAIN.C
*/

int				destroy(s_table *table);
int				arg_checker(int ac, char**av);
int				value_checker(int ac, char **av);
int				diner_launcher(s_table *table);

#endif 
