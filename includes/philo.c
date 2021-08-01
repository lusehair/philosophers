#include <stdio.h> 
#include <pthread.h> 
#include <unistd.h> 

void     *first_thread(void *arg)
{
    int i; 

    i = 0;
    while(i < 20)
    {
        printf("First Thread : %d and the %s\n", i, (char*)arg);
        usleep(300);
        i++;
    }
    printf("End of first thread\n");
}

void     *second_thread(void *arg)
{
    int i; 

    i = 0;
    while(i < 30)
    {
        printf("Second Thread : %d and the %s\n", i, (char*)arg);
        i++;
        usleep(300);
    }
    printf("End of second thread\n");

}


int     main(int ac, char **av)
{

    pthread_t first;
    pthread_t second; 
    void *ret;; 
    void *ret2;
    int i; 
    void *str = (void*) "Hello One";
    
    i = 0;
    printf("Hello\n");
    pthread_create(&first, NULL, &first_thread, str); 
    pthread_join(first, &ret);
    pthread_create(&second, NULL, &second_thread, str); 
    pthread_join(second, &ret2);
    while(i++ < 30)
        printf("The main function\n");    
    // if (ret != 0)
    //     printf("error");
    
}

// /*thread function definition*/
// void* threadFunction(void* args)
// {
//     while(1)
//     {
//         printf("I am threadFunction.\n");
//     }
// }
// int main()
// {
//     /*creating thread id*/
//     pthread_t id;
//     int ret;
  
//     /*creating thread*/
//     ret=pthread_create(&id,NULL,&threadFunction,NULL);
//     if(ret==0){
//         printf("Thread created successfully.\n");
//     }
//     else{
//         printf("Thread not created.\n");
//         return 0; /*return from main*/
//     }
  
//     while(1)
//     {
//       printf("I am main function.\n");      
//     }
  
//     return 0;
// }
