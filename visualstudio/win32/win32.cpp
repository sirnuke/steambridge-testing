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
	return 0;
}

