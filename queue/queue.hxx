/******************************************************************************
**                                                                           **
**    C implementation of array-based, dynamic queues using X-macros         **
**                                                                           **
**    Copyright (C) 2011-2012  Remi BERSON                                   **
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


/// @file queue.hxx
//
/// @authors Remi BERSON
//
/// @brief This file contains macros that define a C implementation of queues,
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
//    ~ NAME_front
//    ~ NAME_back
//
//    ~ NAME_push
//    ~ NAME_pop
//
//  See bellow for more details about this functions.


#ifndef QUEUE_HXX_
# define QUEUE_HXX_

# include <stdlib.h>


/// @brief Defines a "boolean" type. This is much pleasant to use.
typedef char bool;

/// @brief Defines the values TRUE and FALSE to use avec the boolean type.
# define TRUE 1;
# define FALSE 0;


/// @brief This macro will be used to declare structures and headers for the
//  queue data structure. As mentionned in the README, you should create a
//  header file for your "specialized" structure, include queue.hxx and call
//  this macro to declare all the stuff that will be needed to use it.
///
/// @param TYPE Is the type of the element that you want to store in this
//  structure. If you want to use a queue of integer, simply call this macro
//  with  int  as argument. (e.g : QUEUE_HEADER(int, ...))
//  
/// @param NAME Is the name under which your structure will be known after
//  calling the macro. For exemple, if you use call the macro as follow :
//
//    QUEUE_HEADER(int, queue)
//
//  You should use it this way :  queue* my_queue = malloc(sizeof (queue));
//
# define QUEUE_HEADER(TYPE, NAME)                                             \
  typedef struct                                                              \
  {                                                                           \
    TYPE* queue;                                                              \
    unsigned count;                                                           \
    unsigned begin;                                                           \
    unsigned array_size;                                                      \
  } NAME;                                                                     \
                                                                              \
                                                                              \
  typedef void (*visitor_func)(TYPE, void*);                                  \
  typedef void (*destructor_func)(TYPE);                                      \
                                                                              \
                                                                              \
  QUEUE_NCREATE_HEADER(TYPE, NAME);                                           \
  QUEUE_CREATE_HEADER(TYPE, NAME);                                            \
  QUEUE_EMPTY_HEADER(TYPE, NAME);                                             \
  QUEUE_SIZE_HEADER(TYPE, NAME);                                              \
  QUEUE_FRONT_HEADER(TYPE, NAME);                                             \
  QUEUE_BACK_HEADER(TYPE, NAME);                                              \
  QUEUE_PUSH_HEADER(TYPE, NAME);                                              \
  QUEUE_POP_HEADER(TYPE, NAME);                                               \
  QUEUE_CLEAR_HEADER(TYPE, NAME);                                             \
  QUEUE_DELETE_HEADER(TYPE, NAME);                                            \
  QUEUE_VISIT_HEADER(TYPE, NAME);


/// @brief This macro will be replaced at compile time by the definition of
//  each function that could be used on queues. As mentionned in the README
//  you should create a source file for your "specialized" structure, include
//  your header file (that contains the call to the macro QUEUE_HEADER) and
//  call the macro with the *same arguments* as in the header.
///
# define QUEUE_SOURCE(TYPE, NAME)                                             \
  QUEUE_NCREATE(TYPE, NAME)                                                   \
  QUEUE_CREATE(TYPE, NAME)                                                    \
  QUEUE_EMPTY(TYPE, NAME)                                                     \
  QUEUE_SIZE(TYPE, NAME)                                                      \
  QUEUE_FRONT(TYPE, NAME)                                                     \
  QUEUE_BACK(TYPE, NAME)                                                      \
  QUEUE_PUSH(TYPE, NAME)                                                      \
  QUEUE_POP(TYPE, NAME)                                                       \
  QUEUE_CLEAR(TYPE, NAME)                                                     \
  QUEUE_DELETE(TYPE, NAME)                                                    \
  QUEUE_VISIT(TYPE, NAME)



/*
 *  HEADER DEFINITION
 *
 */

// Construction / Destruction

# define QUEUE_CREATE_HEADER(TYPE, NAME)                                      \
  NAME* NAME##_create()

# define QUEUE_NCREATE_HEADER(TYPE, NAME)                                     \
  NAME* NAME##_ncreate(unsigned size)

# define QUEUE_DELETE_HEADER(TYPE, NAME)                                      \
  void NAME##_delete(NAME* queue, destructor_func dest)

# define QUEUE_CLEAR_HEADER(TYPE, NAME)                                       \
  void NAME##_clear(NAME* queue, destructor_func dest)


// Visiting

# define QUEUE_VISIT_HEADER(TYPE, NAME)                                       \
  void NAME##_visit(NAME* queue, visitor_func v, void* data)


// Capacity

# define QUEUE_EMPTY_HEADER(TYPE, NAME)                                       \
  bool NAME##_empty(NAME* queue)

# define QUEUE_SIZE_HEADER(TYPE, NAME)                                        \
  unsigned NAME##_size(NAME* queue)


// Element access

# define QUEUE_FRONT_HEADER(TYPE, NAME)                                       \
  TYPE NAME##_front(NAME* queue)

# define QUEUE_BACK_HEADER(TYPE, NAME)                                        \
  TYPE NAME##_back(NAME* queue)


// Modifiers

# define QUEUE_PUSH_HEADER(TYPE, NAME)                                        \
  void NAME##_push(NAME* queue, TYPE elt)

# define QUEUE_POP_HEADER(TYPE, NAME)                                         \
  TYPE NAME##_pop(NAME* queue)



/*
 *
 * SOURCE DEFINITION
 *
 */


/// @brief Simply call the ncreate function with a default value,
//  see bellow for more details.
//
# define QUEUE_CREATE(TYPE, NAME)                                             \
  NAME* NAME##_create()                                                       \
  {                                                                           \
    return NAME##_ncreate(42);                                                \
  }


/// @brief Create and initialize a new Queue. A new array is initialized
//  with at size and containing element of type TYPE.
///
/// @param TYPE type of the elements that will be stored by the queue
/// @param NAME name of the queue structure
/// @param size is the size of the initial array-container of the queue
//
/// @return a pointer on the new allocated queue. If an error occured,
//  a NULL pointer is returned.
//
# define QUEUE_NCREATE(TYPE, NAME)                                            \
  NAME* NAME##_ncreate(unsigned size)                                         \
  {                                                                           \
    NAME* new_queue = malloc(sizeof (NAME));                                  \
                                                                              \
    if (!new_queue)                                                           \
      return NULL;                                                            \
                                                                              \
    new_queue->queue = malloc(sizeof (TYPE) * size);                          \
    new_queue->count = 0;                                                     \
    new_queue->begin = 0;                                                     \
    new_queue->array_size = size;                                             \
                                                                              \
    return new_queue;                                                         \
  }


/// @brief Starts by calling the function NAME_clear that will free each
//  element contained in the queue, and then free the queue structure it-self.
///
/// @param TYPE type of the elements that will be stored by the queue
/// @param NAME name of the queue structure
/// @param queue The queue to delete
/// @param dest The function pointer to call on each element so has to delete
//  them if needed (this pointer could be NULL if no freeing is needed).
///
# define QUEUE_DELETE(TYPE, NAME)                                             \
  void NAME##_delete(NAME* queue, destructor_func dest)                       \
  {                                                                           \
    NAME##_clear(queue, dest);                                                \
    free(queue->queue);                                                       \
    free(queue);                                                              \
  }


/// @brief Walk through the queue and, if a destructor has been given, call
//  it on each element. At the end, we reset the count of elements to 0
//  (queue empty).
///
/// @param TYPE type of the elements that will be stored by the queue
/// @param NAME name of the queue structure
/// @param queue the queue to clear
/// @param dest The function pointer to call on each element so has to delete
//  them if needed (this pointer could be NULL if no freeing is needed).
///
# define QUEUE_CLEAR(TYPE, NAME)                                              \
  void NAME##_clear(NAME* queue, destructor_func dest)                        \
  {                                                                           \
    if (dest)                                                                 \
      for (unsigned i = 0; i < queue->count; i++)                             \
        dest(queue->queue[(i + queue->begin) % queue->array_size]);           \
    queue->count = 0;                                                         \
    queue->begin = 0;                                                         \
  }


/// @brief Visit the queue and call the visitor function on each element.
///
/// @param TYPE type of the elements that will be stored by the queue
/// @param NAME name of the queue structure
/// @param queue is the queue to visit
/// @param v function pointer to be called on each element in the queue.
/// @param data is a pointer that will be passed to the visitor at each call,
//  you could store anything in it if you need it. The pointer will not be
//  modified by queue functions.
///
# define QUEUE_VISIT(TYPE, NAME)                                              \
  void NAME##_visit(NAME* queue, visitor_func v, void* data)                  \
  {                                                                           \
    for (unsigned i = 0; i < queue->count; i++)                               \
      v(queue->queue[(i + queue->begin) % queue->array_size], data);          \
  }


/// @brief Check if the given queue is empty or not
///
/// @param TYPE type of the elements that will be stored by the queue
/// @param NAME name of the queue structure
/// @param queue the queue
///
/// @return TRUE (1) if the queue is empty (or NULL) and 0 otherwise
///
# define QUEUE_EMPTY(TYPE, NAME)                                              \
  bool NAME##_empty(NAME* queue)                                              \
  {                                                                           \
    return !(queue && queue->count);                                          \
  }


/// @brief Return the size of the queue
///
/// @param TYPE type of the elements that will be stored by the queue2
/// @param NAME name of the queue structure
/// @param queue the queue
///
/// @return the size of the queue
///
# define QUEUE_SIZE(TYPE, NAME)                                               \
  unsigned NAME##_size(NAME* queue)                                           \
  {                                                                           \
    return queue->count;                                                      \
  }


/// @brief Return (but don't modify) the element at the front of the queue
///
/// @param TYPE type of the elements that will be stored by the queue
/// @param NAME name of the queue structure
/// @param queue the queue
///
/// @return the element at the front
///
# define QUEUE_FRONT(TYPE, NAME)                                              \
  TYPE NAME##_front(NAME* queue)                                              \
  {                                                                           \
    return queue->queue[queue->begin];                                        \
  }


/// @brief Return (but don't modify) the element at the back of the queue
///
/// @param TYPE type of the elements that will be stored by the queue
/// @param NAME name of the queue structure
/// @param queue the queue
///
/// @return the element at the bottom
///
# define QUEUE_BACK(TYPE, NAME)                                               \
  TYPE NAME##_back(NAME* queue)                                               \
  {                                                                           \
    return queue->queue[queue->begin + queue->count - 1];                     \
  }


/// @brief Push a new element at the end of the queue
///
/// @param TYPE type of the elements that will be stored by the queue
/// @param NAME name of the queue structure
/// @param queue the queue
/// @param elt element to push in the queue
///
# define QUEUE_PUSH(TYPE, NAME)                                               \
  void NAME##_push(NAME* queue, TYPE elt)                                     \
  {                                                                           \
    if (queue->count >= queue->array_size - 1)                                \
    {                                                                         \
        queue->array_size += queue->array_size / 2;                           \
        TYPE* tmp = malloc(sizeof (TYPE) * queue->array_size);                \
        for (unsigned i = 0; i < queue->count; i++)                           \
          tmp[i] = queue->queue[(i + queue->begin) % queue->array_size];      \
        queue->begin = 0;                                                     \
        free(queue->queue);                                                   \
        queue->queue = tmp;                                                   \
    }                                                                         \
                                                                              \
    queue->queue[(queue->begin + queue->count++) % queue->array_size] = elt;  \
  }


/// @brief Return and remove the element at the front of the queue
///
/// @param TYPE type of the elements that will be stored by the queue
/// @param NAME name of the queue structure
/// @param queue the queue
///
/// @return the front-element
///
# define QUEUE_POP(TYPE, NAME)                                                \
  TYPE NAME##_pop(NAME* queue)                                                \
  {                                                                           \
    return queue->queue[queue->begin + --queue->count];                       \
  }


#endif /* !QUEUE_HXX_ */
