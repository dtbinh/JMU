#include <stdio.h>
#include "message.h"

/*
 * Prints a message buffer
 */

void
printMsg(msgBuf *m)
{
  if (m->mtype == 1)
  {
    printf("factory_ID: %d capacity: %d num_parts: %d duration: %d\n", m->info.factory_ID);
  }
  else if (m->mtype == 2)
  {
  }
  else
  {
  }
	printf( "{ type=%ld , { sender pid=%ld, %3d %c %3d , result=%6d } }\n"
				 , m->mtype
				 , (long) m->info.sender
				 , m->info.num1 , m->info.operation
				 , m->info.num2 , m->info.result ) ;
}
