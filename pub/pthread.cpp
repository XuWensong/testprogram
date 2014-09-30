#include <iostream>
#include <unistd.h>
#include <pthread.h>

void *thread (void *ptr);


int main () {
	pthread_t pid;

	for (int i = 0; i < 3; i++ ) {

		// create new thread, if success, return 0, 
		int ret = pthread_create(&pid, NULL, thread, NULL);
		if(ret) {
			std::cout<<"create thread failed."<<std::endl;
			return 0;
		}
		sleep(1);
		std::cout<<"This is main process "<<i<<std::endl;
		/*release the resource of thread.
		*This function will be blocked. So, it's not recommeded
		*
		*/
		//pthread_join(pid, NULL);
	}
	
	return 0;
}

void *thread (void * ptr) {
	/*
	*set the thread to be detached, so the thread will release
	* resource automatically, it seems to be better than pthread_join(pid, NULL);
	*/
	pthread_detach(pthread_self());
	//sleep(1);
	for(int i = 0; i < 3; i++) {
		std::cout<<"This is thread "<<i<<std::endl;
	}
	return 0;
	
}