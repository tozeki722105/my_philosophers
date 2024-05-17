
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define T 100

unsigned long	get_time_micro()
{
	struct timeval  time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec));
}

int main()
{
	unsigned long s;
	int i;

	while (i++ < 10)
	{
		s = get_time_micro();
		usleep(T);
		printf("diff=%lu\n", get_time_micro() - s);
	}
}