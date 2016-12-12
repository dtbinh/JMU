 /*
 This is an example of using semaphores to solve
 the rendezvous problem.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <pthread.h>
 #include <semaphore.h>

 #define THREADS 8

 void * p( void * ) ;
 sem_t s[THREADS+1] ; /* we will not use s[0] */

 int main()
 {
   int i ;
   pthread_t tid ;

   for( i=1 ; i<= THREADS ; i++)
   {
     sem_init( s+i , /* same as & s[i] */
	       0 , /* local to this process */
	       0 /* initial value */
     ) ;
     pthread_create( &tid, NULL, p , (void *) i );
   }

   printf( "This is the Initial Thread. Creating 8 Threads\n");

   sem_wait( s+8 ) ;
   printf( "This is the Initial Thread. All Threads have exited\n");

   return 0;
 }

 /* --------------------------------------------------------- */

 #define WAISTCYCLES 500000000U
 #define SPIN for( k=0 ; k<WAISTCYCLES ; k++ )

 /*
 This is a simulation of the process diagram
 on slide 38 module 06-Concurrency
 */
 void * p( void * arg )
 {
   unsigned k , mynum ;
   mynum = ( unsigned ) arg ;

   pthread_detach( pthread_self() );

   switch( mynum )
   {
     case 1:
	 printf("Thread %d started\n", mynum);
	 SPIN ;
	 printf("Thread %d ended\n", mynum);
	 sem_post( & s[1] /* or simply s+1 */ );
	 sem_post( s+1 );
	 sem_post( s+1 );
	 break ;

     case 2:
	 sem_wait( s+1 ) ;
	 printf("Thread %d started\n", mynum);
	 SPIN ;
	 printf("Thread %d ended\n", mynum);
	 sem_post( s+2 );
	 sem_post( s+2 );
	 break ;

     case 3:
	 sem_wait( s+2 ) ;
	 printf("Thread %d started\n", mynum);
	 SPIN ;
	 printf("Thread %d ended\n", mynum);
	 sem_post( s+3 );
	 break ;

     case 4:
	 sem_wait( s+2 ) ;
	 printf("Thread %d started\n", mynum);
	 SPIN ;
	 printf("Thread %d ended\n", mynum);
	 sem_post( s+4 );
	 break ;

     case 5:
	 sem_wait( s+1 ) ;
	 printf("Thread %d started\n", mynum);
	 SPIN ;
	 printf("Thread %d ended\n", mynum);
	 sem_post( s+5 );
	 break ;

     case 6:
	 sem_wait( s+4 ) ;
	 sem_wait( s+5 ) ;
	 printf("Thread %d started\n", mynum);
	 SPIN ;
	 printf("Thread %d ended\n", mynum);
	 sem_post( s+6 );
	 break ;

     case 7:
	 sem_wait( s+1 ) ;
	 printf("Thread %d started\n", mynum);
	 SPIN ;
	 printf("Thread %d ended\n", mynum);
	 sem_post( s+7 );
	 break ;

     case 8:
	 sem_wait( s+3 ) ;
	 sem_wait( s+6 ) ;
	 sem_wait( s+7 ) ;
	 printf("Thread %d started\n", mynum);
	 SPIN ;
	 printf("Thread %d ended\n", mynum);
	 sem_post( s+8 );
	 break ;
   };

   pthread_exit( NULL ) ;
 }
