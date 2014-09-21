#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define MAX_LISTEN 1000
#define BUFF_SIZE 1024
#define THREAD_N 20

struct {
	
}

static pthread_t tid[THREAD_N];
static pthread_mutex_t lock[THREAD_N];
static unsigned int s_thread_para[THREAD_N][4]; /* [1]为线程是否在使用标记
						   [2]为线程池中的id
						   [3]为总的连接中的个数
						   [4]为socket的fd*/

int init_poll(void)
{
	pthread_t tid;
	int i;

	for (i=0; i<THREAD_N; i++) {
		s_thread_para[i][0] = 0;
		s_thread_para[i][1] = i;
		
		pthread_mutex_init(lock[i]);
		pthread_mutex_lock(lock[i]);
	}
	for (i=0; i<THREAD_N; i++) {
		tid = pthread_create(tid+i, NULL, worker, NULL);
		if (tid < 0){
			fprintf(stderr, "pthread_create error: %s\n",
				strerror(errno));
			return -1;
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int ret;

	ret = init_poll();
	if (ret < 0) {
		fprintf(stderr, "init_poll error!\n");
		return -1;
	}
	
	return 0;
}


