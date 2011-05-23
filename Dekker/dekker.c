#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>

int counter = 0;

volatile int turn = 0;
int threads[2];

void inline mfence(void)
{
	asm volatile ("mfence":::"memory");
}

void* Dekker(void *arg)
{

int thread_id;
thread_id = *((int*)arg);
int i=0;
for(i;i<10000000;i++){
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

turn = 1-thread_id;
threads[thread_id] = 0;
}
//	printf("thread- %d counter-%d\n",thread_id,counter);
}

int main(int argc, char **argv)
{
cpu_set_t cpu0, cpu1;
CPU_ZERO(&cpu0);
CPU_ZERO(&cpu1);
CPU_SET(0, &cpu0);
CPU_SET(1, &cpu1);



	pthread_t threads[2];
	int threads_args[] = {0,1};
	int i = 0;
	for (i; i < 2; i++)
	{
		int x=pthread_create(&threads[i], NULL, Dekker,(void*)&threads_args[i]);
		if (x!=0) puts ("Error");

	}
		if(pthread_setaffinity_np(threads[0],sizeof(cpu_set_t), &cpu0))
		puts("Err");
		if(pthread_setaffinity_np(threads[1],sizeof(cpu_set_t), &cpu1))
		puts("Err");
//while(1);	
i=0;
	for (i; i < 2; i++)
	{
		int x=pthread_join(threads[i], NULL);
		if (x!=0) puts ("Error");
	}
printf("%d",counter);	
return 0;

}
