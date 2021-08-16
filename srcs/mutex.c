/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusehair <lusehair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 18:30:45 by lusehair          #+#    #+#             */
/*   Updated: 2021/08/16 23:51:31 by lucasseha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	m_numeat(t_table *table, int index, char mode, char arg)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&table->philos[index].muteat);
	if (mode == 'R' && arg == 'N')
		ret = table->philos[index].numEat;
	else if (mode == 'R' && arg == 'E')
		ret = table->philos[index].lastEat;
	else if (mode == 'W' && arg == '+')
		table->philos[index].numEat++;
	else if (mode == 'W' && arg == '-')
		table->philos[index].numEat = -1;
	else if (mode == 'W' && arg == 'D')
		table->philos[index].numEat = -2;
	else if (mode == 'W' && arg == 'E')
		table->philos[index].lastEat = instanttime(table);
	pthread_mutex_unlock(&table->philos[index].muteat);
	return (ret);
}

int	m_isdead(t_table *table, char mode)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&table->data.mdead);
	if (mode == 'R')
		ret = table->data.isdead;
	else
		table->data.isdead = 1;
	pthread_mutex_unlock(&table->data.mdead);
	return (ret);
}
