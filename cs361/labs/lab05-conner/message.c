#include <stdio.h>

#include "message.h"

/*--------------------------------------------------------------------
  Print a message buffer
----------------------------------------------------------------------*/
void printMsg( msgBuf *m )
{
  printf( "{ type=%ld , { sender pid=%ld, %3d %c %3d , result=%6d } }\n"
  , m->mtype , (long) m->info.sender
  , m->info.num1 , m->info.operation
  , m->info.num2 , m->info.result ) ;
}
