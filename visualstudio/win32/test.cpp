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
  //const char *msg = "%c--abcdefghijklmnopqrstuvwxyz1234567890\n";
  printf("(this=0x%p,parent=0x%p,%i,%i,\"%s\",%p)\n", this, parent, param_one, param_two, param_three, param_three);
  //For reference, here's how to call printf
  /*
  __asm
  {
    mov eax, msg
    mov dl, [eax + 16]
    push edx
    //mov eax, msg
    push eax
    call dword ptr[printf]
    pop eax
    pop ecx
  }
  printf("Done with first assembler block\n");
  */
  __asm
  {
    // Push this onto the stack
    //push ecx
    // Push the parameters onto the stack
    mov eax, param_three
    push eax
    // This is correct, bools (at least in GNU-land) are one byte and appear to consistently read 
    // from the lowest byte
    mov al, param_two
    push eax
    mov eax, param_one
    push eax
    // Get the parent
    mov eax, [this]
    mov eax, [eax].parent
    // Push new this onto the stack
    push eax

    //mov eax, msg
    //push eax
    //call dword ptr printf
    //pop eax // msg
    //pop eax // this.parent
    // Get the vtable - pointer should be in the first 32-bits of the class
    mov eax, [eax]
    // Lookup the first pointer in the vtable
    mov eax, [eax + 0]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, eax
    // Cleanup the stack
    // Restore this
    //pop ecx
    // pop this.parent
    pop eax
    // pop param_one
    pop eax
    // pop param_two
    pop eax
    // pop param_three
    pop eax
  }
  return result;
}

bool Test::function_two(double param_one, void *param_two, float param_three)
{
  bool result = false;
  printf("(this=0x%p,parent=0x%p,%f/%i&%i,0x%p,%f)\n", this, parent, param_one, param_one, param_two, param_three, param_three);
  __asm
  {
    // Are float values pushed the same?
    // Push the parameters onto the stack
    mov eax, param_three
    push eax
    mov eax, param_two
    push eax
    // Push both halfs of param_one
    lea edx, param_one
    mov eax, [edx+4]
    push eax
    mov eax, [edx+0]
    push eax
    // Get parent (new this)
    mov eax, [this]
    mov eax, [eax].parent
    // Push this onto the stack
    push eax
    // Get the vtable (pointer at this)
    mov eax, [eax]
    // Lookup the pointer in the vtable
    mov eax, [eax+4]
    // Call that memory location
    call eax
    // Move the returned value into the result
    mov result, al
    // Cleanup the stack
    // pop this->parent
    pop eax
    // pop param_one (in two parts)
    pop eax
    pop eax
    // pop param_two
    pop eax
    // pop param_three
    pop eax
  }
  return result;
}

double Test::function_three(unsigned short param_one)
{
  printf("(this=0x%p,parent=0x%p,%hu)\n", this, this->parent, param_one);
  double result;
  __asm
  {
    mov ax, param_one
    push eax
    // get parent
    mov eax, [this]
    mov eax, [eax].parent
    push eax
    // Get vtable
    mov eax, [eax]
    mov eax, [eax+8]
    call eax
    fst result
    pop eax
    pop eax
  }
  return result;
}

unsigned __int64 Test::function_four()
{
  printf("(this=0x%p,parent=0x%p)\n", this, this->parent);
  unsigned __int64 result;
  __asm
  {
    // get parent
    mov eax, [this]
    mov eax, [eax].parent
    push eax
    // get vtable
    mov eax, [eax]
    mov eax, [eax+12]
    call eax
    // get the result
    lea ecx, result
    mov [ecx+0], eax
    mov [ecx+4], edx
    // cleanup the stack
    pop eax
  }
  return result;
}

float Test::function_five(__int64 param_one)
{
  float result;
  printf("(this=0x%p,parent=0x%p,%lli)\n", this, this->parent, param_one);
  __asm
  {
    lea edx, param_one
    mov eax, [edx+4]
    push eax
    mov eax, [edx+0]
    push eax
    // get parent
    mov eax, [this]
    mov eax, [eax].parent
    push eax
    // get vtable
    mov eax, [eax]
    mov eax, [eax+16]
    call eax
    // get the result
    fst result
    // cleanup the stack
    pop eax
    pop eax
    pop eax
  }

  return result;
}
