#define COMO_BUILTIN_READLINE_BEGIN
  COMO_UNUSED(args);

  char *buffer = malloc(8);
  size_t buffersize = 8;
  size_t i = 0;
  int c;
  como_object *retval;

  while((c = getchar()) != EOF) {
    if(i == buffersize) {
      buffer = realloc(buffer, buffersize * 2);
      buffersize = buffersize * 2;
    }

    if(c == '\n')
      break; 

    buffer[i++] = c;
  }

  buffer[i] = '\0';

  retval =  como_stringfromstring(buffer);

  free(buffer);

  return retval;
#define COMO_BUILTIN_READLINE_END
