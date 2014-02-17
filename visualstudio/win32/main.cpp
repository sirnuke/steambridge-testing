#include <cstdio>

#include "test.h"

int main()
{
  Test t();
  int i = t->function_one(400, true, "Hello World!");
  printf("function_one: %i\n", i);
  bool b = t->function_two(4.2e14, 0x100, 0.125f);
  printf("function_two: %i\n", b);
  return 0;
}
