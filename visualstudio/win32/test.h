// Simple C++ Class for testing

#ifndef  ___TEST_H___
#define  ___TEST_H___

class Test
{
  public:
    Test();
    virtual int function_one(int param_one, bool param_two, const char *param_three); 
    virtual bool function_two(double param_one, void *param_two, float param_three);

  private:
    void *parent;
};

#endif //___TEST_H___

