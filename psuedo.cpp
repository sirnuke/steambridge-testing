// primatives are return in EAX
// floats/doubles in st(0) - possibly different syntax
// CSteamID is in EDX+EAX
//    mov eax, result
//    mov edx, result+8

virtual int Test::function(int param_one, bool param_two, const char *param_three)
{
  __TRACE(...);

  void *read_object = get_real_object();
  int result;
  __asm
  {
    // Do we need to save EAX, EBX, or EDX?
    // As I understand, ESP and ESI should be saved by the callee
    // Push the parameters onto the stack, right to left
    mov eax, param_three
    push eax
    mov eax, param_two
    push eax
    mov eax, param_one
    push eax
    // Push this (ECX on VisualStudio, stack in GCC)
    push ecx
    // Get the pointer located at read_object - should be the virtual table
    mov eax, [read_object]
    // Get the pointer to function located second in the table
    // Four bytes is 32bits aka sizeof a pointer (Test:: has a contstructor in this case)
    mov eax, eax[4]
    // Execute the function (fingers crossed)
    call eax
    mov result, eax
    // It's unclear whether directly modifying esp will work right
    // Documentation suggests that directly modifying it means the compiler
    // will save/restore the value around this block
    // This miiight be fine
    // Restore 'this'
    pop ecx
    // Pop three
    pop eax
    // Pop two
    pop eax
    // Pop one
    pop eax
  }
  return result;
}
