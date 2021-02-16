#include <iostream>

using namespace std;

class A{
  public:
    int nA;
    A(int a) : nA(a) {}
    class B{
      public:
        int nB;
        B(int b) : nB(b) {}
        void meth(){
          cout << nA << "\n";
          nA *= nB;
          cout << nA << "\n";
        }
    };
    B gen_B(int b){
      return B(b);
    }
};

int main(){
  
  A A_thing(12);
  auto B_thing = A_thing.gen_B(13);

  B_thing.meth();
  
  return 1;
}
