#include<iostream.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>
#include<conio.h>

//initializing buffer
typedef int buffer_item;
#define buffer_size 20;
buffer_item buffer[buffer_size];
int i=0,j=0;

//initializing semaphores
sem_t emptySem; //for producer
sem_t fullSem; //for consumer


void insert_item(buffer_item item){
	sem_wait(&emptySem);
	buffer[i] = item;
	i = (i+1) % buffer_size;
	
	if(i == 0){
		sem_post(&fullSem);
		sleep(2);
	}
	sem_post(&emptySem);	
}

int remove_item(buffer_item item){
	
	sem_wait(&fullSem);
	item = buffer[j];
	j = (j+1) % buffer_size;
	
	if(j == 0){
		sleep(2);
	}
	
	sem_post(&fullSem);
}

void main(){
	pthread produceThread,consumeThread;
	
	sem_init(&emptySem,0,1);
	sem_init(&fullSem,0,0);
	
	pthread_create(&produceThread,NULL,Producer,NULL);
	pthread_create(&consumeThread,NULL,Consumer,NULL);
	
	pthread_join(produceThread,NULL);
	pthread_join(consumeThread,NULL);
	
	sem_destroy(&emptySem);
	sem_destroy(&fullSem);
	
	pthread_exit(NULL);
	
}


		
		
	
