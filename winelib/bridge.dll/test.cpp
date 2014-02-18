#include <cstdio>

#define NOMINMAX
#include <wine/debug.h>

#include "test.h"

WINE_DEFAULT_DEBUG_CHANNEL(steambridge);

extern "C"
{
  void *get_real_object()
  {
    // Yes, this leaks memory
    // Shouldn't matter for this test
    return (void *)(new Test());
  }
}

Test::Test()
{
  WINE_TRACE("(this=%p,vtable=%p)\n", this, *((void **)(this)));
   one = 42;
   two = true;
   three = 2.12301424E32;
   four = 4294967301;
   five = -1.2849f;
}

int Test::function_one(int param_one, bool param_two, const char *param_three)
{
  WINE_TRACE("(this=%p,%i,%i,\"%s\")\n", this, param_one, param_two, param_three);
  return one;
}

bool Test::function_two(double param_one, void *param_two, float param_three)
{
  WINE_TRACE("(this=%p,%f|%i&%i,%p,%f)\n", this, param_one, param_one, param_two, param_three);
  return two;
}

double Test::function_three(unsigned short param_one)
{
  WINE_TRACE("(this=%p,%hu)\n", this, param_one);
  return three;
}

uint64_t Test::function_four()
{
  WINE_TRACE("(this=%p)\n", this);
  return four;
}

float Test::function_five(int64_t param_one)
{
  WINE_TRACE("(this=%p,%lli)\n", this, param_one);
  return five;
}

