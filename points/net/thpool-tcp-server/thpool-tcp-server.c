#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "thpool.h"

#define __UNUSED__ __attribute__((unused))

#define BUFFER_SIZE 1024

#define ERR_BIND 1
#define ERR_LISTEN 2

static void tcp_server_handle(void *args)
{
    int client_fd = *(int *)args;
    uint8_t buff[BUFFER_SIZE];

    for (;;) {
        int n = recv(client_fd, buff, BUFFER_SIZE, 0);

        /* When a stream socket peer has performed an orderly shutdown, the return value will be 0 (the traditional "end-of-file" return). */
        if (!n)
            goto POWER_OFF;

        /* power off */
        buff[n] = '\0';
        if (strstr((const char *)buff, "POWER_OFF"))
            goto POWER_OFF;

        send(client_fd, buff, n, 0);
    }

POWER_OFF:
    close(client_fd);
}

// void task(void *arg)
// {
//     printf("Thread #%u working on %lu\n", (int)pthread_self(), (size_t)arg);
// }

static int tcp_server_run(char *ip)
{
    threadpool thpool = thpool_init(1024);

    int server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in si;
    char buff[BUFFER_SIZE];

    memset(&si, 0, sizeof(si));
    memset(buff, 0, sizeof(buff));
    si.sin_family = PF_INET;
    si.sin_addr.s_addr = inet_addr(ip);
    si.sin_port = htons(55558);

    if (-1 == bind(server_socket, (struct sockaddr *)&si, sizeof(si)))
        return ERR_BIND;

    if (-1 == listen(server_socket, 5))
        return ERR_LISTEN;

    struct sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    socklen_t client_addr_size = sizeof(client_addr);

    for (;;) {
        int client_socket = accept(
            server_socket, (struct sockaddr *)&client_addr, &client_addr_size);

        thpool_add_work(thpool, tcp_server_handle, (void *)&client_socket);
    }

    thpool_wait(thpool);
    thpool_destroy(thpool);
    close(server_socket);
    return 0;
}

int main(int argc, char **argv)
{
    return tcp_server_run(argv[1]);
}
