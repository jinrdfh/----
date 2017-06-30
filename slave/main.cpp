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

#include "protocol.h"
#include "socket.cpp"

int main()
{
    socket_init();

    /* 数据传输 */
    while(1)
    {


    /* 从buffer中拷贝出file_name */
    char file_name[FILE_NAME_MAX_SIZE+1];
    bzero(file_name,FILE_NAME_MAX_SIZE+1);
    char buffer[BUFFER_SIZE];
    socket_recv(buffer);
    strncpy(file_name, buffer, strlen(buffer)>FILE_NAME_MAX_SIZE?FILE_NAME_MAX_SIZE:strlen(buffer));
    printf("%s\n", file_name);
    }

    socket_close();
    return 0;
}
