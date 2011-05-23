#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

volatile int turn = 0;
int threads[2];

void inline mfence(void)
{
	asm volatile ("mfence":::"memory");
}

void* Dekker(void *arg)
{

int thread_id, counter = 0;
thread_id = *((int*)arg);
for(;;){
threads[thread_id] = 1;
mfence();
	while (threads[1-thread_id])
	{
	if (turn != thread_id)
		{
		threads[thread_id] = 0;
		while (turn != thread_id)
		{}
		threads[thread_id] = 1;
		}
	}
	++counter;
	printf("thread- %d counter-%d\n",thread_id,counter);

turn = 1-thread_id;
threads[thread_id] = 0;
}
}

int main(int argc, char **argv)
{

	pthread_t threads[2];
	int threads_args[] = {0,1};
	int i = 0;
	for (i; i < 2; i++)
	{
		int x=pthread_create(&threads[i], NULL, Dekker,(void*)&threads_args[i]);
		if (x!=0) puts ("Error");
	}
while(1);	
return 0;

}
