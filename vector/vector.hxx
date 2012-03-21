/******************************************************************************
**                                                                           **
**    C implementation of array-based, dynamic vector using X-macros         **
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

/// @file vector.hxx
//
/// @authors Remi BERSON
//
/// @brief This file contains macros that define a C implementation of vector,
//  based on dynamic arrays. After specialization (see bellow to learn how to
//  do specialisation), you could use the following functions. Assuming that
//  you used NAME as the name of the structure and TYPE as the type of the
//  elements (in general, if you use NAME as the name of your structure, the
//  functions' names will be built like NAME_action. e.g : NAME_clear), the
//  names of the functions will be as is :
//
//
//  See bellow for more details about this functions.


#ifndef VECTOR_HXX_
# define VECTOR_HXX_

# include <stdlib.h>

/// @brief Defines a "boolean" type. This is much pleasant to use.
typedef char bool;

/// @brief Defines the values TRUE and FALSE to use avec the boolean type.
# define TRUE 1;
# define FALSE 0;


/// @brief This macro will be used to declare structures and headers for the
//  vector data structure. As mentionned in the README, you should create a
//  header file for your "specialized" structure, include vector.hxx and call
//  this macro to declare all the stuff that will be needed to use it.
///
/// @param TYPE Is the type of the element that you want to store in this
//  structure. If you want to use a vector of integers, simply call this macro
//  with  int  as argument. (e.g : VECTOR_HEADER(int, ...))
//  
/// @param NAME Is the name under which your structure will be known after
//  calling the macro. For exemple, if you use call the macro as follow :
//
//    VECTOR_HEADER(int, vector)
//
//  You should use it this way :  vector* my_vector = malloc(sizeof (vector));
///
# define VECTOR_HEADER(TYPE, NAME)                                            \
  typedef struct                                                              \
  {                                                                           \
    TYPE* array;                                                              \
    unsigned capacity;                                                        \
    unsigned count;                                                           \
  } NAME;                                                                     \
                                                                              \
  typedef void (*visitor_func)(TYPE, void*);                                  \
  typedef void (*destructor_func)(TYPE);                                      \
                                                                              \
  VECTOR_CREATE_HEADER(TYPE, NAME);                                           \
  VECTOR_NCREATE_HEADER(TYPE, NAME);                                          \
  VECTOR_DELETE_HEADER(TYPE, NAME);                                           \
  VECTOR_SIZE_HEADER(TYPE, NAME);                                             \
  VECTOR_RESIZE_HEADER(TYPE, NAME);                                           \
  VECTOR_CAPACITY_HEADER(TYPE, NAME);                                         \
  VECTOR_EMPTY_HEADER(TYPE, NAME);                                            \
  VECTOR_RESERVE_HEADER(TYPE, NAME);                                          \
  VECTOR_FRONT_HEADER(TYPE, NAME);                                            \
  VECTOR_BACK_HEADER(TYPE, NAME);                                             \
  VECTOR_AT_HEADER(TYPE, NAME);                                               \
  VECTOR_ASSIGN_HEADER(TYPE, NAME);                                           \
  VECTOR_PUSH_BACK_HEADER(TYPE, NAME);                                        \
  VECTOR_PUSH_FRONT_HEADER(TYPE, NAME);                                       \
  VECTOR_INSERT_HEADER(TYPE, NAME);                                           \
  VECTOR_ERASE_HEADER(TYPE, NAME);                                            \
  VECTOR_CLEAR_HEADER(TYPE, NAME);                                            \
  VECTOR_SWAP_VECT_HEADER(TYPE, NAME)                                         \
  VECTOR_SWAP_HEADER(TYPE, NAME)



/// @brief This macro will be replaced at compile time by the definition of
//  each function that could be used on vectors. As mentionned in the README
//  you should create a source file for your "specialized" structure, include
//  your header file (that contains the call to the macro VECTOR_HEADER) and
//  call the macro with the *same arguments* as in the header.
///
# define VECTOR_SOURCE(TYPE, NAME)                                            \
  VECTOR_CREATE(TYPE, NAME)                                                   \
  VECTOR_NCREATE(TYPE, NAME)                                                  \
  VECTOR_DELETE(TYPE, NAME)                                                   \
  VECTOR_SIZE(TYPE, NAME)                                                     \
  VECTOR_RESIZE(TYPE, NAME)                                                   \
  VECTOR_CAPACITY(TYPE, NAME)                                                 \
  VECTOR_EMPTY(TYPE, NAME)                                                    \
  VECTOR_RESERVE(TYPE, NAME)                                                  \
  VECTOR_FRONT(TYPE, NAME)                                                    \
  VECTOR_BACK(TYPE, NAME)                                                     \
  VECTOR_AT(TYPE, NAME)                                                       \
  VECTOR_ASSIGN(TYPE, NAME)                                                   \
  VECTOR_PUSH_BACK(TYPE, NAME)                                                \
  VECTOR_PUSH_FRONT(TYPE, NAME)                                               \
  VECTOR_INSERT(TYPE, NAME)                                                   \
  VECTOR_ERASE(TYPE, NAME)                                                    \
  VECTOR_CLEAR(TYPE, NAME)                                                    \
  VECTOR_SWAP_VECT(TYPE, NAME)                                                \
  VECTOR_SWAP(TYPE, NAME)



/*
 * HEADER DEFINITION
 *
 */


// Construction / Destruction

# define VECTOR_CREATE_HEADER(TYPE, NAME)                                           \
  NAME* NAME##_create()

# define VECTOR_NCREATE_HEADER(TYPE, NAME)                                          \
  NAME* NAME##_ncreate(unsigned size)

# define VECTOR_DELETE_HEADER(TYPE, NAME)                                           \
  void NAME##_delete(NAME* vector, destructor_func dest)

// Capacity

# define VECTOR_SIZE_HEADER(TYPE, NAME)                                             \
  unsigned NAME##_size(NAME* vector)

# define VECTOR_RESIZE_HEADER(TYPE, NAME)                                           \
  void NAME##_resize(NAME* vector, unsigned ns, TYPE c)

# define VECTOR_CAPACITY_HEADER(TYPE, NAME)                                         \
  unsigned NAME##_capacity(NAME* vector)

# define VECTOR_EMPTY_HEADER(TYPE, NAME)                                            \
  bool NAME##_empty(NAME* vector)

# define VECTOR_RESERVE_HEADER(TYPE, NAME)                                          \
  void NAME##_empty(NAME* vector, unsigned rs)

// Element access

# define VECTOR_FRONT_HEADER(TYPE, NAME)                                            \
  TYPE NAME##_front(NAME* vector)

# define VECTOR_BACK_HEADER(TYPE, NAME)                                             \
  TYPE NAME##_back(NAME* vector)

# define VECTOR_AT_HEADER(TYPE, NAME)                                               \
  TYPE NAME##_at(NAME* vector, unsigned pos)

// Modifiers

# define VECTOR_ASSIGN_HEADER(TYPE, NAME)                                           \
  void NAME##_assign(NAME* vector, unsigned n, TYPE elt)

# define VECTOR_PUSH_BACK_HEADER(TYPE, NAME)                                        \
  void NAME##_push_back(NAME* vector, TYPE elt)

# define VECTOR_PUSH_FRONT_HEADER(TYPE, NAME)                                       \
  void NAME##_push_front(NAME* vector, TYPE elt)

# define VECTOR_INSERT_HEADER(TYPE, NAME)                                           \
  void NAME##_insert(NAME* vector, unsigned pos, TYPE elt)

# define VECTOR_ERASE_HEADER(TYPE, NAME)                                            \
  void NAME##_erase(NAME* vector, unsigned start, unsigned len)

# define VECTOR_SWAP_VECT_HEADER(TYPE, NAME)
  void NAME##_swap_vect(NAME* vector, NAME* vector2)

# define VECTOR_SWAP_HEADER(TYPE, NAME)
  void NAME##_swap(NAME* vector, unsigned a, unsigned b)

# define VECTOR_CLEAR_HEADER(TYPE, NAME)
  void NAME##_clear





/*
 *
 * SOURCE DEFINITION
 *
 */



// Construction / Destruction


# define VECTOR_CREATE(TYPE, NAME)                                           \
  NAME* NAME##_create()
  {
    return NAME##_ncreate(42);
  }


# define VECTOR_NCREATE(TYPE, NAME)                                          \
  NAME* NAME##_ncreate(unsigned size)
  {
    NAME* new_vector = NULL;

    if (!(new_vector = malloc(sizeof (NAME))))
      return NULL;

    new_vector->capacity = size;
    new_vector->count = 0;
    if (!(new_vector->array = malloc(sizeof (TYPE) * size)))
    {
      free(new_vector);
      return NULL;
    }

    return new_vector;
  }


# define VECTOR_DELETE_HEADER(TYPE, NAME)                                           \
  void NAME##_delete(NAME* vector, destructor_func dest)
  {
    NAME##_clear(vector, dest);
    free(vector->array);
    free(vector)
  }


// Capacity


# define VECTOR_SIZE_HEADER(TYPE, NAME)                                             \
  unsigned NAME##_size(NAME* vector)
  {
    return vector->count;
  }

# define VECTOR_RESIZE_HEADER(TYPE, NAME)                                           \
  void NAME##_resize(NAME* vector, unsigned ns, TYPE c)
  {
    if (ns < count)
    {
    }
    else if (ns > count)
    {
    }
  }

# define VECTOR_CAPACITY_HEADER(TYPE, NAME)                                         \
  unsigned NAME##_capacity(NAME* vector)
  {
  }

# define VECTOR_EMPTY_HEADER(TYPE, NAME)                                            \
  bool NAME##_empty(NAME* vector)
  {
  }

# define VECTOR_RESERVE_HEADER(TYPE, NAME)                                          \
  void NAME##_empty(NAME* vector, unsigned rs)
  {
  }

// Element access

# define VECTOR_FRONT_HEADER(TYPE, NAME)                                            \
  TYPE NAME##_front(NAME* vector)
  {
  }

# define VECTOR_BACK_HEADER(TYPE, NAME)                                             \
  TYPE NAME##_back(NAME* vector)
  {
  }

# define VECTOR_AT_HEADER(TYPE, NAME)                                               \
  TYPE NAME##_at(NAME* vector, unsigned pos)
  {
  }

// Modifiers

# define VECTOR_ASSIGN_HEADER(TYPE, NAME)                                           \
  void NAME##_assign(NAME* vector, unsigned n, TYPE elt)
  {
  }

# define VECTOR_PUSH_BACK_HEADER(TYPE, NAME)                                        \
  void NAME##_push_back(NAME* vector, TYPE elt)
  {
  }

# define VECTOR_PUSH_FRONT_HEADER(TYPE, NAME)                                       \
  void NAME##_push_front(NAME* vector, TYPE elt)
  {
  }

# define VECTOR_INSERT_HEADER(TYPE, NAME)                                           \
  void NAME##_insert(NAME* vector, unsigned pos, TYPE elt)
  {
  }

# define VECTOR_ERASE_HEADER(TYPE, NAME)                                            \
  void NAME##_erase(NAME* vector, unsigned start, unsigned len)
  {
  }

# define VECTOR_SWAP_VECT_HEADER(TYPE, NAME)
  void NAME##_swap_vect(NAME* vector, NAME* vector2)
  {
  }

# define VECTOR_SWAP_HEADER(TYPE, NAME)
  void NAME##_swap(NAME* vector, unsigned a, unsigned b)
  {
  }

# define VECTOR_CLEAR_HEADER(TYPE, NAME)
  void NAME##_clear
  {
  }

#endif /* !VECTOR_HXX_ */
