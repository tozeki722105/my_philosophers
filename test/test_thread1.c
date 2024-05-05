#include <stdio.h>
#include <pthread.h>

#define NUM 40

typedef struct data {
    int start;
    int count;
    int	*result;
} t_data;

void *func(void *arg)								/* funcの返り値と引数は、(void *)で指定されている */
{
    int i;
    struct data *data_ptr = (struct data *)arg;		//(void *)で持ってこられた引数を元の型にキャスト 

	i = data_ptr->start;
	while(i < data_ptr->start + data_ptr->count)
	{
        data_ptr->result[i] = i * i * i * i;
		i++;
	}
	return (NULL);
}

t_data init(int start, int count, int *result)
{
	t_data data;

	data.start = start;
	data.count = count;
	data.result = result;
	return (data);
}

int main(void){
    
    int 		result[NUM] = {0};					/* 結果を格納する配列 */
	pthread_t 	th1;
	pthread_t	th2;
    t_data		data1;								/* スレッドを実行する上で必要な情報を格納する配列 */
	t_data		data2;

	data1 = init(0, NUM / 2, result);
	pthread_create(&th1, NULL, func, &data1);		/* 1つ目のスレッドを作成 */

    data2 = init(NUM / 2, NUM / 2, result);
    pthread_create(&th2, NULL, func, &data2);		/* 2つ目のスレッドを作成 */

    pthread_join(th1, NULL);						/* スレッドの終了を待機 */

	int i = 0;
	while(i < NUM)
	{
		printf("%2d %10d\n", i, result[i]);
		i++;
	}

    return 0;
}