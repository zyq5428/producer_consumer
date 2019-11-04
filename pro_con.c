#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

struct msg {
	struct msg *next;
	int num;
};

struct msg *head, *tail;
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *p)
{
	struct msg *mp = NULL;
	
	for (;;) {
		pthread_mutex_lock(&lock);
		while (head == NULL)
			pthread_cond_wait(&has_product, &lock);
		mp = head;
		head = head->next;
		pthread_mutex_unlock(&lock);
		printf("Consume %d\n", mp->num);
		free(mp);
		mp =NULL;
		sleep(rand() % 5);
	}
}

void *producer(void *p)
{
	struct msg *mp;
	int i = 0;
	
	for (;;) {
		mp = malloc(sizeof(struct msg));
		mp->num = i++;
		printf("Produce %d\n", mp->num);
		pthread_mutex_lock(&lock);
		if (NULL == head)
			head = mp;
		else
			tail->next = mp;
		tail = mp;
		tail->next = NULL;
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&has_product);
		sleep(rand() % 5);
	}
}

int main(int argc, char *argv[])
{
	pthread_t pid, cid;
	srand(time(NULL));
	pthread_create(&pid, NULL, producer, NULL);
	pthread_create(&pid, NULL, consumer, NULL);
	pthread_join(pid, NULL);
	pthread_join(cid, NULL);
	return 0;
}



