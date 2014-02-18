#include <cstdio>

#define NOMINMAX
#include <wine/debug.h>

#include "test.h"

WINE_DEFAULT_DEBUG_CHANNEL(steambridget);

static Test t;

extern "C"
{
  void *get_real_object()
  {
    return (void *)(&t);
  }
}

Test::Test()
{
  WINE_TRACE("(this=%p,vtable=%p,function_one=%p)\n", this, *((void **)(this)), &Test::function_one);
}

int Test::function_one(int param_one, bool param_two, const char *param_three)
{
  WINE_TRACE("(this=%p,%i,%i,\"%s\")\n", this, param_one, param_two, param_three);
  return 42;
}

bool Test::function_two(double param_one, void *param_two, float param_three)
{
  WINE_TRACE("(this=%p,%f|%i&%i,%p,%f)\n", this, param_one, param_one, param_two, param_three);
  return true;
}

