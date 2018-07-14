#include<stdio.h>
#include<string.h>
int mcripted(char w[]);		//0-not found         1-found
void encript(char fe[]);
void decript(char fd[]);
void main(int argc,char *argv[])
{
if(mcripted(argv[1])==0)					//checking for match in encrypted.txt
{
encript(argv[1]);						//no match-encrypt
}
else
{
decript(argv[1]);						//match-decrypt
}
}
					//................... MCRIPTED.......................................
int mcripted(char w[])
{
int t=0;
char c,cd[26];
FILE *fp,*tf;
fp=fopen("encrypted.txt","a+");
fseek(fp,0L,0);				//opening files
tf=fopen("temp.txt","w");
strcat(w,"\n");							//adding  \n to file name
t=0;
while(fgets(cd,26,fp)!=NULL)				//getting string from file &searching for a match ............................
{
if(strcmp(cd,w)!=0)						//1)placing string-no match   2)t=1-match(skipping matched string)
{
fprintf(tf,"%s",cd);
}
else
{
t=1;
}
}
if(t==0)
{									//incase of no match placing file name
fprintf(fp,"%s",w);
}
else{
fp=freopen("encrypted.txt","w",fp);
tf=freopen("temp.txt","r",tf);
while((c=getc(tf))!=EOF)				//copying temp file into main file.............................
{
putc(c,fp);
}}
fcloseall();
w[strlen(w)-1]='\0';							//closing all files
remove("temp.txt");
return t;
}
					//...................ENCRIPT.........................................
void encript(char fe[])
{
FILE *mf,*tf,*cf;
char c,d;
mf=fopen(fe,"r");
tf=fopen("temp.txt","w");				//opening files	
cf=fopen("code.txt","r");
while((d=getc(mf))!=EOF)     //checking eof & getting each character from main file.............................
{
if(d==' '||d=='\n')					
{
putc(d,tf);							//incase of space or new line character...............................
}
else
{
fseek(cf,0L,0);						//moving to start of code file
while((c=getc(cf))!=EOF&&c!=d)
{
if(c!=d)
{
while((c=getc(cf))!='\n');
}
}  		//searching for a match...................................
if(c==d)
{								//incase of match      placing corresponding code..............................
fseek(cf,1,1);						//moving through -
c=getc(cf);
while(c!='\n')						//getting code
{
putc(c,tf);							//placing code
c=getc(cf);
}
}
else
{								//incase match not found       placing the character itself........................
putc(d,tf);
}
}
putc('.',tf);							//placing seperative .
}
fclose(cf);
tf=freopen("temp.txt","r",tf);				//reopening main & temp files
mf=freopen(fe,"w",mf);
while((c=getc(tf))!=EOF)				//copying temp file into main file.............................
{
putc(c,mf);
}
fcloseall();							//closing all files
remove("temp.txt");
}
					//...................DECRIPT............................
void decript(char fd[])
{
int t;
char c,w[12],*d,cd[12];
FILE *fp,*cf,*tf;
fp=fopen(fd,"r");
cf=fopen("code.txt","r");
tf=fopen("temp.txt","w");							//opening files
while((c=getc(fp))!=EOF)							//getting each character till eof
{
if(c==' '||c=='\n'){fprintf(tf,"%c",c);					//incase of space and \n p.c.i.......................................
c=getc(fp);
}
else {
w[0]=c;
t=1;
while((w[t]=getc(fp))!='.')							//getting code till .   .......................................
{
t++;
}
w[t]='\0';										//ending sring
fseek(cf,0L,0);
t=0;
while(t!=1&&fgets(cd,12,cf)!=NULL)					// searching for a match from code file ......................
{cd[strlen(cd)-1]='\0';						//moving through cd till \n & ending string
d=&cd[2];
if(strcmp(d,w)==0)
{											//incase of match t=1
t=1;
}
}
if(t==1)										//incase of match placing corresponding char ...................
{
fprintf(tf,"%c",cd[0]);
}
else
{
fprintf(tf,"%c",w[0]);						//incase of no match p.c.i.   ................................
}}
}
fclose(cf);
fp=freopen(fd,"w",fp);								//reopening main & temp files
tf=freopen("temp.txt","r",tf);
while((c=getc(tf))!=EOF)							//copying temp file into main file
{
putc(c,fp);
}
fcloseall();							//closing all files
remove("temp.txt");
}
