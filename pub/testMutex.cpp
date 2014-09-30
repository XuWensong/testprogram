/*
*Date: 2014.9.30
*function: To test pthread_mutex by writing data into file multi-thread
*Author:Xu Wensong
*/
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <fstream>
#include <sstream>

void *thread (void *ptr);

int index = 0;
pthread_mutex_t mutex;


int main () {
	pthread_t pid;
	pthread_mutex_init(&mutex, NULL);
	for (int index = 0; index < 3; index++ ) {
		pthread_mutex_lock(&mutex);
		// create new thread, if success, return 0, 
		
		int ret = pthread_create(&pid, NULL, thread, &index);
		if(ret) {
			std::cout<<"create thread failed."<<std::endl;
			return 0;
		}
	}
	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);
	//sleep(3);
	return 0;
}

void *thread (void * ptr) {
	/*
	*set the thread to be detached, so the thread will release
	* resource automatically, it seems to be better than pthread_join(pid, NULL);
	*/
	int para = *(int *)ptr;
	std::stringstream ss;
	ss << para;

	pthread_detach(pthread_self());
	std::fstream fileOut("/songzi/tmp/tmp.txt", std::ios::out|std::ios::app);
	std::string str = "songzi" + ss.str();
	if(fileOut.is_open()) {
		for(int i = 0; i < 10; i++) {
			
			fileOut.write(str.c_str(), str.length());
		}
	}
	fileOut.close();
	pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);
	
}