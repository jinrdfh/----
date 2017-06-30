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

int server_socket_fd;

int socket_init()
{
    /* ����UDP�׽ӿ� */
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    /* ����socket */
    server_socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(server_socket_fd == -1)
    {
    perror("Create Socket Failed:");
    exit(1);
    }

    /* ���׽ӿ� */
    if(-1 == (bind(server_socket_fd,(struct sockaddr*)&server_addr,sizeof(server_addr))))
    {
    perror("Server Bind Failed:");
    exit(1);
    }


    return 0;
}

int socket_recv(char *buffer)
{
    /* ����һ����ַ�����ڲ���ͻ��˵�ַ */
    struct sockaddr_in client_addr;
    socklen_t client_addr_length = sizeof(client_addr);

     /* �������� */
    bzero(buffer, BUFFER_SIZE);
    if(recvfrom(server_socket_fd, buffer, BUFFER_SIZE,0,(struct sockaddr*)&client_addr, &client_addr_length) == -1)
    {
    perror("Receive Data Failed:");
    exit(1);
    }
    return 0;
}

int socket_close()
{
    close(server_socket_fd);
}
