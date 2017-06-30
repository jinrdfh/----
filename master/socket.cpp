#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <stdarg.h>
#include <string.h>


int client_socket_fd;
struct sockaddr_in server_addr;

int socket_init()
{
    /* 服务端地址 */
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(INET_ADDR);
    server_addr.sin_port = htons(SERVER_PORT);

    /* 创建socket */
    client_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(client_socket_fd < 0)
    {
    perror("Create Socket Failed:");
    exit(1);
    }

    return 0;
}

int socket_send(char *buffer)
{
    if(sendto(client_socket_fd, buffer, BUFFER_SIZE,0,(struct sockaddr*)&server_addr,sizeof(server_addr)) < 0)
    {
    perror("Send File Name Failed:");
    exit(1);
    }
}

int socket_close()
{
    close(client_socket_fd);
    return 0;
}
