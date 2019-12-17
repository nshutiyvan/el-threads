#include <pthread.h>
 #include <stdio.h>
 #include <stdlib.h>

 
 int COUNT_LIMIT=3;
 int  count = 0;

 pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
 pthread_cond_t count_finish;

 void* thread_count(void *t) 
 {
   int pid = (int)t;

   for (int i=0; i<COUNT_LIMIT; i++) {
     pthread_mutex_lock(&count_mutex);
     count++;
     if (count == COUNT_LIMIT) {
       pthread_cond_signal(&count_finish);
       }
     printf("Thread:%d, count = %d\n", 
	    pid, count);
     pthread_mutex_unlock(&count_mutex);
     sleep(1);
     }
   pthread_exit(NULL);
 }

 void *watch_count(void *t) 
 {
   pthread_mutex_lock(&count_mutex);
   while (count<COUNT_LIMIT) {
     pthread_cond_wait(&count_finish, &count_mutex);
     }
   pthread_mutex_unlock(&count_mutex);
   pthread_exit(NULL);
 }

 int main (int argc, char *argv[])
 {
   int t1=1, t2=2, t3=3;
   pthread_t threads[3];
   pthread_attr_t attr;

   pthread_cond_init (&count_finish, NULL);

   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
   pthread_create(&threads[0], &attr, watch_count, (void *)t1);
   pthread_create(&threads[1], &attr,thread_count, (void *)t2);
   pthread_create(&threads[2], &attr,thread_count, (void *)t3);

   /* Wait for all threads to complete */
   for (int i=0; i<3; i++) {
     pthread_join(threads[i], NULL);
   }
   /* Clean up and exit */
   pthread_attr_destroy(&attr);
   pthread_mutex_destroy(&count_mutex);
   pthread_cond_destroy(&count_finish);
   pthread_exit(NULL);

 } 