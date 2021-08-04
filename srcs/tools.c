/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusehair <lusehair@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 13:53:08 by lusehair          #+#    #+#             */
/*   Updated: 2021/08/03 13:58:00 by lusehair         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/philo.h"



unsigned long realtime(void)
{
   struct timeval current;
   unsigned long ret;
   
   current = (struct timeval){0};
   gettimeofday(&current,NULL);
   ret = (current.tv_sec * 1000) + (current.tv_usec / 1000);
   return(ret);
}

/*
// Give instant time in ms since the starting of the program is ms
*/ 

unsigned long instanttime(t_table *table)
{
    unsigned long ret; 
    pthread_mutex_lock(&table->data.time);
    ret = realtime() - table->data.realtime; 
    pthread_mutex_unlock(&table->data.time);
    return(ret);
}


/*
// Like usleep but in ms and protect against decading, S for sleep or E for 
// for eating time.
*/ 

void    safe_sleep(t_table *table, char type)
{
    unsigned long endSleep; 

    if(type == 'S')
        endSleep = instanttime(table) + table->data.timeSleep; 
    else
        endSleep = instanttime(table) + table->data.timeEat; 
    while(instanttime(table) < endSleep)
        usleep(300);
}


/*
// Protect the printing message against multi-thread and gost message
*/ 

void     monitor(t_table *table, int index, char *msg)
{
    pthread_mutex_lock(&table->data.monitor);
    if (g_isDead == false)
        printf("%ld ms philo %d %s\n", instanttime(table), index + 1, msg);      
    pthread_mutex_unlock(&table->data.monitor);
}

/*
// Monitoring on philo life
*/ 

bool    watcher(t_table *table)
{
    int i; 
    int maxEatPhilo;

    i = 0;
    maxEatPhilo = 1;
    while(g_isDead == false)
    {
            while(i < table->data.elements)
            {
                if((instanttime(table) - table->philos[i].lastEat > table->data.timeDie))
                {
                    monitor(table,i,"died");
                    g_isDead = true;
                    break;
                }
                if((table->philos[i].numEat > table->data.maxEat) && table->data.maxEat != -1)
                    maxEatPhilo++;
                i++;
                if(maxEatPhilo == table->data.elements)
                    g_isDead = true;    
            }
            i = 0;
    }
    return (true);
}