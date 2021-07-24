#ifndef LIB_H_
#define LIB_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>
#include "queue.h"

#define SERVERPORT			4221
#define BUFSIZE				4096
#define SOCKETERROR			(-1)
#define SERVER_BACKLOG		1
#define THREAD_POOL_SIZE	32

pthread_t       th_pool[THREAD_POOL_SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct sockaddr_in	SA_IN;
typedef struct sockaddr		SA;

void	* handle_connection(void *client_socket);
void 	* thread_func(void * arg);
int		check(int exp, const char *msg);


#endif
