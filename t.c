#include "stdio.hmm"

#define A (a+a)
#define AA(a) (a+A)
#define B(b) text##b
#define PF(p,f) #p,f

int main(){
  int a=AA(1);
  char[] B(1)="text1";
  char[] B(2)="text2";
  printf(PF(%d\n,a));
  return 0;
}
