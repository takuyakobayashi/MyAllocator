#include <stdio.h>
#include <stdlib.h>
#include "c_allocator.h"

int g;
int main(  )
{
  printf("Hello! ");  
  printf("\n");  
  m_create();

  int i = 100;
  int *p;
  p = (int *)m_allocate(sizeof(p));
  *p = 100;
  printf("che p      : %d\n",*p);
  printf("che p addr : %p\n",p);
  m_free(p);
  printf("che p      : %d\n",*p);
  printf("che p addr : %p\n",p);
  return 0;
}
