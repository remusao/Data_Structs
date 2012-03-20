
#ifndef QUEUE_XMACRO_
# define QUEUE_XMACRO_

# include <stdlib.h>


/**
 *  USAGE :
 *
 *
 *
 *
 *
 */


typedef char bool;
# define TRUE 1;
# define FALSE 0;


/// @brief Macro to use if you want to declare all the headers of the
// queue functions. You must use the directive in a header file.
///
/// @param TYPE The type of the elements you want to store in your queue.
//
/// @param NAME The name you want to give to your structure
///
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


/// @brief Macro to use if you want to declare all the sources of the
// queue functins. You must use the directive in a source file.
///
/// @param TYPE The type of the elements you want to store in your queue.
//
/// @param NAME The name you want to give to your structure
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

# define QUEUE_NCREATE_HEADER(TYPE, NAME)                                     \
  NAME* NAME##_ncreate(unsigned size)

# define QUEUE_VISIT_HEADER(TYPE, NAME)                                       \
  void NAME##_visit(NAME* queue, visitor_func v, void* data)

# define QUEUE_DELETE_HEADER(TYPE, NAME)                                      \
  void NAME##_delete(NAME* queue, destructor_func dest)

# define QUEUE_CLEAR_HEADER(TYPE, NAME)                                       \
  void NAME##_clear(NAME* queue, destructor_func dest)

# define QUEUE_CREATE_HEADER(TYPE, NAME)                                      \
  NAME* NAME##_create()

# define QUEUE_EMPTY_HEADER(TYPE, NAME)                                       \
  bool NAME##_empty(NAME* queue)

# define QUEUE_SIZE_HEADER(TYPE, NAME)                                        \
  unsigned NAME##_size(NAME* queue)

# define QUEUE_FRONT_HEADER(TYPE, NAME)                                       \
  TYPE NAME##_front(NAME* queue)

# define QUEUE_BACK_HEADER(TYPE, NAME)                                        \
  TYPE NAME##_back(NAME* queue)

# define QUEUE_PUSH_HEADER(TYPE, NAME)                                        \
  void NAME##_push(NAME* queue, TYPE elt)

# define QUEUE_POP_HEADER(TYPE, NAME)                                         \
  TYPE NAME##_pop(NAME* queue)



/*
 *
 * SOURCE DEFINITION
 *
 */


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


/// @brief Visit each element of the queue and call the visitor function
//  on it.
///
/// @param v is the visitor function ptr
/// @param data is a ptr in which you could store whatever you wich
///
# define QUEUE_VISIT(TYPE, NAME)                                              \
  void NAME##_visit(NAME* queue, visitor_func v, void* data)                  \
  {                                                                           \
    for (unsigned i = 0; i < queue->count; i++)                               \
      v(queue->queue[(i + queue->begin) % queue->array_size], data);          \
  }


/// @brief Clear and free the whole queue
///
# define QUEUE_DELETE(TYPE, NAME)                                             \
  void NAME##_delete(NAME* queue, destructor_func dest)                       \
  {                                                                           \
    NAME##_clear(queue, dest);                                                \
    free(queue->queue);                                                       \
    free(queue);                                                              \
  }


/// @brief Reset the queue
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


/// @brief  Create a new queue that contains elements of type TYPE
///
/// @return A new queue structure.
//
# define QUEUE_CREATE(TYPE, NAME)                                             \
  NAME* NAME##_create()                                                       \
  {                                                                           \
    return NAME##_ncreate(42);                                                \
  }



/// @brief Check if the queue given as parameter is empty. A null ptr is
// an empty queue.
///
/// @return TRUE (1) if the queue is empty, FALSE (0) otherwise
//
# define QUEUE_EMPTY(TYPE, NAME)                                              \
  bool NAME##_empty(NAME* queue)                                              \
  {                                                                           \
    return !(queue && queue->count);                                          \
  }


/// @brief Return the size of the given as argument
//
# define QUEUE_SIZE(TYPE, NAME)                                               \
  unsigned NAME##_size(NAME* queue)                                           \
  {                                                                           \
    return queue->count;                                                      \
  }


/// @brief Return the first element of the queue
///
# define QUEUE_FRONT(TYPE, NAME)                                              \
  TYPE NAME##_front(NAME* queue)                                              \
  {                                                                           \
    return queue->queue[queue->begin];                                        \
  }


/// @brief Return the last element of the queue
///
# define QUEUE_BACK(TYPE, NAME)                                               \
  TYPE NAME##_back(NAME* queue)                                               \
  {                                                                           \
    return queue->queue[queue->begin + queue->count - 1];                     \
  }


/// @brief Push an element of type TYPE at the end of the queue
//  The queue could be resized if it needs to. If there is enough
//  space at the begening of the queue, the elements are simply shifted.
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


/// @brief Return and delete the first element of the queue
///
# define QUEUE_POP(TYPE, NAME)                                                \
  TYPE NAME##_pop(NAME* queue)                                                \
  {                                                                           \
    return queue->queue[queue->begin + --queue->count];                       \
  }


#endif /* !QUEUE_XMACRO_ */
