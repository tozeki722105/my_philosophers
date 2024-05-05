#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM 4

typedef struct  
{
	int count;
} t_data;


void * func(void *arg)
{
	t_data *data;

	
	data = (t_data *)arg;
	usleep(10000);
	printf("%d\n", data->count);

	return (NULL);
}

void test(t_data *data)
{
	printf("count %d\n", data->count);
}

int main()
{
	t_data data;
	pthread_t	th[NUM];

	data.count = 0;

	int i = 0;
	while(i < NUM)
	{
		pthread_create(&(th[i]), NULL, func, &data);
		// test(&data);
		// usleep(10000);
		data.count++;
		i++;
	}

	i = 0;
	while(i < NUM)
	{
		pthread_join(th[i], NULL);
		i++;
	}
}