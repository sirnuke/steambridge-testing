// Simple C++ Class for testing

#include "test.h"
#include "../api.h"

Test::Test() : parent(NULL)
{
  parent = get_real_test();
}


int Test::function_one(int param_one, bool param_two, const char *param_three)
{
  int result = 0;

  // TODO: assembler
  return result;
}

bool function_two(double param_one, void *param_two, float param_three)
{
  bool result = 0;
  // TODO: assembler
  return result;
}

