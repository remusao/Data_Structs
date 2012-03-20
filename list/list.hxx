
#ifndef LIST_HXX_
# define LIST_HXX_

# include <stdlib.h>

# define TRUE 1
# define FALSE 0

typedef char bool;


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

# define LIST_CREATE_HEADER(TYPE, NAME)                                       \
  NAME* NAME##_create()

# define LIST_SIZE_HEADER(TYPE, NAME)                                         \
  unsigned NAME##_size(NAME* list)

# define LIST_VISIT_HEADER(TYPE, NAME)                                        \
  void NAME##_visit(NAME* list, visitor_func v, void* data)

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

# define LIST_FRONT_HEADER(TYPE, NAME)                                        \
  TYPE NAME##_front(NAME* list)

# define LIST_BACK_HEADER(TYPE, NAME)                                         \
  TYPE NAME##_back(NAME* list)

# define LIST_EMPTY_HEADER(TYPE, NAME)                                        \
  bool NAME##_empty(NAME* list)

# define LIST_DELETE_HEADER(TYPE, NAME)                                       \
  void NAME##_delete(NAME* list, destructor_func d)

# define LIST_CLEAR_HEADER(TYPE, NAME)                                        \
  void NAME##_clear(NAME* list, destructor_func d)



# define LIST_SIZE(TYPE, NAME)                                                \
  unsigned NAME##_size(NAME* list)                                            \
  {                                                                           \
    return list->size;                                                        \
  }


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


# define LIST_DELETE(TYPE, NAME)                                              \
  void NAME##_delete(NAME* list, destructor_func dest)                        \
  {                                                                           \
    NAME##_clear(list, dest);                                                 \
    free(list->first);                                                        \
    free(list);                                                               \
  }


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


# define LIST_EMPTY(TYPE, NAME)                                               \
  bool NAME##_empty(NAME* list)                                               \
  {                                                                           \
    return !(list && list->size);                                             \
  }


# define LIST_PUSH_FRONT(TYPE, NAME)                                          \
  void NAME##_push_front(NAME* list, TYPE elt)                                \
  {                                                                           \
    s_node_##NAME* new_node = NULL;                                           \
                                                                              \
    new_node = malloc(sizeof (s_node_##NAME));                                \
    if (!new_node)                                                            \
      return;                                                                 \
                                                                              \
    new_node->elt = elt;                                                      \
                                                                              \
    new_node->previous = list->first;                                         \
    new_node->next = list->first->next;                                       \
    list->first->next = new_node;                                             \
                                                                              \
    if (!list->size)                                                          \
      list->last = new_node;                                                  \
    else                                                                      \
      new_node->next->previous = new_node;                                    \
                                                                              \
    list->size++;                                                             \
  }


# define LIST_PUSH_BACK(TYPE, NAME)                                           \
  void NAME##_push_back(NAME* list, TYPE elt)                                 \
  {                                                                           \
    s_node_##NAME* new_node = NULL;                                           \
                                                                              \
    new_node = malloc(sizeof (s_node_##NAME));                                \
    if (!new_node)                                                            \
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


# define LIST_POP_BACK(TYPE, NAME)                                            \
  TYPE NAME##_pop_back(NAME* list)                                            \
  {                                                                           \
    s_node_##NAME*  tmp = list->last;                                         \
    TYPE            elt = tmp->elt;                                           \
                                                                              \
    tmp->previous->next = NULL;                                               \
    list->last = tmp->previous;                                               \
    free(tmp);                                                                \
                                                                              \
    return elt;                                                               \
  }


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


# define LIST_FRONT(TYPE, NAME)                                               \
  TYPE NAME##_front(NAME* list)                                               \
  {                                                                           \
    return list->first->next->elt;                                            \
  }


# define LIST_BACK(TYPE, NAME)                                                \
  TYPE NAME##_back(NAME* list)                                                \
  {                                                                           \
    return list->last->elt;                                                   \
  }



#endif /* !LIST_HXX_ */
