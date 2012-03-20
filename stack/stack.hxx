#ifndef STACK_HXX_
# define STACK_HXX_

# include <stdlib.h>

typedef char bool;
# define TRUE 1;
# define FALSE 0;


# define STACK_HEADER(TYPE, NAME)                                           \
  typedef struct                                                            \
  {                                                                         \
    TYPE*     stack;                                                        \
    unsigned  size;                                                         \
    unsigned  count;                                                        \
  } NAME;                                                                   \
                                                                            \
  typedef void (*visitor_func)(TYPE, void*);                                \
  typedef void (*destructor_func)(TYPE);                                    \
                                                                            \
                                                                            \
  STACK_NCREATE_HEADER(TYPE, NAME);                                         \
  STACK_CREATE_HEADER(TYPE, NAME);                                          \
  STACK_EMPTY_HEADER(TYPE, NAME);                                           \
  STACK_SIZE_HEADER(TYPE, NAME);                                            \
  STACK_FRONT_HEADER(TYPE, NAME);                                           \
  STACK_BACK_HEADER(TYPE, NAME);                                            \
  STACK_PUSH_HEADER(TYPE, NAME);                                            \
  STACK_POP_HEADER(TYPE, NAME);                                             \
  STACK_CLEAR_HEADER(TYPE, NAME);                                           \
  STACK_DELETE_HEADER(TYPE, NAME);                                          \
  STACK_VISIT_HEADER(TYPE, NAME);



# define STACK_SOURCE(TYPE, NAME)                                           \
  STACK_NCREATE(TYPE, NAME)                                                 \
  STACK_CREATE(TYPE, NAME)                                                  \
  STACK_EMPTY(TYPE, NAME)                                                   \
  STACK_SIZE(TYPE, NAME)                                                    \
  STACK_FRONT(TYPE, NAME)                                                   \
  STACK_BACK(TYPE, NAME)                                                    \
  STACK_PUSH(TYPE, NAME)                                                    \
  STACK_POP(TYPE, NAME)                                                     \
  STACK_CLEAR(TYPE, NAME)                                                   \
  STACK_DELETE(TYPE, NAME)                                                  \
  STACK_VISIT(TYPE, NAME)



/*
 *  HEADER DEFINITION
 *
 */

# define STACK_NCREATE_HEADER(TYPE, NAME)                                     \
  NAME* NAME##_ncreate(unsigned size)

# define STACK_VISIT_HEADER(TYPE, NAME)                                       \
  void NAME##_visit(NAME* stack, visitor_func v, void* data)

# define STACK_DELETE_HEADER(TYPE, NAME)                                      \
  void NAME##_delete(NAME* stack, destructor_func dest)

# define STACK_CLEAR_HEADER(TYPE, NAME)                                       \
  void NAME##_clear(NAME* stack, destructor_func dest)

# define STACK_CREATE_HEADER(TYPE, NAME)                                      \
  NAME* NAME##_create()

# define STACK_EMPTY_HEADER(TYPE, NAME)                                       \
  bool NAME##_empty(NAME* stack)

# define STACK_SIZE_HEADER(TYPE, NAME)                                        \
  unsigned NAME##_size(NAME* stack)

# define STACK_FRONT_HEADER(TYPE, NAME)                                       \
  TYPE NAME##_front(NAME* stack)

# define STACK_BACK_HEADER(TYPE, NAME)                                        \
  TYPE NAME##_back(NAME* stack)

# define STACK_PUSH_HEADER(TYPE, NAME)                                        \
  void NAME##_push(NAME* stack, TYPE elt)

# define STACK_POP_HEADER(TYPE, NAME)                                         \
  TYPE NAME##_pop(NAME* stack)



/*
 *
 * SOURCE DEFINITION
 *
 */


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


# define STACK_VISIT(TYPE, NAME)                                              \
  void NAME##_visit(NAME* stack, visitor_func v, void* data)                  \
  {                                                                           \
    for (unsigned i = 0; i < stack->count; i++)                               \
      v(stack->stack[i], data);                                               \
  }


/// @brief Clear and free the whole stack
///
# define STACK_DELETE(TYPE, NAME)                                             \
  void NAME##_delete(NAME* stack, destructor_func dest)                       \
  {                                                                           \
    NAME##_clear(stack, dest);                                                \
    free(stack->stack);                                                       \
    free(stack);                                                              \
  }


/// @brief Reset the stack
///
# define STACK_CLEAR(TYPE, NAME)                                              \
  void NAME##_clear(NAME* stack, destructor_func dest)                        \
  {                                                                           \
    if (dest)                                                                 \
      for (unsigned i = 0; i < stack->count; i++)                             \
        dest(stack->stack[i]);                                                \
    stack->count = 0;                                                         \
  }


/// @brief  Create a new stack that contains elements of type TYPE
///
/// @return A new stack structure.
//
# define STACK_CREATE(TYPE, NAME)                                             \
  NAME* NAME##_create()                                                       \
  {                                                                           \
    return NAME##_ncreate(42);                                                \
  }



/// @brief Check if the stack given as parameter is empty. A null ptr is
// an empty stack.
///
/// @return TRUE (1) if the stack is empty, FALSE (0) otherwise
//
# define STACK_EMPTY(TYPE, NAME)                                              \
  bool NAME##_empty(NAME* stack)                                              \
  {                                                                           \
    return !(stack && stack->count);                                          \
  }


/// @brief Return the size of the given as argument
//
# define STACK_SIZE(TYPE, NAME)                                               \
  unsigned NAME##_size(NAME* stack)                                           \
  {                                                                           \
    return stack->count;                                                      \
  }


/// @brief Return the first element of the stack
///
# define STACK_FRONT(TYPE, NAME)                                              \
  TYPE NAME##_front(NAME* stack)                                              \
  {                                                                           \
    return stack->stack[stack->count - 1];                                    \
  }


/// @brief Return the last element of the stack
///
# define STACK_BACK(TYPE, NAME)                                               \
  TYPE NAME##_back(NAME* stack)                                               \
  {                                                                           \
    return stack->stack[0];                                                   \
  }


/// @brief Push an element of type TYPE at the end of the stack
//  The stack could be resized if it needs to. If there is enough
//  space at the begening of the stack, the elements are simply shifted.
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


/// @brief Return and delete the first element of the stack
///
# define STACK_POP(TYPE, NAME)                                                \
  TYPE NAME##_pop(NAME* stack)                                                \
  {                                                                           \
    return stack->stack[--stack->count];                                      \
  }


#endif /* !STACK_HXX_ */
