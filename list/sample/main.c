/******************************************************************************
**                                                                           **
**    Sample code for the list data structure                                **
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
#include "list.h"

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


/// @brief Main function to test the list structure
///
/// @return 0 if all went ok, 1 otherwise
int
main(void)
{
  list* s = NULL;
  int count = 100000;

  printf("\033[33m > Starting list test\033[37m :\n\n");

  // Creating list
  printf("[ \033[32mCreating\033[37m list ..\n");
  s = list_create();
  if (!s)
    return 1;
  printf("List correctly created ] \n\n");

  printf("Is the list empty ? > %s\n", (list_empty(s) ? "yes" : "no"));
  printf("List size : %i\n\n", list_size(s));

  // Pushing / Poping
  printf("[ \033[32mPushing\033[37m %i elements on front of the list ..\n\n", count);
  for (int i = 0; i < count; i++)
    list_push_front(s, i);

  printf("Is the list empty ? > %s\n", (list_empty(s) ? "yes" : "no"));
  printf("List size : %i\n\n", list_size(s));

  printf("[ \033[32mPoping\033[37m %i elements from the list ..\n\n", count);
  for (int i = 0; i < count; i++)
    list_pop_front(s);

  printf("Is the list empty ? > %s\n", (list_empty(s) ? "yes" : "no"));
  printf("List size : %i\n\n", list_size(s));

  printf("[ \033[32mPushing\033[37m 100000 elements at the back of the list ..\n\n");
  for (int i = 0; i < count; i++)
    list_push_back(s, i);

  printf("[ \033[32mPoping\033[37m 100000 elements at the back of the list ..\n\n");
  for (int i = 0; i < count; i++)
    list_pop_back(s);

  printf("[ \033[32mInserting\033[37m 100000 elements in the middle of the list ..\n\n");
    list_insert(s, 0, -1);
  for (int i = 0; i < count - 1; i++)
    list_insert(s, 5000, i);

  printf("Is the list empty ? > %s\n", (list_empty(s) ? "yes" : "no"));
  printf("List size : %i\n\n", list_size(s));

  printf("[ \033[32mClearing\033[37m the list ..\n\n");
  list_clear(s, NULL);

  printf("Is the list empty ? > %s\n", (list_empty(s) ? "yes" : "no"));
  printf("List size : %i\n\n", list_size(s));


  printf("[ \033[32mPushing\033[37m 1, 2, 3, 4, 5 on the front of the list ..\n\n");
  list_push_front(s, 1);
  list_push_front(s, 2);
  list_push_front(s, 3);
  list_push_front(s, 4);
  list_push_front(s, 5);
  printf("\033[32mFirst\033[37m element is : %i\n", list_front(s));
  printf("\033[32mLast\033[37m element is : %i\n\n", list_back(s));

  printf("\033[32mVisiting\033[37m the list ..\n");
  list_visit(s, visitor, NULL);


  printf("\n[ \033[32mDeleting\033[37m the list..\n\n");
  list_delete(s, NULL);

  printf("Is the list empty ? > %s\n", (list_empty(s) ? "yes" : "no"));
  printf("List size : %i\n\n", list_size(s));

  return 0;
}
