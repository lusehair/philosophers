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
    int maxEatPhilo;

    i = 0;
    maxEatPhilo = 1;
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
                if((table->philos[i].numEat > table->data.maxEat) && table->data.maxEat != -1)
                {
                    maxEatPhilo++;
                }
                i++;
            }
            i = 0;
    }
    return (true);
}