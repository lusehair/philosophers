/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusehair <lusehair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 20:01:21 by lusehair          #+#    #+#             */
/*   Updated: 2021/08/16 15:09:30 by lusehair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "philo.h"

bool	g_isDead;


typedef struct s_philo
{
	int				index;
	pthread_mutex_t	*forkLeft;
	pthread_mutex_t	*forkRight;
	int				numEat;
	unsigned long	lastEat;
	char			PIO;
	pthread_t		tPhilo;
	pthread_mutex_t muteat;
}				s_philo;

typedef struct s_data
{
	int				elements;
	unsigned long	timeDie;
	unsigned long	timeEat;
	unsigned long	timeSleep;
	int				maxEat;
	unsigned long	realtime;
	int 			isdead;
	pthread_mutex_t	monitor;
	pthread_mutex_t	time;
	pthread_mutex_t mdead;
}				s_data;

typedef struct s_table
{
	s_data			data;
	pthread_mutex_t	*forks;
	s_philo			*philos;
	int				countmax;
}				s_table;

typedef struct s_human
{
	s_table	*table;
	int		index;
}	s_human;

#endif 
