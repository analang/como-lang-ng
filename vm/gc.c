#include <como.h>

como_object *gc_new(como_frame *frame, como_object *obj)
{
  obj->next = frame->root;
  obj->flags = 0;

  frame->root = obj;

  return obj;
}