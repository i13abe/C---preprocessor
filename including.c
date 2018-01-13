struct filelist {
char *name;
int linen;
int dbyteh;
int dbytel;
};
struct filelist **incdepth;
int saveincdepth(int _cmm_1P,int _cmm_2P,int _cmm_3P);
int makeincdepth(char *_cmm_1P);
int deleteincdepth(char *_cmm_1P);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int ifsp=-1;
int saveincdepth(int _cmm_1P,int _cmm_2P,int _cmm_3P){
(incdepth[ifsp]->linen=_cmm_1P);
(incdepth[ifsp]->dbyteh=_cmm_2P);
(incdepth[ifsp]->dbytel=_cmm_3P);
return ifsp;
}
int makeincdepth(char *_cmm_1P){
(ifsp=(ifsp+1));
(incdepth[ifsp]=_mAlloc(sizeof(struct filelist )));
(incdepth[ifsp]->name=_cmm_1P);
(incdepth[ifsp]->linen=0);
(incdepth[ifsp]->dbyteh=0);
(incdepth[ifsp]->dbytel=0);
return ifsp;
}
int deleteincdepth(char *_cmm_1P){
{if((strcmp(_cmm_1P,incdepth[ifsp]->name)==0)){
free(incdepth[ifsp]);
(ifsp=(ifsp+-1));
return ifsp;
}
}return -1;
}
