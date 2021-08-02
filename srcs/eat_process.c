#include "../includes/philo.h"

/*
// if one fork is avalaible : return 0 or 1 if is doesn't 
*/ 


int     if_take_one_fork(t_table *table, int index)
{
    int ret; 

    ret = 0;

    if (g_isDead == true)
        return(-1);
    if(table->philos[index].PIO == 'I')
        ret = pthread_mutex_lock(table->philos[index].forkRight); 
    else
        ret = pthread_mutex_lock(table->philos[index].forkLeft);     
    if(ret == 0)
        monitor(table, index, "took one fork");
    return (ret);
}




int     if_take_two_fork(t_table *table, int index)
{
    int ret; 

    ret = 0;
    if(g_isDead == true)
        return(-1);
    if(table->philos[index].PIO == 'I')
        ret = pthread_mutex_lock(table->philos[index].forkLeft); 
    else
        ret = pthread_mutex_lock(table->philos[index].forkRight);     
    return (ret);
}

int     is_eating(t_table *table, int index)
{
    pthread_mutex_t *fork1;
    pthread_mutex_t *fork2;
    int ret; 

    ret = 0;
    fork1 = table->philos[index].forkLeft;
    fork2 = table->philos[index].forkRight;
    if(table->data.maxEat != -1)
    {
        table->philos[index].numEat++;
        if(table->philos[index].numEat == table->data.maxEat + 1)
            return(table->data.maxEat);
    }
    monitor(table,index, "is eating");
    safe_sleep(table,'E');
    ret += pthread_mutex_unlock(fork1);
    ret += pthread_mutex_unlock(fork2);
    table->philos[index].lastEat = instanttime(table);
    return (ret);
}

