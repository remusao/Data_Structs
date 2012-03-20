/******************************************************************************
**                                                                           **
**    Sample code for the stack data structure                               **
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
#include "stack.h"

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


/// @brief Main function to test the stack structure
///
/// @return 0 if all went ok, 1 otherwise
int
main(void)
{
  stack* s = NULL;
  int count = 100000;

  printf("\033[33m > Starting stack test\033[37m :\n\n");

  // Creating stack
  printf("[ \033[32mCreating\033[37m stack ..\n");
  s = stack_create();
  if (!s)
    return 1;
  printf("Stack correctly created ] \n\n");

  printf("Is the stack empty ? > %s\n", (stack_empty(s) ? "yes" : "no"));
  printf("Stack size : %i\n\n", stack_size(s));

  // Pushing / Poping
  printf("[ \033[32mPushing\033[37m %i elements on the stack ..\n\n", count);
  for (int i = 0; i < count; i++)
    stack_push(s, i);

  printf("Is the stack empty ? > %s\n", (stack_empty(s) ? "yes" : "no"));
  printf("Stack size : %i\n\n", stack_size(s));

  printf("[ \033[32mPoping\033[37m %i elements from the stack ..\n\n", count);
  for (int i = 0; i < count; i++)
    stack_pop(s);

  printf("Is the stack empty ? > %s\n", (stack_empty(s) ? "yes" : "no"));
  printf("Stack size : %i\n\n", stack_size(s));

  printf("[ \033[32mPushing\033[37m 100000 elements on the stack ..\n\n");
  for (int i = 0; i < count; i++)
    stack_push(s, i);

  printf("Is the stack empty ? > %s\n", (stack_empty(s) ? "yes" : "no"));
  printf("Stack size : %i\n\n", stack_size(s));

  printf("[ \033[32mClearing\033[37m the stack ..\n\n");
  stack_clear(s, NULL);

  printf("Is the stack empty ? > %s\n", (stack_empty(s) ? "yes" : "no"));
  printf("Stack size : %i\n\n", stack_size(s));


  printf("[ \033[32mPushing\033[37m 1, 2, 3, 4, 5 on top of the stack ..\n\n");
  stack_push(s, 1);
  stack_push(s, 2);
  stack_push(s, 3);
  stack_push(s, 4);
  stack_push(s, 5);
  printf("\033[32mTop\033[37m element is : %i\n", stack_top(s));
  printf("\033[32mBottom\033[37m element is : %i\n\n", stack_bottom(s));

  printf("\033[32mVisiting\033[37m the stack ..\n");
  stack_visit(s, visitor, NULL);


  printf("\n[ \033[32mDeleting\033[37m the stack..\n\n");
  stack_delete(s, NULL);

  printf("Is the stack empty ? > %s\n", (stack_empty(s) ? "yes" : "no"));
  printf("Stack size : %i\n\n", stack_size(s));

  return 0;
}
