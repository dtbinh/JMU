#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h> 
#include <errno.h>

#include "message.h"
#include "mySock.h"
#define MAXBUFLEN   256

/*------------------------------------------------------------------------
 * main - UDP client for DAYTIME service that prints the resulting time
 *----------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
    char	*host    = "localhost";    /* host to use if none supplied	*/
    char	*service = "80";      /* default service name	        */
    char    *msg     = "Bla Bla Bla" ;
    char    timeStr[MAXBUFLEN];        /* time string   */ 
    int	    s;                         /* socket descriptor */
    msgBuf from_msg, to_msg;
    int factory_ID, duration, capacity, num_iters, total_produced;

    //A switch for the client
    switch (argc) 
      {
          case 1:
              break;
          case 3:
              service = argv[2];
              /* FALL THROUGH */
          case 2:
              host = argv[1];
              break;
          default:
              fprintf(stderr, "usage: %s [host [port]]\n" , argv[0] );
              exit(1);
      }

    s = clientUDPsock( host , service );  
    /* socket will always send to host:service */
    /* Therefore, use  in sendto( .... , NULL , 0) */
    
    to_msg.info.factory_ID = 1234; // Nonsense number. This process needs an ID from the server
    sendto(s, (void *) &to_msg, sizeof(to_msg), 0, NULL, 0);
    
    if (recvfrom(s, (void*) &from_msg, sizeof(from_msg), 0, NULL , 0) <= 0)
        err_sys( "Failed to get the message from the server" );

    factory_ID = from_msg.info.factory_ID;
    duration = from_msg.info.duration;
    capacity = from_msg.info.capacity;
    num_iters = 0;
    total_produced = 0;
    printf("Line %d started. Duration: %d Capacity: %d\n", factory_ID, duration, capacity);

    while (from_msg.info.produce) // if this is zero, stop
      {
        //Sleeps for the durration
        sleep (duration);

        to_msg.info.factory_ID = factory_ID;
        to_msg.info.capacity = capacity;
        to_msg.info.duration = duration;
        to_msg.info.produce = from_msg.info.produce;

        printf("Line %d produced %d items\n", factory_ID, from_msg.info.produce);

        sendto(s, (void *) &to_msg, sizeof(to_msg), 0, NULL, 0);
        if (recvfrom(s, (void*) &from_msg, sizeof(from_msg), 0, NULL , 0) <= 0)
            err_sys( "Failed to get the message from the server" );
        num_iters++;
        total_produced += from_msg.info.produce;
      }

    printf("Line %d has completed %d iterations, %d items in %d seconds\n", factory_ID,
       num_iters, total_produced, num_iters * duration);
    printf("Line %d has completed its portion of the order\n", factory_ID);

    //exits the program
    exit(0);
}
