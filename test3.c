#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
static struct definition *_cmm_0T[20];
struct definition **deftable=_cmm_0T;
static struct filelist *_cmm_1T[10];
struct filelist **incdepth=_cmm_1T;
static FILE *fd;
static char eofflag=0;
static char _cmm_2T[50];
static char *ipbuf=_cmm_2T;
static char *word;
static int isp=0;
static int bytel=0;
static int byteh=0;
static int linenum=1;
static void byteplus(){
if((bytel==32767)){
(byteh=(byteh+sizeof(char )));
(bytel=0);
}
else (bytel=(bytel+sizeof(char )));
}
static int enterlcnt=0;
static char nextlch=0;
static char getL(){
char _cmm_1L;
{if(((nextlch!=0)&&(nextlch!=92))){
(_cmm_1L=nextlch);
(nextlch=0);
byteplus();
return _cmm_1L;
}
}if((nextlch==92))(_cmm_1L=92);
else {
(_cmm_1L=fgetc(fd));
byteplus();
}
for(;(_cmm_1L==92);)
{
if((!_feof(fd)))(nextlch=fgetc(fd));
else {
(eofflag=1);
return 10;
}
if((nextlch==10)){
(linenum=(linenum+1));
if((!_feof(fd)))do{
(_cmm_1L=fgetc(fd));
byteplus();
{if(_feof(fd)){
(eofflag=1);
return 10;
}
}}
while((_cmm_1L==32));
else {
(eofflag=1);
return 10;
}
(enterlcnt=(enterlcnt+1));
(nextlch=0);
}
else return _cmm_1L;
}
{if((_cmm_1L==10))(linenum=(linenum+1));
}return _cmm_1L;
}
static int enterhcnt=0;
static char nexthch=0;
static char sentense=0;
#define _cmm_0S "コメントエラー\n"
#define _cmm_1S "コメントエラー\n"
static char getH(){
char _cmm_1L;
int _cmm_2L;
(_cmm_2L=0);
{if((nexthch!=0)){
(_cmm_1L=nexthch);
(nexthch=0);
return _cmm_1L;
}
}(_cmm_1L=getL());
{if((_cmm_1L==34))if((!sentense))(sentense=1);
else (sentense=0);
}{if(sentense)return _cmm_1L;
}for(;(_cmm_1L==47);)
{
(nexthch=getL());
{if(eofflag)break;
}if((nexthch==47)){
(nexthch=0);
for(;(_cmm_1L!=10);)
{
(_cmm_1L=getL());
{if(eofflag)return 10;
}}
break;
}
else if((nexthch==42)){
(nexthch=0);
(_cmm_2L=1);
for(;(_cmm_2L==1);)
{
for(;(_cmm_1L!=42);)
{
{if((_cmm_1L==10))(enterhcnt=(enterhcnt+1));
}(_cmm_1L=getL());
{if(eofflag){
printf(_cmm_0S);
return 10;
}
}}
(_cmm_1L=getL());
{if(eofflag){
printf(_cmm_1S);
return 10;
}
}{if((_cmm_1L==47))(_cmm_2L=0);
}}
}
else return _cmm_1L;
(_cmm_1L=getL());
{if(eofflag)return _cmm_1L;
}}
return _cmm_1L;
}
static char nextwch=0;
static char wordflag=0;
static char wordspace=0;
static char argspace=0;
static char linehead=1;
static char getWord(){
char _cmm_1L;
if((nextwch!=0)){
(_cmm_1L=nextwch);
(nextwch=0);
}
else (_cmm_1L=getH());
(nextwch=getH());
if((isalnum(_cmm_1L)||(_cmm_1L==46))){
(linehead=0);
(wordflag=1);
{if(((!isalnum(nextwch))&&(nextwch!=46)))if(((nextwch==34)&&(!sentense)))(wordflag=1);
else (wordflag=0);
}}
else if(((_cmm_1L==32)&&(!argspace)))if(linehead){
(wordspace=0);
return _cmm_1L;
}
else {if(wordspace){
(wordspace=0);
for(;(nextwch==32);)
(nextwch=getH());
return _cmm_1L;
}
}else if((_cmm_1L==34))if(sentense)(wordflag=1);
else (wordflag=0);
else {
(linehead=0);
(wordflag=0);
}
{if((nextwch==32))(wordspace=1);
}return _cmm_1L;
}
static int entercount(){
int _cmm_1L;
{
(_cmm_1L=0);
for(;(_cmm_1L<(enterhcnt+enterlcnt));(_cmm_1L=(_cmm_1L+1)))
(ipbuf[_cmm_1L]=10);
}
(enterlcnt=0);
(enterhcnt=0);
return _cmm_1L;
}
static char lexflag=0;
#define _cmm_2S "Edefine"
#define _cmm_3S "Sdefine"
#define _cmm_4S "include"
#define _cmm_5S "else"
#define _cmm_6S "ifdef"
#define _cmm_7S "ifndef"
#define _cmm_8S "elseifdef"
#define _cmm_9S "elseifndef"
#define _cmm_10S "endif"
#define _cmm_11S "undef"
static int lexical(){
int _cmm_1L;
(_cmm_1L=0);
int _cmm_2L;
(_cmm_2L=0);
char _cmm_3L;
(word=_mAlloc((sizeof(char )*50)));
(_cmm_3L=getWord());
for(;wordflag;)
{
(ipbuf[_cmm_1L]=_cmm_3L);
(word[_cmm_2L]=_cmm_3L);
(_cmm_1L=(_cmm_1L+1));
(_cmm_2L=(_cmm_2L+1));
(_cmm_3L=getWord());
}
{if((_cmm_3L==10)){
(_cmm_1L=entercount());
(sentense=0);
(linehead=1);
}
}(ipbuf[_cmm_1L]=_cmm_3L);
(_cmm_1L=(_cmm_1L+1));
(ipbuf[_cmm_1L]=0);
(word[_cmm_2L]=_cmm_3L);
(_cmm_2L=(_cmm_2L+1));
(word[_cmm_2L]=0);
int _cmm_4L;
(_cmm_4L=strlen(word));
{if(lexflag)if((strcmp(word,_cmm_2S)==0))return 1;
else if((strcmp(word,_cmm_3S)==0))return 2;
else if((strcmp(word,_cmm_4S)==0))return 3;
else if((strcmp(word,_cmm_5S)==0))return 4;
else if((strcmp(word,_cmm_6S)==0))return 5;
else if((strcmp(word,_cmm_7S)==0))return 6;
else if((strcmp(word,_cmm_8S)==0))return 7;
else if((strcmp(word,_cmm_9S)==0))return 8;
else if((strcmp(word,_cmm_10S)==0))return 9;
else {if((strcmp(word,_cmm_11S)==0))return 10;
}}if(((word[0]==39)&&(word[(_cmm_4L+-1)]==39)))return 13;
else {if(((word[0]==34)&&(word[(_cmm_4L+-1)]==34)))return 13;
}return 12;
}
#define _cmm_12S " "
static int skipspace(){
int _cmm_1L;
lexical();
for(;(strcmp(word,_cmm_12S)==0);)
(_cmm_1L=lexical());
return _cmm_1L;
}
#define _cmm_13S "\0"
#define _cmm_14S ","
#define _cmm_15S ")"
#define _cmm_16S "\n"
#define _cmm_17S "("
#define _cmm_18S ")"
static char *lexarg(){
int _cmm_1L;
(_cmm_1L=0);
char *_cmm_2L;
(_cmm_2L=_mAlloc((sizeof(char )*10)));
lexical();
(_cmm_2L=strcpy(_cmm_2L,_cmm_13S));
for(;;)
{
{if(((strcmp(word,_cmm_14S)==0)&&(_cmm_1L==0)))break;
}{if(((strcmp(word,_cmm_15S)==0)&&(_cmm_1L==0)))break;
}{if(((strcmp(word,_cmm_16S)==0)||eofflag))break;
}if((strcmp(word,_cmm_17S)==0))(_cmm_1L=(_cmm_1L+1));
else {if((strcmp(word,_cmm_18S)==0))(_cmm_1L=(_cmm_1L+-1));
}(_cmm_2L=strcat(_cmm_2L,word));
lexical();
}
return _cmm_2L;
}
static int narg;
#define _cmm_19S "("
#define _cmm_20S ","
#define _cmm_21S ")"
static char **getArg(){
char **_cmm_1L;
(narg=0);
(argspace=1);
(_cmm_1L=_mAlloc((sizeof(char *)*10)));
lexical();
{if((strcmp(word,_cmm_19S)==0)){
(_cmm_1L[narg]=lexarg());
(narg=(narg+1));
for(;(strcmp(word,_cmm_20S)==0);)
{
(_cmm_1L[narg]=lexarg());
(narg=(narg+1));
}
{if((strcmp(word,_cmm_21S)!=0))(narg=narg);
}}
}(_cmm_1L[narg]=0);
(argspace=0);
return _cmm_1L;
}
#define _cmm_22S "\0"
static char *getDef(char *_cmm_1P,char **_cmm_2P){
char *_cmm_1L;
(_cmm_1L=_mAlloc((sizeof(char )*50)));
int _cmm_2L;
(_cmm_2L=0);
char *_cmm_3L;
char **_cmm_4L;
int _cmm_5L;
(_cmm_5L=narg);
skipspace();
for(;(word[0]!=10);)
{
int _cmm_6L;
(_cmm_6L=0);
{
(_cmm_6L=0);
for(;(_cmm_6L<_cmm_5L);(_cmm_6L=(_cmm_6L+1)))
{if((strcmp(_cmm_2P[_cmm_6L],word)==0)){if((makelist(_cmm_1P,_cmm_6L,_cmm_2L)==-1))return 0;
}}}
{if((_cmm_6L==_cmm_5L)){
int _cmm_7L;
(_cmm_7L=searchdef(word));
{if((_cmm_7L!=-1)){
(_cmm_3L=word);
if((deftable[_cmm_7L]->narg==0)){
(_cmm_4L=_mAlloc(sizeof(char *)));
(_cmm_4L[0]=0);
}
else (_cmm_4L=getArg());
(ipbuf=replacedef(_cmm_3L,_cmm_4L));
}
}}
}(_cmm_1L=strcat(_cmm_1L,ipbuf));
lexical();
(_cmm_2L=(_cmm_2L+1));
}
(_cmm_1L=strcat(_cmm_1L,_cmm_22S));
return _cmm_1L;
}
static char *macroname;
static char **do_makeMname(){
int _cmm_1L;
(_cmm_1L=0);
char **_cmm_2L;
{if(_feof(fd))return 0;
}(_cmm_1L=skipspace());
(macroname=word);
if((_cmm_1L==12))if(isalpha(word[0])){
(_cmm_2L=getArg());
int _cmm_3L;
(_cmm_3L=0);
{
(_cmm_3L=0);
for(;(_cmm_3L<narg);(_cmm_3L=(_cmm_3L+1)))
{if((!isalpha(_cmm_2L[_cmm_3L][0])))return 0;
}}
{if((makemacro(macroname,narg)==-1))return 0;
}}
else return 0;
else return 0;
return _cmm_2L;
}
static int do_Edefine(){
char **_cmm_1L;
(_cmm_1L=do_makeMname());
{if((_cmm_1L==0))return -1;
}char *_cmm_2L;
(_cmm_2L=_mAlloc((sizeof(char )*50)));
(_cmm_2L=getDef(macroname,_cmm_1L));
{if((_cmm_2L==0))return -1;
}int _cmm_3L;
(_cmm_3L=0);
int _cmm_4L;
(_cmm_4L=1);
if((_cmm_2L[0]==40)){
{
(_cmm_3L=1);
for(;(_cmm_2L[_cmm_3L]!=0);(_cmm_3L=(_cmm_3L+1)))
{
if((_cmm_2L[_cmm_3L]==40))(_cmm_4L=(_cmm_4L+1));
else {if((_cmm_2L[_cmm_3L]==41))(_cmm_4L=(_cmm_4L+-1));
}{if((_cmm_4L==0))break;
}}
}
{if((_cmm_2L[(_cmm_3L+1)]!=0))return -1;
}}
else return -1;
{if((makedef(macroname,_cmm_2L)==-1))return -1;
}return 0;
}
static int do_Sdefine(){
char **_cmm_1L;
(_cmm_1L=do_makeMname());
{if((_cmm_1L==0))return -1;
}char *_cmm_2L;
(_cmm_2L=_mAlloc((sizeof(char )*50)));
(_cmm_2L=getDef(macroname,_cmm_1L));
{if((_cmm_2L==0))return -1;
}{if((makedef(macroname,_cmm_2L)==-1))return -1;
}return 0;
}
static int do_undef(){
skipspace();
{if((deletedef(word)==-1))return -1;
}return 0;
}
#define _cmm_23S "r"
static int do_include(){
int _cmm_1L;
char *_cmm_2L;
(_cmm_2L=_mAlloc((sizeof(char )*20)));
(_cmm_1L=skipspace());
if((_cmm_1L==13)){
int _cmm_3L;
(_cmm_3L=0);
{
(_cmm_3L=1);
for(;(word[_cmm_3L]!=34);(_cmm_3L=(_cmm_3L+1)))
(_cmm_2L[(_cmm_3L+-1)]=word[_cmm_3L]);
}
}
else {if((word[0]==60)){
lexical();
for(;(word[0]!=62);)
{
(_cmm_2L=strcat(_cmm_2L,word));
lexical();
}
}
}saveincdepth(linenum,byteh,bytel);
(isp=makeincdepth(_cmm_2L));
(fd=fopen(incdepth[isp]->name,_cmm_23S));
(byteh=0);
(bytel=0);
(linenum=0);
return 0;
}
static int _cmm_3T[10];
static int *ifdepth=_cmm_3T;
static int sp=0;
static char elseflag=0;
static int conditioncheck(){
skipspace();
int _cmm_1L;
(_cmm_1L=searchdef(word));
{if((_cmm_1L>-1))return 1;
}return 0;
}
static int do_ifdef(int _cmm_1P){
(elseflag=0);
if((ifdepth[sp]==1)){
(sp=(sp+1));
if((_cmm_1P==1)){
(ifdepth[sp]=1);
(elseflag=1);
}
else (ifdepth[sp]=0);
}
else {
(sp=(sp+1));
(ifdepth[sp]=0);
}
return 0;
}
static int do_else(){
if((ifdepth[(sp+-1)]==1))if(((ifdepth[sp]==1)||elseflag))(ifdepth[sp]=0);
else (ifdepth[sp]=1);
else (ifdepth[sp]=0);
return 0;
}
static int do_ifndef(int _cmm_1P){
(elseflag=0);
if((ifdepth[sp]==1)){
(sp=(sp+1));
if((_cmm_1P==0)){
(ifdepth[sp]=1);
(elseflag=1);
}
else (ifdepth[sp]=0);
}
else {
(sp=(sp+1));
(ifdepth[sp]=0);
}
return 0;
}
static int do_elseifdef(int _cmm_1P){
if(((ifdepth[(sp+-1)]==1)&&(!elseflag)))if((ifdepth[sp]==1))(ifdepth[sp]=0);
else if((_cmm_1P==1)){
(ifdepth[sp]=1);
(elseflag=1);
}
else (ifdepth[sp]=0);
else (ifdepth[sp]=0);
return 0;
}
static int do_elseifndef(int _cmm_1P){
if(((ifdepth[(sp+-1)]==1)&&(!elseflag)))if((ifdepth[sp]==1))(ifdepth[sp]=0);
else if((_cmm_1P==0)){
(ifdepth[sp]=1);
(elseflag=1);
}
else (ifdepth[sp]=0);
else (ifdepth[sp]=0);
return 0;
}
static int do_endif(){
(ifdepth[sp]=0);
(sp=(sp+-1));
(elseflag=0);
return 0;
}
#define _cmm_24S "r"
#define _cmm_25S "\n"
#define _cmm_26S "r"
#define _cmm_27S "h=%d l=%d\n"
int main(int _cmm_1P,char **_cmm_2P){
(isp=makeincdepth(_cmm_2P[1]));
(fd=fopen(incdepth[isp]->name,_cmm_24S));
int _cmm_1L;
int _cmm_2L;
char *_cmm_3L;
char **_cmm_4L;
(ifdepth[sp]=1);
for(;(!_feof(fd));)
{
(_cmm_1L=lexical());
{if((word[0]==35)){
(lexflag=1);
continue;
}
}if((ifdepth[sp]==1))if(((_cmm_1L==12)||(_cmm_1L==13))){
{if(lexflag){
putchar(35);
int _cmm_5L;
(_cmm_5L=0);
{
(_cmm_5L=0);
for(;(ipbuf[_cmm_5L]!=0);(_cmm_5L=(_cmm_5L+1)))
putchar(ipbuf[_cmm_5L]);
}
(lexflag=0);
continue;
}
}int _cmm_5L;
(_cmm_5L=searchdef(word));
{if((_cmm_5L!=-1)){
(_cmm_3L=word);
(_cmm_4L=getArg());
(ipbuf=replacedef(_cmm_3L,_cmm_4L));
}
}int _cmm_6L;
(_cmm_6L=0);
{
(_cmm_6L=0);
for(;(ipbuf[_cmm_6L]!=0);(_cmm_6L=(_cmm_6L+1)))
putchar(ipbuf[_cmm_6L]);
}
}
else if((_cmm_1L==1)){
(lexflag=0);
putchar(10);
do_Edefine();
}
else if((_cmm_1L==2)){
(lexflag=0);
putchar(10);
do_Sdefine();
}
else if((_cmm_1L==10)){
(lexflag=0);
putchar(10);
do_undef();
}
else {if((_cmm_1L==3)){
(lexflag=0);
do_include();
}
}else {
(lexflag=0);
{if((strcmp(word,_cmm_25S)==0))putchar(10);
}}
if((_cmm_1L==5)){
(lexflag=0);
(_cmm_2L=conditioncheck());
do_ifdef(_cmm_2L);
}
else if((_cmm_1L==4)){
(lexflag=0);
do_else();
}
else if((_cmm_1L==6)){
(lexflag=0);
(_cmm_2L=conditioncheck());
do_ifndef(_cmm_2L);
}
else if((_cmm_1L==7)){
(lexflag=0);
(_cmm_2L=conditioncheck());
do_elseifdef(_cmm_2L);
}
else if((_cmm_1L==8)){
(lexflag=0);
(_cmm_2L=conditioncheck());
do_elseifndef(_cmm_2L);
}
else {if((_cmm_1L==9)){
(lexflag=0);
do_endif();
}
}{if((_feof(fd)&&(isp!=0))){
(isp=deleteincdepth(incdepth[isp]->name));
(fd=fopen(incdepth[isp]->name,_cmm_26S));
fseek(fd,incdepth[isp]->dbyteh,incdepth[isp]->dbytel);
(byteh=incdepth[isp]->dbyteh);
(bytel=incdepth[isp]->dbytel);
printf(_cmm_27S,byteh,bytel);
}
}}
fclose(fd);
return 0;
}
