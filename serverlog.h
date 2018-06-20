/*  (Version: p2)
 *  serverlog.h 
 *    - created for use with "bbbserver.c"
 *    - prototypes of server logging functions
 *    - contains documentation/usage notes and constant definitions
 */

#ifndef SERVERLOG_H
#define SERVERLOG_H

#include <string.h>
#include <stdio.h>

/* 
 *  debug flag for server log (DB_LOG)
 *    - set value to 2 for debug log
 *    - set value to 1 for regular log
 *	  - ser value to 0 for no log
 */

 #define DB_LOG 1
 
#define LOG_LEVEL_H "HIGH (db)" 
#define LOG_LEVEL_R "REGULAR"
#define LOG_LEVEL_S "SILENT"

#define MAX_PRINT_LEN 1024




void log_ip_info(char* cf);




/*
 *  log_config_info
 *    - logs info from the input config filename
 *
 *    ~ params:
 *        cf   - config filename 
 *                  (format ex: "config/node.conf")
 */
void log_config_info(char* cf);


/*
 *  log_startup:
 *  
 *    ~ params:
 *        sn   - Server name (from bbbserver.c)
 *        cf   - config filename (with config/<fn> format)
 *        p_fe - front-end port
 *        p_be - back-end port
 *        lvl  - level of verbosity for log
 *              > Silent log: lvl == 0 
 *              > Normal log: lvl == 1 
 *              > Debug log : lvl == 2 
 *
 */
void log_startup(char* sn, char* cf, int lvl);



/*
 *	log_msg
 *    - created for use in bbbserver.c main fn
 *	  - logs msg with no extra debug data
 *    - internally calls server_log fn
 */
void log_msg(char* msg);

/*
 *	log_main
 *    - created for use in bbbserver.c main fn
 *	  - logs msg and uses c as debug data
 *    - internally calls server_log fn
 */
void log_main(char* msg, int c);

/*
 *	log_thr
 *    - created for use in bbbserver.c serve_client_thread fn
 *	  - logs msg and uses c and t as debug data
 *    - internally calls server_log fn
 */
void log_thr(char* msg, int c, int t);


 /*	log_req
 *    - created for use in bbbserver.c serve_client_thread fn,
 *        when handling multiple requests from client
 *	  - logs msg and uses c, t and r as debug data
 *    - internally calls server_log fn
 */
 
void log_req(char* msg, int c, int t, int r);

/*
 *	server_log
 *    - created for use in bbbserver.c
 *	  - logs message and debug info depending on defined flags (DB_LOG and LOG)
 *    - DB_LOG = 2 --> logs concatenation of db and message
 *	  - DB_LOG = 1 --> logs message
 *	  - DB_LOG = 0 --> logs nothing 
 */
void server_log(char* message, char* db);

#endif
