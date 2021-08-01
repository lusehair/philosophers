#include "../includes/philo.h"

/*
// Give instant time in ms since the startong of the program. 
*/ 

unsigned long realtime(void)
{
   struct timeval current;
   unsigned long ret;
  // long long int temp;
   current = (struct timeval){0};
   gettimeofday(&current,NULL);
   ret = (current.tv_sec * 1000) + (current.tv_usec / 1000);
   return(ret);
}

unsigned long instanttime(t_table *table)
{
    unsigned long ret; 
    ret = realtime() - table->data.realtime; 
    return(ret);
}


// /* DEV TOOLS */ 

// void    show_data(t_table *table)
// {
//     printf("The Time to die : %ld\n The Time to die : %ld\n The Time to die : %ld\n")
// }




/*
// Give the index of the current thread. use this function just one time, at the init of thread. 
*/ 

int     ret_index(t_table *table)
{
    int ret; 

    ret = 0;
    
    while(ret < table->data.elements)
    {
        if(table->philos[ret].state == notinit)
        {
            printf("Is The Ret %d\n", ret);
            return (ret);
        }
        ret++;
    }
    return(ret);
}

void    safe_sleep(t_table *table, char type)
{
    unsigned long endSleep; 

    if(type == 'S')
        endSleep = instanttime(table) + table->data.timeSleep; 
    else
        endSleep = instanttime(table) + table->data.timeEat; 
    while(instanttime(table) < endSleep)
        usleep(100);
            
}

bool    dead_or_not(t_table *table, int index, unsigned long time)
{
    unsigned long last = table->philos[index].lastEat;
    
    if(time - last >= table->data.timeDie)
    {
        philo_end_eat(table,index);
        printf("This is the time : %ld and the last : %ld and the timedie %ld\n", time, last, table->data.timeDie);
        //printf("The ")
        if(g_isDead == false)
            printf("%ld Philo %d died\n", instanttime(table),index );
        g_isDead = true; 
        return (true);
    }
    else if(g_isDead == true)
    {
        philo_end_eat(table, index);
        return(true);
    }
    else
        return(false);
}

void     monitor(t_table *table, int index, char *msg)
{
    pthread_mutex_lock(&table->data.monitor);
    printf("%ld ms philo %d %s\n", instanttime(table), index+1, msg);      
    
  
    if((ft_strncmp(msg,"is dead", ft_strlen(msg))) != 0)
        pthread_mutex_unlock(&table->data.monitor);
}

bool    watcher(t_table *table)
{
    int i; 
    i = 0;

    while(g_isDead == false)
    {
            while(i < table->data.elements)
            {
                if((instanttime(table) - table->philos[i].lastEat > table->data.timeDie))
                {
                    g_isDead = true;
                    monitor(table,i,"is dead");
                    break;
                }
                if(table->philos[i].numEat > table->data.maxEat)
                {
                    g_isDead = true;
                    return (true);
                }
                i++;
            }
            i = 0;
    }
    return (true);
}