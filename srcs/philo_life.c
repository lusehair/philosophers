#include "../includes/philo.h"

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
    //int fork;
    int index;
    t_human *human;
    t_table *table;

    human = tab;
    table = human->table; 
    //fork = 1;
    index = human->index;
    ft_free_safe(tab);
    if(table->philos[index].PIO == 'P')
        is_sleep(table, index);
    table->philos[index].lastEat = instanttime(table);
    while(g_isDead == false)
    {
        monitor(table, index, "is thinking");
        //fork = 1;
        //while(fork)
             if_take_one_fork(table,index);
        //fork = 1;
        //while(fork)               
            if_take_two_fork(table,index);
        is_eating(table, index); 
        is_sleep(table,index);
    }
    //printf("proper exit from %d\n", index +1);
    pthread_mutex_unlock(table->philos[index].forkRight);
    pthread_mutex_unlock(table->philos[index].forkLeft);
   
    return(NULL);
}
