#ifndef FRONTEND_H
#define FRONTEND_H

#include "datawriter.h"
#include "parser.h"
#include "serverlog.h"
#include "backend.h"
#include "node.h"

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>


#define MAX_FILEPATH_LEN 512
#define MAXLINE 8192
#define BUFSIZE 1024
#define MAX_RANGE_NUM_LEN 32
#define SERVER_NAME "BBBserver"

/* max queueable requests for front end */
#define FE_MAX_CON_RQSTS 10

#define COM_BUF_DATA 1
#define COM_BUF_HDR 2
#define COM_BUF_DATA_FIN 3
#define COM_BUF_FIN 4
#define COM_BUFSIZE 1500

// BE_FLAGS
#define FILE_NOT_FOUND -1
#define SERVER_ERROR -2

extern pthread_mutex_t mutex;

/*
 * init_frontend
 *    - initializes FE's socket, builds Internet Address, and begins listening
 *
 *  ~ return:
 *
 *      sockfd - socket's file descriptor
 */
int init_frontend(short port_fe, struct sockaddr_in* self_addr);

/*
 * frontend_response
 *    - handles HTTP GET requests
 *
 *  ~ params:
 *
 *      connfd  - fd for reading/writing responses
 *      BUF     - GET request message buffer
 *      ct      - Client thread data struct
 */
void frontend_response(int connfd, char* BUF, struct thread_data *ct);

/*
 * fe_range_response
 *    - handles HTTP GET requests with Range headers
 *
 *  ~ params:
 *
 *      connfd  - fd for reading/writing responses
 *      BUF     - GET request message buffer
 *      ct      - Client thread data struct
 */
void fe_range_response(int connfd, char* BUF, struct thread_data *ct);






void handle_be_response(char* COM_BUF, int connfd, char* content_type);

#endif
