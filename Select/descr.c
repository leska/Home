#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/poll.h>
#include <unistd.h>
#include <errno.h>

#define size 20
int result, i = 1,max = 0;
char buf[20];
int main (int argc, char**argv)
{
int *read_fd = malloc((argc-1)*sizeof(int));
fd_set readset;
fd_set tmp;
int res;
FD_ZERO(&readset);

for (i = 0; i< argc-1; ++i)
	{
	read_fd[i] = (int)(strtol(argv[i+1],NULL,10));
	FD_SET(read_fd[i],&readset);
	if(read_fd[i] > max)
		max=read_fd[i];
	}

for (tmp=readset;1;readset=tmp)
	{
	result = select(max + 1,&readset, NULL, NULL, NULL);
	if(result == -1)
		puts("Error");
	else
	{
		for(i = 0; i< argc-1; ++i)
			{
			if (result > 0)
				{
				if (FD_ISSET(read_fd[i],&readset)!=0)
					{
					res=read(read_fd[i], buf, size);
					if (res < 0)
						puts("Err");
					else
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
