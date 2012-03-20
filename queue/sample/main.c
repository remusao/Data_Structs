/******************************************************************************
**                                                                           **
**    Sample code for the queue data structure                               **
**                                                                           **
**    This program is free software: you can redistribute it and/or modify   **
**    it under the terms of the GNU General Public License as published by   **
**    the Free Software Foundation, either version 3 of the License, or      **
**    (at your option) any later version.                                    **
**                                                                           **
**    This program is distributed in the hope that it will be useful,        **
**    but WITHOUT ANY WARRANTY; without even the implied warranty of         **
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          **
**    GNU General Public License for more details.                           **
**                                                                           **
**    You should have received a copy of the GNU General Public License      **
**    along with this program.  If not, see <http://www.gnu.org/licenses/>.  **
**                                                                           **
******************************************************************************/

#include <stdio.h>
#include "queue.h"

/// @brief Visitor for an element of type int. Simply
//  print the argument on stdout, followed by a eol.
///
/// @param i The integer to "visit"
/// @param data Could possibly store data in that pointer
void
visitor(int i, void* data)
{
  printf("%i\n", i);
}


/// @brief Main function to test the queue structure
///
/// @return 0 if all went ok, 1 otherwise
int
main(void)
{
  queue* s = NULL;
  int count = 100000;

  printf("\033[33m > Starting queue test\033[37m :\n\n");

  // Creating queue
  printf("[ \033[32mCreating\033[37m queue ..\n");
  s = queue_create();
  if (!s)
    return 1;
  printf("Queue correctly created ] \n\n");

  printf("Is the queue empty ? > %s\n", (queue_empty(s) ? "yes" : "no"));
  printf("Queue size : %i\n\n", queue_size(s));

  // Pushing / Poping
  printf("[ \033[32mPushing\033[37m %i elements in the queue ..\n\n", count);
  for (int i = 0; i < count; i++)
    queue_push(s, i);

  printf("Is the queue empty ? > %s\n", (queue_empty(s) ? "yes" : "no"));
  printf("Queue size : %i\n\n", queue_size(s));

  printf("[ \033[32mPoping\033[37m %i elements from the queue ..\n\n", count);
  for (int i = 0; i < count; i++)
    queue_pop(s);

  printf("Is the queue empty ? > %s\n", (queue_empty(s) ? "yes" : "no"));
  printf("Queue size : %i\n\n", queue_size(s));

  printf("[ \033[32mPushing\033[37m 100000 elements in the queue ..\n\n");
  for (int i = 0; i < count; i++)
    queue_push(s, i);

  printf("Is the queue empty ? > %s\n", (queue_empty(s) ? "yes" : "no"));
  printf("Queue size : %i\n\n", queue_size(s));

  printf("[ \033[32mClearing\033[37m the queue ..\n\n");
  queue_clear(s, NULL);

  printf("Is the queue empty ? > %s\n", (queue_empty(s) ? "yes" : "no"));
  printf("Queue size : %i\n\n", queue_size(s));


  printf("[ \033[32mPushing\033[37m 1, 2, 3, 4, 5 in the queue ..\n\n");
  queue_push(s, 1);
  queue_push(s, 2);
  queue_push(s, 3);
  queue_push(s, 4);
  queue_push(s, 5);
  printf("\033[32mFront\033[37m element is : %i\n", queue_front(s));
  printf("\033[32mBack\033[37m element is : %i\n\n", queue_back(s));

  printf("\033[32mVisiting\033[37m the queue ..\n");
  queue_visit(s, visitor, NULL);


  printf("\n[ \033[32mDeleting\033[37m the queue..\n\n");
  queue_delete(s, NULL);

  printf("Is the queue empty ? > %s\n", (queue_empty(s) ? "yes" : "no"));
  printf("Queue size : %i\n\n", queue_size(s));

  return 0;
}
