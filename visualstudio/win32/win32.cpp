// win32.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cstdio>

#include "test.h"


int _tmain(int argc, _TCHAR* argv[])
{
  Test t;
  int i = t.function_one(400, true, "Hello World!");
  printf("function_one: %i\n", i);
  bool b = t.function_two(4.2e14, (void *)(0x100), 0.125f);
  printf("function_two: %i\n", b);
  double d = t.function_three(256);
  printf("function_three: %f\n", d);
  unsigned __int64 u = t.function_four();
  printf("function_four: %llu\n", u);
  float f = t.function_five(4294967306);
  printf("function_five: %f\n", f);
	return 0;
}

