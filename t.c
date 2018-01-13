#Edefine A (a+a)
#Edefine AA(a) (a+A)
#Sdefine B(b) text##b
#Sdefine PF(p,f) \
#p,f

//#include "including.hmm"


int main(){
  int a=AA(1);
  #ifdef B
  char[] B(1)="//text1";
  char[] B(2)="/*text2*/";
  #elseifdef A
  int b=AA(2);
  #else
  int c=AA(3);
  #endif
  /*kgabniabnai*/
  //sdfbnadjbnsbjna
  printf(PF(   %d\n,a));
  return 0;
}
