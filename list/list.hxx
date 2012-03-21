/******************************************************************************
**                                                                           **
**    C implementation of double linked-lists using X-macros                 **
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


/** @file list.hxx
**
**  @author Remi BERSON
**
**  @brief This file contains macros that define a C implementation of
**  double-linked dynamic lists. After specialization (see bellow to learn
**  how to do specialisation), you could use the following functions.
**  Assuming that you used NAME as the name of the structure and TYPE as
**  the type of the elements (in general, if you use NAME as the name of
**  your structure, the functions' names will be built like NAME_action.
**  e.g : NAME_clear), the names of the functions will be as is :
**
**    ~ NAME_create
**    ~ NAME_delete
**    ~ NAME_clear
**
**    ~ NAME_visit
**
**    ~ NAME_empty
**    ~ NAME_size
**
**    ~ NAME_front
**    ~ NAME_back
**
**    ~ NAME_push_front
**    ~ NAME_push_back
**    ~ NAME_pop_back
**    ~ NAME_pop_front
**    ~ NAME_insert
**
**  See bellow for more details about this functions.
*/


#ifndef LIST_HXX_
# define LIST_HXX_

# include <stdlib.h>


/**
**  @brief Defines the value TRUE to use with the boolean type.
*/
# define TRUE 1
/**
**  @brief Defines the value FALSE to use with the boolean type.
*/
# define FALSE 0

/**
**  @brief Defines a "boolean" type with a char.
*/
typedef char bool;

/**
** @brief This macro will be used to declare structures and headers for the
** list data structure. As mentionned in the README, you should create a
** header file for your "specialized" structure, include stack.hxx and call
** this macro to declare all the stuff that will be needed to use it.
**
** @param TYPE Is the type of the element that you want to store in this
**  structure. If you want to use a list of integers, simply call this macro
**  with  int  as argument. (e.g : LIST_HEADER(int, ...))
**  
** @param NAME Is the name under which your structure will be known after
**  calling the macro. For exemple, if you use call the macro as follow :
**
**    LIST_HEADER(int, list)
**
**  You should use it this way :  list* my_list = malloc(sizeof (list));
*/
# define LIST_HEADER(TYPE, NAME)                                              \
                                                                              \
  typedef struct NAME NAME;                                                   \
  typedef struct s_node_##NAME s_node_##NAME;                                 \
                                                                              \
  struct NAME                                                                 \
  {                                                                           \
    s_node_##NAME*  first;                                                    \
    s_node_##NAME*  last;                                                     \
    unsigned        size;                                                     \
  };                                                                          \
                                                                              \
  struct s_node_##NAME                                                        \
  {                                                                           \
    TYPE            elt;                                                      \
    s_node_##NAME*  previous;                                                 \
    s_node_##NAME*  next;                                                     \
  };                                                                          \
                                                                              \
  typedef void (*visitor_func)(TYPE, void*);                                  \
  typedef void (*destructor_func)(TYPE);                                      \
                                                                              \
  LIST_CREATE_HEADER(TYPE, NAME);                                             \
  LIST_SIZE_HEADER(TYPE, NAME);                                               \
  LIST_VISIT_HEADER(TYPE, NAME);                                              \
  LIST_PUSH_FRONT_HEADER(TYPE, NAME);                                         \
  LIST_PUSH_BACK_HEADER(TYPE, NAME);                                          \
  LIST_POP_BACK_HEADER(TYPE, NAME);                                           \
  LIST_POP_FRONT_HEADER(TYPE, NAME);                                          \
  LIST_INSERT_HEADER(TYPE, NAME);                                             \
  LIST_FRONT_HEADER(TYPE, NAME);                                              \
  LIST_BACK_HEADER(TYPE, NAME);                                               \
  LIST_EMPTY_HEADER(TYPE, NAME);                                              \
  LIST_DELETE_HEADER(TYPE, NAME);                                             \
  LIST_CLEAR_HEADER(TYPE, NAME);


/**
** @brief This macro will be replaced at compile time by the definition of
**  each function that could be used on lists. As mentionned in the README
**  you should create a source file for your "specialized" structure, include
**  your header file (that contains the call to the macro LIST_HEADER) and
**  call the macro with the *same arguments* as in the header.
*/
# define LIST_SOURCE(TYPE, NAME)                                              \
  LIST_CREATE(TYPE, NAME)                                                     \
  LIST_SIZE(TYPE, NAME)                                                       \
  LIST_VISIT(TYPE, NAME)                                                      \
  LIST_PUSH_FRONT(TYPE, NAME)                                                 \
  LIST_PUSH_BACK(TYPE, NAME)                                                  \
  LIST_POP_BACK(TYPE, NAME)                                                   \
  LIST_POP_FRONT(TYPE, NAME)                                                  \
  LIST_INSERT(TYPE, NAME)                                                     \
  LIST_FRONT(TYPE, NAME)                                                      \
  LIST_BACK(TYPE, NAME)                                                       \
  LIST_EMPTY(TYPE, NAME)                                                      \
  LIST_DELETE(TYPE, NAME)                                                     \
  LIST_CLEAR(TYPE, NAME)




/*
 * HEADER DEFINITION
 *
 */


// Construction / Destruction


# define LIST_CREATE_HEADER(TYPE, NAME)                                       \
  NAME* NAME##_create()

# define LIST_DELETE_HEADER(TYPE, NAME)                                       \
  void NAME##_delete(NAME* list, destructor_func d)

# define LIST_CLEAR_HEADER(TYPE, NAME)                                        \
  void NAME##_clear(NAME* list, destructor_func d)


// Visiting


# define LIST_VISIT_HEADER(TYPE, NAME)                                        \
  void NAME##_visit(NAME* list, visitor_func v, void* data)


// Capacity


# define LIST_SIZE_HEADER(TYPE, NAME)                                         \
  unsigned NAME##_size(NAME* list)

# define LIST_EMPTY_HEADER(TYPE, NAME)                                        \
  bool NAME##_empty(NAME* list)


// Element access


# define LIST_FRONT_HEADER(TYPE, NAME)                                        \
  TYPE NAME##_front(NAME* list)

# define LIST_BACK_HEADER(TYPE, NAME)                                         \
  TYPE NAME##_back(NAME* list)


// Modifiers


# define LIST_PUSH_FRONT_HEADER(TYPE, NAME)                                   \
  void NAME##_push_front(NAME* list, TYPE elt)

# define LIST_PUSH_BACK_HEADER(TYPE, NAME)                                    \
  void NAME##_push_back(NAME* list, TYPE elt)

# define LIST_POP_BACK_HEADER(TYPE, NAME)                                     \
  TYPE NAME##_pop_back(NAME* list)

# define LIST_POP_FRONT_HEADER(TYPE, NAME)                                    \
  TYPE NAME##_pop_front(NAME* list)

# define LIST_INSERT_HEADER(TYPE, NAME)                                       \
  void NAME##_insert(NAME* list, unsigned pos, TYPE elt)



/*
 *
 * SOURCE DEFINITION
 *
 */


/**
** @brief Create a new list composed of the list struct and a unique element
**  which is the sentry. Because we know that there is always at least one
**  element in the list, the algorithms are much more simple.
**
** @param TYPE type of the elements that will be stored in the list
** @param NAME name of the list structure
**
** @return a pointer on the new allocated list. If an error occured, a NULL
**  pointer is returned.
*/
# define LIST_CREATE(TYPE, NAME)                                              \
  NAME* NAME##_create()                                                       \
  {                                                                           \
    NAME* new_list = NULL;                                                    \
    s_node_##NAME* sentry = NULL;                                             \
                                                                              \
    new_list = malloc(sizeof (NAME));                                         \
                                                                              \
    if (!new_list)                                                            \
      return NULL;                                                            \
                                                                              \
    sentry = malloc(sizeof (s_node_##NAME));                                  \
                                                                              \
    if (!sentry)                                                              \
    {                                                                         \
      free(new_list);                                                         \
      return NULL;                                                            \
    }                                                                         \
                                                                              \
    sentry->previous = NULL;                                                  \
    sentry->next = NULL;                                                      \
                                                                              \
    new_list->first = sentry;                                                 \
    new_list->last = sentry;                                                  \
    new_list->size = 0;                                                       \
                                                                              \
    return new_list;                                                          \
  }


/**
** @brief Starts by calling the function NAME_clear that will free each node
**  stored in the list (except the sentry that remains in the list until
**  destruction). After clearing the list, the sentry and the list structure
**  are free.
**
** @param TYPE type of the elements that will be stored in the list
** @param NAME name of the list structure
** @param list the list to delete
** @param dest a function pointer that will be called on each element of the
**  list so as to as to delete them if needed (this pointer could be NULL if
**  no freeing is needed).
*/
# define LIST_DELETE(TYPE, NAME)                                              \
  void NAME##_delete(NAME* list, destructor_func dest)                        \
  {                                                                           \
    NAME##_clear(list, dest);                                                 \
    free(list->first);                                                        \
    free(list);                                                               \
  }


/**
** @brief Walk through the list and, if a destructor has been given, call
**  if on each element of the list. We also reset the size to 0 (empty list)
**  and make the last en first elements of the list to be the sentry.
**
** @param TYPE type of the elements that will be stored in the list
** @param NAME name of the list structure
** @param list the list to clear
** @param dest a function pointer that will be called on each element of the
**  list so as to as to delete them if needed (this pointer could be NULL if
**  no freeing is needed).
*/
# define LIST_CLEAR(TYPE, NAME)                                               \
  void NAME##_clear(NAME* list, destructor_func dest)                         \
  {                                                                           \
    s_node_##NAME* tmp = list->first->next;                                   \
                                                                              \
    list->last = list->first;                                                 \
    list->size = 0;                                                           \
    list->first->next = NULL;                                                 \
                                                                              \
    while (tmp)                                                               \
    {                                                                         \
      if (dest)                                                               \
        dest(tmp->elt);                                                       \
      tmp = tmp->next;                                                        \
    }                                                                         \
  }


/**
** @brief return the number of elements in the list (we do not take into
**  account the sentry).
**
** @param TYPE type of the elements that will be stored in the list
** @param NAME name of the list structure
** @param list the list
**
** @return the size of the list
*/
# define LIST_SIZE(TYPE, NAME)                                                \
  unsigned NAME##_size(NAME* list)                                            \
  {                                                                           \
    return list->size;                                                        \
  }


/**
** @brief Visit the stack and call the visitor function on each element.
**
** @param TYPE type of the elements that will be stored in the list
** @param NAME name of the list structure
** @param list the list to visit
** @param v function pointer to be called on each element of the list
** @param data is a pointer that will be passed to the visitor at each call,
**  you could store anything in it if you need it. The pointer will not be
**  modified by list functions.
*/
# define LIST_VISIT(TYPE, NAME)                                               \
  void NAME##_visit(NAME* list, visitor_func v, void* data)                   \
  {                                                                           \
    s_node_##NAME* tmp = list->first->next;                                   \
    while (tmp)                                                               \
    {                                                                         \
      v(tmp->elt, data);                                                      \
      tmp = tmp->next;                                                        \
    }                                                                         \
  }


/**
** @brief Check if the given list is empty or not (do not take into account
**  the senty node).
**
** @param TYPE type of the elements that will be stored in the list
** @param NAME name of the list structure
** @param list the list
**
** @return TRUE (1), if the list is empty (or NULL), FALSE (0) otherwise
*/
# define LIST_EMPTY(TYPE, NAME)                                               \
  bool NAME##_empty(NAME* list)                                               \
  {                                                                           \
    return !(list && list->size);                                             \
  }


/**
** @brief Add an element at the begenning of the list. (Of course, begening
**  means just *after* the sentry).
**
** @param TYPE type of the elements that will be stored in the list
** @param NAME name of the list structure
** @param list the list
** @param elt the element of type TYPE to add
*/
# define LIST_PUSH_FRONT(TYPE, NAME)                                          \
  void NAME##_push_front(NAME* list, TYPE elt)                                \
  {                                                                           \
    s_node_##NAME* new_node = NULL;                                           \
                                                                              \
    if (!(new_node = malloc(sizeof (s_node_##NAME))))                         \
      return;                                                                 \
                                                                              \
    new_node->elt = elt;                                                      \
    new_node->previous = list->first;                                         \
    new_node->next = list->first->next;                                       \
    list->first->next = new_node;                                             \
                                                                              \
    if (!(list->size++))                                                      \
      list->last = new_node;                                                  \
    else                                                                      \
      new_node->next->previous = new_node;                                    \
  }


/**
** @brief Add an element at the end of the list.
**
** @param TYPE type of the elements that will be stored in the list
** @param NAME name of the list structure
** @param list the list
** @param elt the element of type TYPE to add
*/
# define LIST_PUSH_BACK(TYPE, NAME)                                           \
  void NAME##_push_back(NAME* list, TYPE elt)                                 \
  {                                                                           \
    s_node_##NAME* new_node = NULL;                                           \
                                                                              \
    if (!(new_node = malloc(sizeof (s_node_##NAME))))                         \
      return;                                                                 \
                                                                              \
    new_node->elt = elt;                                                      \
                                                                              \
    new_node->previous = list->last;                                          \
    new_node->next = NULL;                                                    \
    new_node->previous->next = new_node;                                      \
    list->last = new_node;                                                    \
                                                                              \
    list->size++;                                                             \
  }


/**
** @brief Remove and return the first element of the list (the first element
**  just *after* the sentry).
**
** @param TYPE type of the elements that will be stored in the list
** @param NAME name of the list structure
** @param list the list
**
** @return the first element of the list
*/
# define LIST_POP_FRONT(TYPE, NAME)                                           \
  TYPE NAME##_pop_front(NAME* list)                                           \
  {                                                                           \
    s_node_##NAME*  tmp = list->first->next;                                  \
    TYPE            elt = tmp->elt;                                           \
                                                                              \
    if (!(--list->size))                                                      \
      list->last = list->first;                                               \
    else                                                                      \
      tmp->next->previous = list->first;                                      \
                                                                              \
    list->first->next = tmp->next;                                            \
    free(tmp);                                                                \
                                                                              \
    return elt;                                                               \
  }


/**
** @brief Remove and return the last element of the list.
**
** @param TYPE type of the elements that will be stored in the list
** @param NAME name of the list structure
** @param list the list
**
** @return the last element of the list
*/
# define LIST_POP_BACK(TYPE, NAME)                                            \
  TYPE NAME##_pop_back(NAME* list)                                            \
  {                                                                           \
    s_node_##NAME*  tmp = list->last;                                         \
    TYPE            elt = tmp->elt;                                           \
                                                                              \
    list->size--;                                                             \
    tmp->previous->next = NULL;                                               \
    list->last = tmp->previous;                                               \
    free(tmp);                                                                \
                                                                              \
    return elt;                                                               \
  }


/**
** @brief Insert an element at a given position in the list. There are 2
** particular cases :
**   1) pos == 0, in that case we do a push_front
**   2) pos >= size(list), in that case we do a push_back
**
** @param TYPE type of the elements that will be stored in the list
** @param NAME name of the list structure
** @param list the list
** @param pos position to insert the new element
** @param elt new element to insert
*/
# define LIST_INSERT(TYPE, NAME)                                              \
  void NAME##_insert(NAME* list, unsigned pos, TYPE elt)                      \
  {                                                                           \
    s_node_##NAME* new_node = NULL;                                           \
    s_node_##NAME* previous = list->first;                                    \
    s_node_##NAME* tmp = previous->next;                                      \
                                                                              \
    if (pos >= list->size)                                                    \
      NAME##_push_back(list, elt);                                            \
    else if (!pos)                                                            \
      NAME##_push_front(list, elt);                                           \
    else                                                                      \
    {                                                                         \
      new_node = malloc(sizeof (s_node_##NAME));                              \
      new_node->elt = elt;                                                    \
                                                                              \
      while (pos--)                                                           \
      {                                                                       \
        previous = tmp;                                                       \
        tmp = tmp->next;                                                      \
      }                                                                       \
                                                                              \
      tmp->previous = new_node;                                               \
      new_node->next = tmp;                                                   \
      previous->next = new_node;                                              \
      new_node->previous = previous;                                          \
                                                                              \
      list->size++;                                                           \
    }                                                                         \
  }


/**
** @brief return but don't remove the first element of the list (the first
**  element *after* the sentry)
**
** @param TYPE type of the elements that will be stored in the list
** @param NAME name of the list structure
** @param list the list
**
** @return the first element of the list
*/
# define LIST_FRONT(TYPE, NAME)                                               \
  TYPE NAME##_front(NAME* list)                                               \
  {                                                                           \
    return list->first->next->elt;                                            \
  }


/**
** @brief return but don't remove the last element of the list.
**
** @param TYPE type of the elements that will be stored in the list
** @param NAME name of the list structure
** @param list the list
**
** @return the last element of the list
*/
# define LIST_BACK(TYPE, NAME)                                                \
  TYPE NAME##_back(NAME* list)                                                \
  {                                                                           \
    return list->last->elt;                                                   \
  }


#endif /* !LIST_HXX_ */
