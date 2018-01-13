struct reflist {
struct reflist *next;
int nchar;
int argn;
};
struct definition {
char *name;
int narg;
char *mdefinition;
struct reflist *pattern;
};
struct definition **deftable;
char *replacedef(char *_cmm_1P,char **_cmm_2P);
int searchdef(char *_cmm_1P);
int makemacro(char *_cmm_1P,int _cmm_2P);
int deletedef(char *_cmm_1P);
int makelist(char *_cmm_1P,int _cmm_2P,int _cmm_3P);
int makedef(char *_cmm_1P,char *_cmm_2P);
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
static int depth=0;
char *replacedef(char *_cmm_1P,char **_cmm_2P){
int _cmm_1L;
(_cmm_1L=0);
char *_cmm_2L;
(_cmm_2L=_mAlloc((sizeof(char )*50)));
(_cmm_1L=searchdef(_cmm_1P));
if((deftable[_cmm_1L]->narg==0)){
(_cmm_2L=strcpy(_cmm_2L,deftable[_cmm_1L]->mdefinition));
return _cmm_2L;
}
else {
int _cmm_3L;
(_cmm_3L=0);
{
(_cmm_3L=0);
for(;(_cmm_3L<deftable[_cmm_1L]->narg);(_cmm_3L=(_cmm_3L+1)))
{if((_cmm_2P[_cmm_3L]==0))return 0;
}}
struct reflist *_cmm_4L;
(_cmm_4L=deftable[_cmm_1L]->pattern);
int _cmm_5L;
(_cmm_5L=-1);
int _cmm_6L;
(_cmm_6L=0);
int _cmm_7L;
(_cmm_7L=0);
char _cmm_8L;
(_cmm_8L=0);
char _cmm_9L;
(_cmm_9L=0);
for(;(deftable[_cmm_1L]->mdefinition[_cmm_7L]!=0);)
if((isalnum(deftable[_cmm_1L]->mdefinition[_cmm_7L])||(deftable[_cmm_1L]->mdefinition[_cmm_7L]==46))){
(_cmm_5L=(_cmm_5L+1));
if((_cmm_5L==_cmm_4L->nchar)){
for(;(isalnum(deftable[_cmm_1L]->mdefinition[_cmm_7L])||(deftable[_cmm_1L]->mdefinition[_cmm_7L]==46));)
(_cmm_7L=(_cmm_7L+1));
{if(_cmm_8L){
(_cmm_2L[_cmm_6L]=34);
(_cmm_6L=(_cmm_6L+1));
}
}{
(_cmm_3L=0);
for(;(_cmm_3L<strlen(_cmm_2P[_cmm_4L->argn]));(_cmm_3L=(_cmm_3L+1)))
{
(_cmm_2L[_cmm_6L]=_cmm_2P[_cmm_4L->argn][_cmm_3L]);
(_cmm_6L=(_cmm_6L+1));
}
}
{if(_cmm_8L){
(_cmm_2L[_cmm_6L]=34);
(_cmm_6L=(_cmm_6L+1));
}
}(_cmm_8L=0);
(_cmm_9L=0);
{if((_cmm_4L->next!=0))(_cmm_4L=_cmm_4L->next);
}}
else for(;(isalnum(deftable[_cmm_1L]->mdefinition[_cmm_7L])||(deftable[_cmm_1L]->mdefinition[_cmm_7L]==46));)
{
(_cmm_2L[_cmm_6L]=deftable[_cmm_1L]->mdefinition[_cmm_7L]);
(_cmm_7L=(_cmm_7L+1));
(_cmm_6L=(_cmm_6L+1));
}
}
else {
(_cmm_5L=(_cmm_5L+1));
if((deftable[_cmm_1L]->mdefinition[_cmm_7L]==35)){
if(_cmm_9L){
(_cmm_2L[_cmm_6L]=35);
(_cmm_6L=(_cmm_6L+1));
}
else if(_cmm_8L){
(_cmm_9L=1);
(_cmm_8L=0);
}
else (_cmm_8L=1);
(_cmm_7L=(_cmm_7L+1));
}
else {
(_cmm_2L[_cmm_6L]=deftable[_cmm_1L]->mdefinition[_cmm_7L]);
(_cmm_6L=(_cmm_6L+1));
(_cmm_7L=(_cmm_7L+1));
}
}
(_cmm_2L[_cmm_6L]=0);
}
return _cmm_2L;
}
int searchdef(char *_cmm_1P){
int _cmm_1L;
(_cmm_1L=0);
{
(_cmm_1L=0);
for(;(_cmm_1L<depth);(_cmm_1L=(_cmm_1L+1)))
{if((strcmp(deftable[_cmm_1L]->name,_cmm_1P)==0))return _cmm_1L;
}}
return -1;
}
int makemacro(char *_cmm_1P,int _cmm_2P){
{if((searchdef(_cmm_1P)!=-1))return -1;
}(deftable[depth]=_mAlloc(sizeof(struct definition )));
(deftable[depth]->name=_cmm_1P);
(deftable[depth]->narg=_cmm_2P);
(deftable[depth]->pattern=0);
(deftable[depth]->mdefinition=0);
(depth=(depth+1));
return 0;
}
int deletedef(char *_cmm_1P){
int _cmm_1L;
(_cmm_1L=searchdef(_cmm_1P));
{if((_cmm_1L!=-1)){
free(deftable[_cmm_1L]);
int _cmm_2L;
(_cmm_2L=0);
(depth=(depth+-1));
{
(_cmm_2L=_cmm_1L);
for(;(_cmm_2L<depth);(_cmm_2L=(_cmm_2L+1)))
(deftable[_cmm_2L]=deftable[(_cmm_2L+1)]);
}
}
}return 0;
}
int makelist(char *_cmm_1P,int _cmm_2P,int _cmm_3P){
int _cmm_1L;
(_cmm_1L=0);
struct reflist *_cmm_2L;
(_cmm_1L=searchdef(_cmm_1P));
{if((_cmm_1L==-1))return -1;
}if((deftable[_cmm_1L]->pattern==0)){
(deftable[_cmm_1L]->pattern=_mAlloc(sizeof(struct reflist )));
(_cmm_2L=deftable[_cmm_1L]->pattern);
}
else {
(_cmm_2L=deftable[_cmm_1L]->pattern);
for(;;)
{
{if((_cmm_2L->next==0)){
(_cmm_2L->next=_mAlloc(sizeof(struct reflist )));
(_cmm_2L=_cmm_2L->next);
break;
}
}(_cmm_2L=_cmm_2L->next);
}
}
(_cmm_2L->nchar=_cmm_3P);
(_cmm_2L->argn=_cmm_2P);
(_cmm_2L->next=0);
return 0;
}
int makedef(char *_cmm_1P,char *_cmm_2P){
int _cmm_1L;
(_cmm_1L=0);
(_cmm_1L=searchdef(_cmm_1P));
{if((_cmm_1L==-1))return -1;
}(deftable[_cmm_1L]->mdefinition=_cmm_2P);
return 0;
}
