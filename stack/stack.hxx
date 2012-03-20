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


/// @file stack.hxx
//
/// @authors Remi BERSON
//
/// @brief This file contains macros that define a C implementation of stacks,
//  based on dynamic arrays. After specialization (see bellow to learn how to
//  do specialisation), you could use the following functions. Assuming that
//  you used NAME as the name of the structure and TYPE as the type of the
//  elements (in general, if you use NAME as the name of your structure, the
//  functions' names will be built like NAME_action. e.g : NAME_clear), the
//  names of the functions will be as is :
//
//    ~ NAME_create
//    ~ NAME_ncreate
//    ~ NAME_delete
//    ~ NAME_clear
//
//    ~ NAME_visit
//
//    ~ NAME_empty
//    ~ NAME_size
//
//    ~ NAME_top
//    ~ NAME_back
//
//    ~ NAME_push
//    ~ NAME_pop
//
//  See bellow for more details about this functions.



#ifndef STACK_HXX_
# define STACK_HXX_

# include <stdlib.h>

/// @brief Defines a "boolean" type. This is much pleasant to use.
typedef char bool;

/// @brief Defines the values TRUE and FALSE to use avec the boolean type.
# define TRUE 1;
# define FALSE 0;


/// @brief This macro will be used to declare structures and headers for the
//  stack data structure. As mentionned in the README, you should create a
//  header file for your "specialized" structure, include stack.hxx and call
//  this macro to declare all the stuff that will be needed to use it.
///
/// @param TYPE Is the type of the element that you want to store in this
//  structure. If you want to use a stack of integer, simply call this macro
//  with  int  as argument. (e.g : STACK_HEADER(int, ...))
//  
/// @param NAME Is the name under which your structure will be known after
//  calling the macro. For exemple, if you use call the macro as follow :
//
//    STACK_HEADER(int, stack)
//
//  You should use it this way :  stack* my_stack = malloc(sizeof (stack));
///
# define STACK_HEADER(TYPE, NAME)                                             \
  typedef struct                                                              \
  {                                                                           \
    TYPE*     stack;                                                          \
    unsigned  size;                                                           \
    unsigned  count;                                                          \
  } NAME;                                                                     \
                                                                              \
  typedef void (*visitor_func)(TYPE, void*);                                  \
  typedef void (*destructor_func)(TYPE);                                      \
                                                                              \
                                                                              \
  STACK_NCREATE_HEADER(TYPE, NAME);                                           \
  STACK_CREATE_HEADER(TYPE, NAME);                                            \
  STACK_EMPTY_HEADER(TYPE, NAME);                                             \
  STACK_SIZE_HEADER(TYPE, NAME);                                              \
  STACK_FRONT_HEADER(TYPE, NAME);                                             \
  STACK_BACK_HEADER(TYPE, NAME);                                              \
  STACK_PUSH_HEADER(TYPE, NAME);                                              \
  STACK_POP_HEADER(TYPE, NAME);                                               \
  STACK_CLEAR_HEADER(TYPE, NAME);                                             \
  STACK_DELETE_HEADER(TYPE, NAME);                                            \
  STACK_VISIT_HEADER(TYPE, NAME);


/// @brief This macro will be replaced at compile time by the definition of
//  each function that could be used on stacks. As mentionned in the README
//  you should create a source file for your "specialized" structure, include
//  your header file (that contains the call to the macro STACK_HEADER) and
//  call the macro with the *same arguments* as in the header.
///
# define STACK_SOURCE(TYPE, NAME)                                             \
  STACK_NCREATE(TYPE, NAME)                                                   \
  STACK_CREATE(TYPE, NAME)                                                    \
  STACK_EMPTY(TYPE, NAME)                                                     \
  STACK_SIZE(TYPE, NAME)                                                      \
  STACK_FRONT(TYPE, NAME)                                                     \
  STACK_BACK(TYPE, NAME)                                                      \
  STACK_PUSH(TYPE, NAME)                                                      \
  STACK_POP(TYPE, NAME)                                                       \
  STACK_CLEAR(TYPE, NAME)                                                     \
  STACK_DELETE(TYPE, NAME)                                                    \
  STACK_VISIT(TYPE, NAME)



/*
 *  HEADER DEFINITION
 *
 */


// Construction / Destruction

# define STACK_CREATE_HEADER(TYPE, NAME)                                      \
  NAME* NAME##_create()

# define STACK_NCREATE_HEADER(TYPE, NAME)                                     \
  NAME* NAME##_ncreate(unsigned size)

# define STACK_DELETE_HEADER(TYPE, NAME)                                      \
  void NAME##_delete(NAME* stack, destructor_func dest)

# define STACK_CLEAR_HEADER(TYPE, NAME)                                       \
  void NAME##_clear(NAME* stack, destructor_func dest)

// Visiting

# define STACK_VISIT_HEADER(TYPE, NAME)                                       \
  void NAME##_visit(NAME* stack, visitor_func v, void* data)

// Capacity

# define STACK_EMPTY_HEADER(TYPE, NAME)                                       \
  bool NAME##_empty(NAME* stack)

# define STACK_SIZE_HEADER(TYPE, NAME)                                        \
  unsigned NAME##_size(NAME* stack)

// Element access

# define STACK_FRONT_HEADER(TYPE, NAME)                                       \
  TYPE NAME##_top(NAME* stack)

# define STACK_BACK_HEADER(TYPE, NAME)                                        \
  TYPE NAME##_back(NAME* stack)

// Modifiers

# define STACK_PUSH_HEADER(TYPE, NAME)                                        \
  void NAME##_push(NAME* stack, TYPE elt)

# define STACK_POP_HEADER(TYPE, NAME)                                         \
  TYPE NAME##_pop(NAME* stack)



/*
 *
 * SOURCE DEFINITION
 *
 */


/// @brief Simply call the ncreate function with a default value,
//  see bellow for more details.
//
# define STACK_CREATE(TYPE, NAME)                                             \
  NAME* NAME##_create()                                                       \
  {                                                                           \
    return NAME##_ncreate(42);                                                \
  }


/// @brief Create and initialize a new Stack. A new array is initialized
//  with a size and containing element of type TYPE.
///
/// @param TYPE type of the elements that will be stored by the stack
/// @param NAME name of the stack structure
/// @param size is the size of the initial array-container of the stack
//
/// @return a pointer on the new allocated stack. If an error occured,
//  a NULL pointer is returned.
//
# define STACK_NCREATE(TYPE, NAME)                                            \
  NAME* NAME##_ncreate(unsigned size)                                         \
  {                                                                           \
    NAME* new_stack = malloc(sizeof (NAME));                                  \
                                                                              \
    if (!new_stack)                                                           \
      return NULL;                                                            \
                                                                              \
    new_stack->stack = malloc(sizeof (TYPE) * size);                          \
    new_stack->count = 0;                                                     \
    new_stack->size = size;                                                   \
                                                                              \
    return new_stack;                                                         \
  }


/// @brief Starts by calling the function NAME_clear that will free each
//  element contained in the stack, and then free the stack structure it-self.
///
/// @param TYPE type of the elements that will be stored by the stack
/// @param NAME name of the stack structure
/// @param stack The stack to delete
/// @param dest The function pointer to call on each element so has to delete
//  them if needed (this pointer could be NULL if no freeing is needed).
///
# define STACK_DELETE(TYPE, NAME)                                             \
  void NAME##_delete(NAME* stack, destructor_func dest)                       \
  {                                                                           \
    NAME##_clear(stack, dest);                                                \
    free(stack->stack);                                                       \
    free(stack);                                                              \
  }


/// @brief Walk through the stack and, if a destructor has been given, call
//  it on each element. At the end, we reset the count of elements to 0
//  (stack empty).
///
/// @param TYPE type of the elements that will be stored by the stack
/// @param NAME name of the stack structure
/// @param stack the stack to clear
/// @param dest The function pointer to call on each element so has to delete
//  them if needed (this pointer could be NULL if no freeing is needed).
///
# define STACK_CLEAR(TYPE, NAME)                                              \
  void NAME##_clear(NAME* stack, destructor_func dest)                        \
  {                                                                           \
    if (dest)                                                                 \
      for (unsigned i = 0; i < stack->count; i++)                             \
        dest(stack->stack[i]);                                                \
    stack->count = 0;                                                         \
  }


/// @brief Visit the stack and call the visitor function on each element.
///
/// @param TYPE type of the elements that will be stored by the stack
/// @param NAME name of the stack structure
/// @param stack is the stack to visit
/// @param v function pointer to be called on each element in the stack.
/// @param data is a pointer that will be passed to the visitor at each call,
//  you could store anything in it if you need it. The pointer will not be
//  modified by stack functions.
///
# define STACK_VISIT(TYPE, NAME)                                              \
  void NAME##_visit(NAME* stack, visitor_func v, void* data)                  \
  {                                                                           \
    for (unsigned i = 0; i < stack->count; i++)                               \
      v(stack->stack[i], data);                                               \
  }


/// @brief Check if the given stack is empty or not
///
/// @param TYPE type of the elements that will be stored by the stack
/// @param NAME name of the stack structure
/// @param stack the stack
///
/// @return TRUE (1) if the stack is empty (or NULL) and 0 otherwise
///
# define STACK_EMPTY(TYPE, NAME)                                              \
  bool NAME##_empty(NAME* stack)                                              \
  {                                                                           \
    return !(stack && stack->count);                                          \
  }


/// @brief Return the size of the stack
///
/// @param TYPE type of the elements that will be stored by the stack2
/// @param NAME name of the stack structure
/// @param stack the stack
///
/// @return the size of the stack
///
# define STACK_SIZE(TYPE, NAME)                                               \
  unsigned NAME##_size(NAME* stack)                                           \
  {                                                                           \
    return stack->count;                                                      \
  }


/// @brief Return (but don't modify) the element at the top of the stack
///
/// @param TYPE type of the elements that will be stored by the stack
/// @param NAME name of the stack structure
/// @param stack the stack
///
/// @return the element at the top
///
# define STACK_FRONT(TYPE, NAME)                                              \
  TYPE NAME##_top(NAME* stack)                                                \
  {                                                                           \
    return stack->stack[stack->count - 1];                                    \
  }


/// @brief Return (but don't modify) the element at the bottom of the stack
///
/// @param TYPE type of the elements that will be stored by the stack
/// @param NAME name of the stack structure
/// @param stack the stack
///
/// @return the element at the bottom
///
# define STACK_BACK(TYPE, NAME)                                               \
  TYPE NAME##_back(NAME* stack)                                               \
  {                                                                           \
    return stack->stack[0];                                                   \
  }


/// @brief Push a new element at the top of the stack
///
/// @param TYPE type of the elements that will be stored by the stack
/// @param NAME name of the stack structure
/// @param stack the stack
/// @param elt element to push on the stack
///
# define STACK_PUSH(TYPE, NAME)                                               \
  void NAME##_push(NAME* stack, TYPE elt)                                     \
  {                                                                           \
    if (stack->count >= stack->size - 1)                                      \
    {                                                                         \
        stack->size += stack->size / 2;                                       \
        stack->stack = realloc(stack->stack, stack->size * sizeof (TYPE));    \
    }                                                                         \
                                                                              \
    stack->stack[stack->count++] = elt;                                       \
  }


/// @brief Return and remove the element at the top of the stack
///
/// @param TYPE type of the elements that will be stored by the stack
/// @param NAME name of the stack structure
/// @param stack the stack
///
/// @return the top-element
///
# define STACK_POP(TYPE, NAME)                                                \
  TYPE NAME##_pop(NAME* stack)                                                \
  {                                                                           \
    return stack->stack[--stack->count];                                      \
  }


#endif /* !STACK_HXX_ */
