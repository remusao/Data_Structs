#include <stdio.h>
#include "queue.h"

#define PRINT(a)


void v(int i, void* data)
{
}

int main()
{
  queue* q = queue_ncreate(10);
  unsigned test = 10000000;

  for (unsigned i = 0; i < test; i++)
    queue_push(q, i);

  for (unsigned i = 0; i < test; i++)
    queue_pop(q);
  
  for (unsigned i = 0; i < test; i++)
    queue_push(q, i);

  queue_delete(q, NULL);

  return 0;
}
