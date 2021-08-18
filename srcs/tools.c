/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusehair <lusehair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:53:08 by lusehair          #+#    #+#             */
/*   Updated: 2021/08/18 14:10:16 by lusehair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long	realtime(void)
{
	struct timeval	current;
	unsigned long	ret;

	current = (struct timeval){0};
	gettimeofday(&current, NULL);
	ret = (current.tv_sec * 1000) + (current.tv_usec / 1000);
	return (ret);
}

unsigned long	instanttime(t_table *table)
{
	unsigned long	ret;

	pthread_mutex_lock(&table->data.time);
	ret = realtime() - table->data.realtime;
	pthread_mutex_unlock(&table->data.time);
	return (ret);
}

void	safe_sleep(t_table *table, char type)
{
	unsigned long	endSleep;

	if (type == 'S')
		endSleep = instanttime(table) + table->data.timeSleep;
	else if (type == 'K')
		endSleep = instanttime(table) + table->data.timeDie + 100;
	else if (type == 'B')
		endSleep = instanttime(table) + (table->data.timeSleep / 2);
	else
		endSleep = instanttime(table) + table->data.timeEat;
	while (instanttime(table) < endSleep)
	{
		if (m_isdead(table,'R'))
			return ;
		usleep(10);
	}

}

void	monitor(t_table *table, int index, char *msg)
{
	pthread_mutex_lock(&table->data.monitor);
	if (!(m_isdead(table, 'R')))
	{
		printf("%ld ms philo %d %s\n", instanttime(table), index + 1, msg);
	}
	pthread_mutex_unlock(&table->data.monitor);
}

bool	watcher(t_table *table)
{
	int	i;

	while (!(m_isdead(table, 'R')))
	{
		i = 0;
		while (i < table->data.elements)
		{
			if (the_death(table, i))
				return (1);
			if (m_numeat(table, i, 'R', 'N') == -1 && table->data.maxEat != -1)
			{	
				table->countmax++;
				m_numeat(table, i, 'W', 'D');
			}
			i++;
			if ((table->countmax == table->data.elements) && (table->data.maxEat
					!= -1))
				m_isdead(table, 'W');
		}
	}
	return (m_isdead(table, 'W'));
}
