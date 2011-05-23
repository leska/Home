#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/poll.h>
#include <unistd.h>
#include <errno.h>

#define size 20
int result, i = 1,max=0;
char buf[20];
int main (int argc, char**argv)
{
int *read_fd = malloc((argc-1)*sizeof(int));
fd_set readset;
FD_ZERO(&readset);
for (i = 0; i< argc-1; ++i)
{
read_fd[i] = (int)(strtol(argv[i+1],NULL,10));
	FD_SET(read_fd[i],&readset);
//printf("%d\n",read_fd[i]);
	if(read_fd[i] > max)
		max=read_fd[i];
}
fd_set tmp;
int res;
//return;
for (tmp=readset;1;readset=tmp)

{
	result = select(max + 1,&readset, NULL, NULL, NULL);
//printf("q%d\n",result);
	if(result == -1)
		puts("Error");
	else{
	for(i = 0; i< argc-1; ++i)
	{
		if (result > 0)
		{
			if (FD_ISSET(read_fd[i],&readset)!=0)
			{
//				printf("r%d\n",i);
				res=read(read_fd[i], buf, size);
				//while(res >0)
					write(1, buf, res);
			}
		}else if (result < 0)
			printf("Error on select(): %d\n", strerror(errno));
	}
	     }
}
free(read_fd);
return 0;
}
