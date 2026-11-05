/* Estimate speed of link between two processes using TCP socket */
#ifndef __SPD_H__
#define __SPD_H__

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/* 100 MB default payload */
#define DEFAULT_PAYLOAD_SIZE 100000000

int client(size_t payload_size, char *ip);
int server(size_t payload_size);
void help();

#endif
