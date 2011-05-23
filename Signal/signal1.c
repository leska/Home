#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

char info[100];

void func(int i, siginfo_t *c,void * v)
{
write(1, info, strlen(info));
//fputs(info,stderr);
if(i==2)
	exit(0);
}


int main ()
{
	sprintf(info, "PID: %d; GID: %d\n", getpid(), getpgid(getpid()));
	//fputs(info, stderr);
	write(1, info, strlen(info));

struct sigaction sa;

//sa.sa_handler = func;
sa.sa_sigaction = func;
sa.sa_flags = SA_SIGINFO; 
sigfillset(&sa.sa_mask);

int i;
for(i=1; i< 32; i++)
{if(i!=9 && i!=19){
if(sigaction(i, &sa, 0)==-1)
	printf("Error:%d\n",i);}
}

while(1) sleep(1)
	;

return 0;
}

