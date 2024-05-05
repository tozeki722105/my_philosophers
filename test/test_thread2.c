#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int num = 0;

void* output(void *arg){

    for(;;){
        if (num == -1) {
            break;
        }
		usleep(1000000);
        printf("num = %d\n", num);
    }

    return NULL;
}

void* input(void *arg){

    for(;;){
        scanf("%d", &num);
        if (num == -1) {
            break;
        }
    }

    return NULL;
}

int main(void){
    pthread_t output_thread;
    pthread_t input_thread;

    /* スレッド作成 */
    pthread_create(&output_thread, NULL, output, NULL);
    pthread_create(&input_thread, NULL, input, NULL);

    /* スレッドの終了待ち */
    pthread_join(output_thread, NULL);
    pthread_join(input_thread, NULL);
    
    return 0;
}