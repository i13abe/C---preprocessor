#include "including.hmm"
#Edefine A (a+a)
#Edefine AA(a) (a+A)
#Sdefine B(b) text##b
#Sdefine PF(p,f) #p,f

int main(){
  int a=AA(1);
  char[] B(1)="text1";
  char[] B(2)="text2";
  printf(PF(%d\n,a));
  return 0;
}
