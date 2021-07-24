#include "../includes/lib.h"

int main()
{
	int server_socket;
	int client_socket;
	int addr_size;

	SA_IN server_addr, client_addr;

	// create threads
	for (int i = 0; i < THREAD_POOL_SIZE; i++)
		pthread_create(&th_pool[i], NULL, thread_func, NULL);

	check((server_socket = socket(AF_INET, SOCK_STREAM, 0)), "Failed to create socket");

	//init addr struct
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(SERVERPORT);

	check(bind(server_socket,(SA*)&server_addr, sizeof(server_addr)), "Bind Failed!");
	check(listen(server_socket, SERVER_BACKLOG), "Listen Failed!");

	while (true) 
	{
		printf("Waiting for connections...\n");

		addr_size = sizeof(SA_IN);
		check(client_socket = accept(server_socket, (SA*)&client_addr, (socklen_t*)&addr_size), "accept failed");
		printf("Connected!\n");

		int *pclient = malloc(sizeof(int));
		*pclient = client_socket;
		pthread_mutex_lock(&mutex);
		enqueue(pclient);
		pthread_mutex_unlock(&mutex);
	}
	close(server_socket);
	return (0);
}

int check(int exp, const char *msg) 
{
	if(exp == SOCKETERROR)
	{
		perror(msg);
		exit(1);
	}
	return exp;
}

void * thread_func(void *arg)
{
	(void)arg;
	while (true)
	{
		pthread_mutex_lock(&mutex);
		int *pclient = dequeue();
		pthread_mutex_unlock(&mutex);
		if (pclient != NULL)
			// there is a connection
			handle_connection(pclient);
	}
}

void * handle_connection(void* p_client_socket)
{
	int		client_socket = *((int*)p_client_socket);

	free(p_client_socket);
	char	buffer[BUFSIZE];
	size_t	bytes_read;
	int		msg_size = 0;
	char	actual_path[PATH_MAX + 1];

	// read client's message 
	while((bytes_read = read(client_socket, buffer + msg_size, sizeof(buffer) - msg_size - 1)) > 0)
	{
		msg_size += bytes_read;
		if (msg_size > BUFSIZE - 1 || buffer[msg_size -1] == '\n')
			break;
	}

	check(bytes_read, "recv error");
	buffer[msg_size - 1] = 0; 

	printf("REQUEST: %s\n", buffer);
	fflush(stdout);

	// validity check
	if (realpath(buffer, actual_path) == NULL)
	{
		printf("ERROR(bad path): %s\n", buffer);
		close(client_socket);
		return (NULL);
	}

	FILE *fp = fopen(actual_path, "r");
	if (fp == NULL)
	{
		printf("ERROR(open): %s\n", buffer);
		close(client_socket);
		return (NULL);
	}
	// SLEEP -- testing only
	//sleep(1);

	while ((bytes_read = fread(buffer, 1, BUFSIZE, fp)) > 0)
	{
		printf("sending %zu bytes\n", bytes_read);
	}
	close(client_socket);
	fclose(fp);
	printf("Closing connection\n");
	return (NULL);
}

