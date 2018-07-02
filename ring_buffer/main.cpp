#include <iostream>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

#include "ring_buffer.h"


#define MAX_TEST_NUM 100
Sven::Ring_buffer<int, MAX_TEST_NUM> test_container;

int producer_array[MAX_TEST_NUM];
int consumer_array[MAX_TEST_NUM];

void *put_fun(void *data)
{
	int i = 0;
	//while (true)
	//{
	//	for (i = 0; i < 5; ++i)
	//	{
	//		if (test_container.put(i))
	//		{
	//			std::cout << "p";
	//		}
	//		else
	//		{
	//			std::cout << "q";
	//		}
	//	}
	//}
	while (i < MAX_TEST_NUM)
	{
		if (test_container.put(i))
		{
			++producer_array[i];
			++i;
		}
	}
	std::cout << "put data finish \n";

	return NULL;
}

void *get_fun(void *data)
{
	int *temp , d;
	//while (true)
	//{
	//	temp = test_container.get();
	//	if (temp)
	//	{
	//		/*d = *temp;
	//		std::cout << d;*/
	//		std::cout << "g";
	//	}
	//	else
	//	{
	//		std::cout << "f";
	//	}
	//}

	std::cout << "start consumer\n";
	while (true)
	{
		temp = test_container.get();
		if (temp)
		{
			d = *temp;
			++consumer_array[d];
			if (d == (MAX_TEST_NUM - 1)) break;
		}
	}

	for (int i = 0; i < MAX_TEST_NUM; ++i)
	{
		if (producer_array[i] != 1)
		{
			std::cout << "producer_array[" << i << "]" << " = " << producer_array[i] << "error \n";
		}

		if (consumer_array[i] != 1)
		{
			std::cout << "consumer_array[" << i << "]" << " = " << consumer_array[i] << "error \n";
		}
	}
	std::cout << "check finish success \n";

	return NULL;
}


int main()
{

	memset(producer_array, 0, sizeof(producer_array));
	memset(consumer_array, 0, sizeof(consumer_array));

#ifndef _WIN32
	pthread_t tid_producer, tid_consumer;
#endif

//生产者
#ifdef _WIN32
	CreateThread(NULL , 0 , (LPTHREAD_START_ROUTINE)put_fun , NULL , 0 ,NULL);
#else
	pthread_create(&tid_producer , NULL , &put_fun , NULL);
#endif
	//put_fun(NULL);

//消费者
#ifdef _WIN32
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)get_fun, NULL, 0, NULL);
#else
	pthread_create(&tid_producer, NULL, &get_fun, NULL);
#endif

#ifndef _WIN3
	//pthread_detach(tid_consumer);
	//pthread_detach(tid_producer);
	pthread_join(tid_producer, NULL);
	pthread_join(tid_consumer, NULL);
#endif

	getchar();
 	return 0;
}