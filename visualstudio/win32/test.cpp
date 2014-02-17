// Simple C++ Class for testing

#include <cstdio>

#include "test.h"
#include "../api.h"

Test::Test() : parent(NULL)
{
  parent = get_real_test();
}


int Test::function_one(int param_one, bool param_two, const char *param_three)
{
  int result = 0;
  fprintf(stderr, "(this=0x%p,parent=0x%p,%i,%i,\"%s\")\n", this, parent, param_one, param_two, param_three);
  __asm
  {
    // Push the parameters onto the stack
    push param_three
    push param_two
    push param_one
    // Push this onto the stack
    push ecx
    // Get the vtable ecx=this, parent
    mov eax, ecx[offset parent]
    // Lookup the first pointer in the vtable
    mov eax, eax[0]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // Cleanup the stack
    pop ecx
    pop eax
    pop eax
    pop eax
  }
  return result;
}

bool function_two(double param_one, void *param_two, float param_three)
{
  bool result = false;
  __asm
  {
    // Are float values pushed the same?
    // Push the parameters onto the stack
    push param_three
    push param_two
    push param_one[4]
    push param_one
    // Push this onto the stack
    push ecx
    // Get the vtable ecx=this, parent
    mov eax, ecx[offset parent]
    // Lookup the first pointer in the vtable
    mov eax, eax[0]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // Cleanup the stack
    pop ecx
    pop eax
    pop eax
    pop eax
    pop eax
  }
  return result;
}

