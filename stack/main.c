#include <stdio.h>
#include "stack.h"

void visitor(int i, void* data)
{
  printf("%i\n", i);
}

int
main(void)
{
  stack* s = stack_ncreate(10);
  int count = 10000000;

  if (!s)
    return 1;

  for (int i = 0; i < count; i++)
    stack_push(s, i);

  for (int i = 0; i < count; i++)
    stack_pop(s);

  for (int i = 0; i < count; i++)
    stack_push(s, i);

  stack_delete(s, NULL);
  //stack_visit(s, visitor, NULL);

  return 0;
}
