###############################################################################
#                                                                             #
#    Sample code for the Stack implementation                                 #
#                                                                             #
#    Copyright (C) 2011-2012  Remi BERSON                                     #
#                                                                             # 
#    This program is free software: you can redistribute it and/or modify     #
#    it under the terms of the GNU General Public License as published by     #
#    the Free Software Foundation, either version 3 of the License, or        #
#    (at your option) any later version.                                      #
#                                                                             #
#    This program is distributed in the hope that it will be useful,          #
#    but WITHOUT ANY WARRANTY; without even the implied warranty of           #
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            #
#    GNU General Public License for more details.                             #
#                                                                             #
#    You should have received a copy of the GNU General Public License        #
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.    #
#                                                                             #
###############################################################################

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
