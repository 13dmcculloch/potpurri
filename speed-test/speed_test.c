/* Estimate speed of link between two processes using TCP socket */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "speed_test.h"

/* 100 MB default payload */
#define DEFAULT_PAYLOAD_SIZE 100000000

int server(size_t payload_size)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    struct sockaddr_in s;
    s.sin_family = AF_INET;
    s.sin_port = htons(5118);
    s.sin_addr.s_addr = INADDR_ANY;
    socklen_t s_len = sizeof(s);

    bind(socket_fd, (struct sockaddr *)&s, s_len);
    listen(socket_fd, 2);
    int client_socket = accept(socket_fd, (struct sockaddr *)&s, &s_len);

    char *payload = malloc(payload_size);

    struct timespec start, end;
    size_t n = 0;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    while(n < payload_size)
    {
        n += read(client_socket, payload + n, payload_size);
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    close(client_socket);

    float duration_usec = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
    printf("Duration: %f us\n", duration_usec);
    printf("Bytes transferred: %f MB\n", (payload_size / 1e6));
    
    float payload_bit = payload_size * 8.0;
    float transfer_speed_mbps = payload_bit / duration_usec;

    printf("Transfer speed = %f Mb/s\n", transfer_speed_mbps);

    free(payload);

    return 0;
}

int client(size_t payload_size, char *ip)
{
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    size_t n = 0;

    struct sockaddr_in s;
    s.sin_family = AF_INET;
    s.sin_port = htons(5118);
    s.sin_addr.s_addr = inet_addr(ip);
    socklen_t s_len = sizeof(s);

    char *payload = malloc(payload_size);
    int random = open("/dev/random", O_RDONLY);
    while(n < payload_size)
    {
        n += read(random, payload, payload_size);
    }

    int rc = connect(client_fd, (struct sockaddr *)&s, s_len);
    if(rc < 0)
    {
        return -1;
    }


    n = 0;
    while(n < payload_size)
    {
        n += write(client_fd, payload + n, payload_size);
    }

    close(client_fd);
    free(payload);

    return 0;
}

void help()
{
    fprintf(stderr, "Usage:\nspeed_test -s [payload_size]\nspeed_test -c [payload_size] ip\nwhere payload_size is optional.\n");
}

int main(int argc, char **argv)
{
    unsigned long long custom_size;
    custom_size = 0;

    if(argc > 4 || argc < 2) 
    {
        help();
        return 1;
    }

    if(argv[1][1] == 's')
    {
        if(argc == 3) custom_size = strtoull(argv[2], NULL, 10);
        if(custom_size) return server(custom_size);
        else return server(DEFAULT_PAYLOAD_SIZE);
    }
    else if(argv[1][1] == 'c')
    {
        if(argc == 4) custom_size = strtoull(argv[2], NULL, 10);
        if(custom_size) return client(custom_size, argv[3]);
        else return client(DEFAULT_PAYLOAD_SIZE, argv[2]);
    }
    else
    {
        help();
        return 1;
    }

    return 0;
}
