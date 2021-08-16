/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusehair <lusehair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:01:21 by lusehair          #+#    #+#             */
/*   Updated: 2021/08/16 13:16:02 by lusehair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "philo.h"

bool	g_isDead;


typedef struct t_philo
{
	int				index;
	pthread_mutex_t	*forkLeft;
	pthread_mutex_t	*forkRight;
	int				numEat;
	unsigned long	lastEat;
	char			PIO;
	pthread_t		tPhilo;
}				t_philo;

typedef struct t_data
{
	int				elements;
	unsigned long	timeDie;
	unsigned long	timeEat;
	unsigned long	timeSleep;
	int				maxEat;
	unsigned long	realtime;
	pthread_mutex_t	monitor;
	pthread_mutex_t	time;
}				t_data;

typedef struct t_table
{
	t_data			data;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				countmax;
}				t_table;

typedef struct t_human
{
	t_table	*table;
	int		index;
}	t_human;

#endif 
