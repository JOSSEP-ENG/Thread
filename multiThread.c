#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

// Thread에서 동작할 함수(함수포인터 형식)
void* thread_main(void* arg);
// 공유 자원 변수 생성.
int sharedResource = 0;
// 뮤텍스 변수 생성.
pthread_mutex_t mutex;

int main(int argc, char* argv[]) {
	// Thread ID 저장할 변수 생성.
	pthread_t t_id[3];
	// Thread 생성 시 파라미터로 넘겨줄 변수, 값.
	int thread_param[3] = {1,2,3};
	// thread_main의 return 값을 받을 포인터 변수 생성.
	//void* thr_ret;
	// 뮤텍스 초기화.
	pthread_mutex_init(&mutex, NULL);
	for(int i=0; i<3; i++) {		
		//Success create : 0, Failed create : 양수 반환.
		if(pthread_create(&t_id[i], NULL, thread_main, (void*)&thread_param[i])!=0) {
			puts("pthread_create() error");
			return -1;
		}
	}
	
	// 스레드의 실행이 완료될 때까지 대기하는 함수.
	for(int i=0; i<3; i++) {
		if(pthread_join(t_id[i], NULL)!=0) {
			puts("pthread_join() error");
			return -1;
		}
	}
	
	// 뮤텍스 정리
	pthread_mutex_destroy(&mutex);
	
	//printf("Thread return message : %s\n", (char*)thr_ret);
	printf("result : %d\n", sharedResource);
	puts("main close");
	//free(thr_ret);
	return 0;
}

void* thread_main(void* arg) {
	int i;
	//int cnt = *((int*)arg);
	//char* msg = (char*)malloc(sizeof(char)*50);
	//strcpy(msg, "Hello, I'm thread~\n");

	for(i=0; i<10000000; i++) {
		//sleep(1);
		//printf("running thread %d\n", cnt);
		pthread_mutex_lock(&mutex);
		sharedResource++;
		pthread_mutex_unlock(&mutex);
	}
	//return (void*)msg;
	return NULL;
}
