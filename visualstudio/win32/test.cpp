// Simple C++ Class for testing

#include <cstdio>

#include "test.h"
#include "../bridge/bridge.h"

Test::Test() : parent(NULL)
{
  parent = get_real_object();
}


int Test::function_one(int param_one, bool param_two, const char *param_three)
{
  int result = 0;
  fprintf(stderr, "(this=0x%p,parent=0x%p,%i,%i,\"%s\")\n", this, parent, param_one, param_two, param_three);
  __asm
  {
    // Push the parameters onto the stack
    mov eax, param_three
    push eax
    mov eax, 0
    mov al, param_two
    push eax
    mov eax, param_one
    push eax
    // Push this onto the stack
    push ecx
    // Get the vtable ecx=this, parent
    mov eax, [ecx].parent
    // Lookup the first pointer in the vtable
    mov eax, [eax + 0]
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

bool Test::function_two(double param_one, void *param_two, float param_three)
{
  bool result = false;
  __asm
  {
    // Are float values pushed the same?
    // Push the parameters onto the stack
    mov eax, param_three
    push eax
    mov eax, param_two
    push eax
    lea edx, param_one
    mov eax, [edx+4]
    push eax
    mov eax, [edx]
    push eax
    // Push this onto the stack
    push ecx
    // Get the vtable ecx=this, parent
    mov eax, [ecx].parent
    // Lookup the first pointer in the vtable
    mov eax, [eax+4]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // Cleanup the stack
    pop ecx
    pop eax
    pop eax
    pop eax
    pop eax
  }
  return result;
}

