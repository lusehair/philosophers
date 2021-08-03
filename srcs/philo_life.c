#include "../includes/philo.h"


/*
// if one fork is avalaible : return 0 or 1 if is doesn't 
*/ 


int     if_take_one_fork(t_table *table, int index)
{
    int ret; 

    ret = 0;

    if (g_isDead == true)
        return (-1);
    if (table->philos[index].PIO == 'I')
        ret = pthread_mutex_lock(table->philos[index].forkRight); 
    else
        ret = pthread_mutex_lock(table->philos[index].forkLeft);     
    if (ret == 0)
        monitor(table, index, "has taken a fork");
    return (ret);
}




int     if_take_two_fork(t_table *table, int index)
{
    int ret; 

    ret = 0;
    if (g_isDead == true)
        return(-1);
    if (table->philos[index].PIO == 'I')
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
    if (table->data.maxEat != - 1)
    {
        table->philos[index].numEat++;
        if (table->philos[index].numEat == table->data.maxEat + 1)
            return (table->data.maxEat);
    }
    monitor(table,index, "is eating");
    table->philos[index].lastEat = instanttime(table);
    safe_sleep(table,'E');
    ret += pthread_mutex_unlock(fork1);
    ret += pthread_mutex_unlock(fork2);
    return (ret);
}





int     is_sleep(t_table *table, int index)
{
    monitor(table,index,"is sleeping");
    safe_sleep(table, 'S');
    return(0);
}


/*
// philosopher life with all process functions 
// ret = -1 if the philo died;
// ret = 1 if philo as eat enought 
*/ 

void     *philo_life(void *tab)
{
    int index;
    t_human *human;
    t_table *table;

    human = tab;
    table = human->table; 
    index = human->index;
    ft_free_safe(tab);
    if (table->philos[index].PIO == 'P')
        is_sleep(table, index);
    table->philos[index].lastEat = instanttime(table);
    while (g_isDead == false)
    {
        monitor(table, index, "is thinking");
        if_take_one_fork(table,index);
        if_take_two_fork(table,index);
        is_eating(table, index); 
        is_sleep(table,index);
    }
    pthread_mutex_unlock(table->philos[index].forkRight);
    pthread_mutex_unlock(table->philos[index].forkLeft);
    return (NULL);
}
