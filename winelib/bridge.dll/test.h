// Simple C++ Class for testing

#ifndef  ___TEST_H___
#define  ___TEST_H___

#include <stdint.h>

extern "C"
{
void *get_real_object();
}

class Test
{
  public:
    Test();
    virtual int function_one(int param_one, bool param_two, const char *param_three); 
    virtual bool function_two(double param_one, void *param_two, float param_three);
    virtual double function_three(unsigned short param_one);
    virtual uint64_t function_four();
    virtual float function_five(int64_t param_one);

  private:
    int one;
    bool two;
    double three;
    uint64_t four;
    float five;

};



#endif //___TEST_H___

