/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusehair <lusehair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:53:08 by lusehair          #+#    #+#             */
/*   Updated: 2021/08/17 14:04:38 by lusehair         ###   ########.fr       */
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
	else
		endSleep = instanttime(table) + table->data.timeEat;
	while (instanttime(table) < endSleep)
		usleep(300);
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
			if ((instanttime(table) - m_numeat(table, i, 'R', 'E')
					> table->data.timeDie && (m_numeat(table, i, 'R', 'N') != table->data.maxEat)))
			{
				if(!(table->data.maxEat != -1 && m_numeat(table, i, 'R', 'N') != table->data.maxEat))
				{
					monitor(table, i, "died");
					return (1);
				}
			}
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
