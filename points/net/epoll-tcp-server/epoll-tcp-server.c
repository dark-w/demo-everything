#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define __UNUSED__ __attribute__((unused))

#define BUFFER_SIZE 1024

#define ERR_BIND 1
#define ERR_LISTEN 2

#define MAX_EVENTS 10

static void tcp_server_handle(int client_fd)
{
    uint8_t buff[BUFFER_SIZE];

    int n = recv(client_fd, buff, BUFFER_SIZE, 0);

    /* When a stream socket peer has performed an orderly shutdown, the return value will be 0 (the traditional "end-of-file" return). */
    if (!n)
        goto POWER_OFF;

    /* power off */
    buff[n] = '\0';
    if (strstr((const char *)buff, "POWER_OFF"))
        goto POWER_OFF;

    send(client_fd, buff, n, 0);

    return;

POWER_OFF:
    close(client_fd);
    return;
}

static int tcp_server_run(char *ip)
{
    struct epoll_event ev, events[MAX_EVENTS];
    int listen_sock, conn_sock, nfds, epollfd;

    /* Code to set up listening socket, 'listen_sock',
       (socket(), bind(), listen()) omitted */

    listen_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in si;
    char buff[BUFFER_SIZE];

    memset(&si, 0, sizeof(si));
    memset(buff, 0, sizeof(buff));
    si.sin_family = PF_INET;
    si.sin_addr.s_addr = inet_addr(ip);
    si.sin_port = htons(55557);

    if (-1 == bind(listen_sock, (struct sockaddr *)&si, sizeof(si)))
        return ERR_BIND;

    if (-1 == listen(listen_sock, 5))
        return ERR_LISTEN;

    epollfd = epoll_create1(0);
    if (epollfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;
    ev.data.fd = listen_sock;
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {
        perror("epoll_ctl: listen_sock");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    socklen_t addrlen = sizeof(addr);

    for (;;) {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (int n = 0; n < nfds; ++n) {
            if (events[n].data.fd == listen_sock) {
                conn_sock =
                    accept(listen_sock, (struct sockaddr *)&addr, &addrlen);
                if (conn_sock == -1) {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }

                // setnonblocking(conn_sock);
                int status = fcntl(conn_sock, F_SETFL,
                                   fcntl(conn_sock, F_GETFL, 0) | O_NONBLOCK);

                if (status == -1) {
                    perror("calling fcntl");
                    // handle the error.  By the way, I've never seen fcntl fail in this way
                }

                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = conn_sock;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
                    perror("epoll_ctl: conn_sock");
                    exit(EXIT_FAILURE);
                }
            } else {
                tcp_server_handle(events[n].data.fd);
            }
        }
    }

    //    close(listen_sock);
    return 0;
}

int main(int argc, char **argv)
{
    return tcp_server_run(argv[1]);
}
