/* mySock.c - utility sunction for socket programming */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include "mySock.h"
#define MAXMSGLEN 256
/*------------------------------------------------------------------------
 * Error Handling Functions
 *----------------------------------------------------------------------*/
void err_sys(const char* x) 
{ 
    fflush( stderr ) ;
    perror(x); 
    exit(1); 
}

void err_quit(const char* x) 
{ 
    fflush( stderr ) ;
    fputs( x , stderr ) ; 
    exit(1); 
}

/*------------------------------------------------------------------------
 * clientUDPsock - allocate a UDP socket & connect to default destination
 *------------------------------------------------------------------------
 *
 *
 * Arguments:
 *      host      - name of host to which connection is desired
 *      service   - service associated with the desired port
 */
int clientUDPsock(const char *host, const char *service )
{
    struct addrinfo    *ainfo;  /* pointer to address information entry */
    struct addrinfo    hints ,  /* used to filter gai search results    */
                       *rp ;    /* used to iterate gai search results   */
	int	s, type;	            /* socket descriptor and socket type	*/
	char   msg[MAXMSGLEN] ;     /* used with snprintf                   */
	int    errCode ;
         
    /* Allocate a socket */
	s = socket( AF_INET, SOCK_DGRAM , 0 ) ;
	if (s < 0)
		err_sys( "connectsock() can't create socket" ) ;
    
    /* Prepare hints to filter results of getaddrinfo()  */
    memset( &hints , 0 , sizeof( struct addrinfo ) ) ;

    hints.ai_family   = AF_INET ;        /* Allow IPv4 ONLY      */
    hints.ai_socktype = SOCK_DGRAM ;
    hints.ai_flags    = 0 ;
    hints.ai_protocol = IPPROTO_UDP ;
    
    /* Map host name (possibly in dotted decimal) to IP address  */
    errCode = getaddrinfo( host , service , &hints , &ainfo ) ;

    if( errCode )
    {
        snprintf( msg , MAXMSGLEN , "getaddrinfo() failed: %s\n" ,
                  gai_strerror( errCode ) ) ;
        err_quit( msg ) ;   
    }
    else
    {   /* Iterate through the server's IPs trying to connect */
        for (rp = ainfo; rp != NULL; rp = rp->ai_next )
            if ( connect( s, rp->ai_addr, rp->ai_addrlen ) == 0 )
                break;                  /* Success */ 

        if ( rp == NULL )               /* No address succeeded */    
            err_quit( "Could not connect; No gai() address succeeded\n");
    }

    freeaddrinfo( ainfo ) ;
    
	return s;
}

/*------------------------------------------------------------------------
 * serverUDPsock - allocate & bind a server socket using UDP
 *------------------------------------------------------------------------
 * Arguments:
 *      port   - port# associated with the desired service
 */

int serverUDPsock(const unsigned short port)
{	
    struct sockaddr_in sin;	 /* an Internet endpoint address  */
    int	s;                   /* socket descriptor         	  */
    char   msg[MAXMSGLEN] ;  /* used with snprintf            */
    
    memset( (void *) &sin, 0 , sizeof(sin) );
    sin.sin_family      = AF_INET;
    sin.sin_addr.s_addr = htonl( INADDR_ANY );
    sin.sin_port        = htons( port + BASEPORT) ;

    /* Allocate a socket */
    s = socket( AF_INET, SOCK_DGRAM  , 0 ) ;
    if (s < 0)
        err_sys( "passivesock() can't create socket" ) ;

    fprintf(stderr , "Created socket with descriptor %d\n" , s);
    /* Bind the socket */
    if ( bind( s, (SA *) &sin, sizeof(sin) ) < 0 )
    {
        snprintf( msg , MAXMSGLEN , 
                  "passivesock() can't bind to port %d", port ) ;
        err_sys( msg ) ;
    }
    fprintf(stderr , "Bound socket %d to port %d\n" , s , ntohs(sin.sin_port) );    
	return s;
}

