#ifndef CTYPE_H
#define CTYPE_H

#include <stdlib.h>

static inline int iscntrl( int c )
{
  return 0;
}

static inline int isalnum( int c )
{
  return isalpha(c) || isdigit(c);
}

#endif
