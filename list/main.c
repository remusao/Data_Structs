#include <stdio.h>
#include "list.h"


void
visitor(int i, void* data)
{
  printf("%i\n", i);
}

int
main(void)
{
  list* l = list_create();
  unsigned test = 1000000;

  for (unsigned i = 0; i < test; i++)
    list_push_front(l, i);

  for (unsigned i = 0; i < test; i++)
    list_pop_back(l);

  for (unsigned i = 0; i < test; i++)
    list_push_front(l, i);
    /*
  list_delete(l, NULL);*/
  return 0;
}
