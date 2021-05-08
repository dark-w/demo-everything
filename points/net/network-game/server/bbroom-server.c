#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include "list.h"

#include "thpool.h"

#define __UNUSED__ __attribute__((unused))

#define BUFFER_SIZE 1024

#define ERR_BIND 1
#define ERR_LISTEN 2

static LIST_HEAD(g_id_list);

#define ID_MAX 10

struct person {
    char id[ID_MAX];
    int client_fd;
    struct list_head person_node;
};

static void tcp_server_handle(void *args)
{
    int client_fd = *(int *)args;
    uint8_t buff[BUFFER_SIZE];

    int n = recv(client_fd, buff, BUFFER_SIZE, 0);

    struct person *person = (struct person *)malloc(sizeof(*person));
    memcpy(person->id, buff, n);
    person->client_fd = client_fd;
    list_add(&person->person_node, &g_id_list);

    const char *msg = "login successful\n";
    send(client_fd, msg, strlen(msg), 0);

    for (;;) {
        int n = recv(client_fd, buff, BUFFER_SIZE, 0);

        buff[n] = '\0';

        /* When a stream socket peer has performed an orderly shutdown, the return value will be 0 (the traditional "end-of-file" return). */
        if (!n || strstr((const char *)buff, "off")) {
            /* power off */
            
            list_del(&person->person_node);
            free(person);

            const char *msg = "you out\n";
            send(client_fd, msg, strlen(msg), 0);

            goto POWER_OFF;
        }

        /* command 'list' handle */
        if (strstr((const char *)buff, "list")) {
            struct list_head *itr;
            list_for_each(itr, &g_id_list) {
                struct person *p = container_of(itr, struct person, person_node);

                send(client_fd, p->id, strlen(p->id), 0);
            }

            continue;
        }

        printf("%s\n", buff);

        /* msg broadcast */
        struct list_head *itr;
        list_for_each(itr, &g_id_list) {
            struct person *p = container_of(itr, struct person, person_node);

            char *msg = (char *)malloc(sizeof(msg) * strlen((char *)buff) + ID_MAX);

            memcpy(msg, person->id, strlen(person->id));
            msg[strlen(person->id) - 1] = ':'; // '\n' -> ':'
            msg[strlen(person->id)] = ' ';
            memcpy(msg + strlen(person->id) + 1, buff, strlen((char *)buff));
            msg[strlen(person->id) + strlen((char *)buff) + 1] = '\0';

            send(p->client_fd, msg, strlen(msg), 0);
        }
    }

POWER_OFF:
    close(client_fd);
}

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
    si.sin_port = htons(55559);

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
