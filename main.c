#include <stdio.h>
#include <stdlib.h>
#include "c_allocator.h"

int main( )
{
  m_create();

  int *pi;
  pi = (int *)m_allocate(sizeof(pi));
  *pi = 100;
  printf("che pi      : %d\n",*pi);
  printf("che pi addr : %p\n",pi);
  m_free(pi);
  printf("che pi      : %d\n",*pi);
  printf("che pi addr : %p\n",pi);

  double *pd;
  pd = (double *)m_allocate(sizeof(pd));
  *pd = 100.5;
  printf("che pd      : %f\n",*pd);
  printf("che pd addr : %p\n",pd);
  m_free(pd);
  printf("che pd      : %f\n",*pd);
  printf("che pd addr : %p\n",pd);

  return 0;
}
