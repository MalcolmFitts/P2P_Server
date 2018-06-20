/*  (Version: p2)
 *  serverlog.c 
 *    - created for use with "bbbserver.c"
 *    - implementations of server logging functions
 *    - documentation/usage notes in "serverlog.h"
 *    - constants defined in "serverlog.h"
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "serverlog.h"
#include "configlib.h"




void log_ip_info(char* cf) {
  /* IP Resolution variables */
  struct hostent *hostp;
  char hostaddrp[256];
  char* ip_buf;

  char* cf_p_fe = NULL;
  char* cf_p_be = NULL;
  int p_fe = CF_DEFAULT_FE_PORT;
  int p_be = CF_DEFAULT_BE_PORT;

  /* Retrieving hostname, info and IP representation */
  if(gethostname(hostaddrp, sizeof(hostaddrp)) == -1) { exit(0); }
  hostp = gethostbyname(hostaddrp);

  if(hostp == NULL) { exit(0); }
  ip_buf = inet_ntoa(*((struct in_addr*) hostp->h_addr_list[0]));

  cf_p_fe = get_config_field(cf, CF_TAG_FE_PORT, 0);
  cf_p_be = get_config_field(cf, CF_TAG_BE_PORT, 0);
  if(cf_p_fe)  { p_fe = atoi(cf_p_fe); }
  if(cf_p_be)  { p_be = atoi(cf_p_be); }


  printf("Machine Hostname:\t%s\n", hostaddrp);
  printf("Machine Host IP:\t%s\n", ip_buf);
  printf("Front-End Port:\t\t%d\n", p_fe);
  printf("Back-End port:\t\t%d\n", p_be);
  printf("\n");
}


void log_config_info(char* cf) {
  if(validate_config_file(cf) != 1) {
    printf("Error: invalid config file.\n");
    exit(0);
  }

  char* n_p_str = NULL;
  int n_peers = CF_DEFAULT_PEER_COUNT;

  n_p_str = get_config_field(cf, CF_TAG_PEER_COUNT, 0);
  if(n_p_str) { n_peers = atoi(n_p_str); }

  printf("Config File's Filepath:\t%s\n", cf);
  printf("Config File info:\n");
  printf("\tUUID:\t\t%s\n", get_config_field(cf, CF_TAG_UUID, 0));
  printf("\tNode Name:\t%s\n", get_config_field(cf, CF_TAG_NAME, 0));
  printf("\tContent Dir:\t%s\n", get_config_field(cf, CF_TAG_CONTENT_DIR, 0));
  printf("\tPeer Count:\t%d\n", n_peers);
  for(int i = 0; i < n_peers; i++) {
    printf("\tPeer #%d Info:\t%s\n", 
          i, get_config_field(cf, CF_TAG_PEER_INFO, i));
  }
  printf("\n");
}

void log_startup(char* sn, char* cf, int lvl) {
  /* Silent log: lvl == 0 */
  /* Normal log: lvl == 1 */
  /* Debug log : lvl == 2 */
  char log_lvl_str[100];
  char buf[100];

  if      (lvl == 0) { sprintf(log_lvl_str, "%s", LOG_LEVEL_S); }
  else if (lvl == 1) { sprintf(log_lvl_str, "%s", LOG_LEVEL_R); }
  else if (lvl == 2) { sprintf(log_lvl_str, "%s", LOG_LEVEL_H); }
  else {
    printf("Invalid Server Log Level Option.\n");
    printf("Must be 0 (silent), 1 (regular) or 2 (debug).\n");
    exit(0);
  }

  sprintf(buf, "%s", "|----------------------------------------------------------------|");
  /* Start-up info: */
  printf("\n%s\n", buf);
  printf("|-------->\t%s start-up info\t\t\t<--------|\n", sn);
  printf("|-------->\tTerminal Log Verbostiy Level: %s\t<--------|\n\n", log_lvl_str);
  
  /* Regular log: IP info */
  if(lvl == 1) { log_ip_info(cf); }

  /* Debug log: IP and Config info */
  else if(lvl == 2) { 
    log_ip_info(cf);
    log_config_info(cf); 
  }
  
  printf("|-------->\tEnd of %s start-up info\t\t<--------|\n", sn);
  printf("%s\n\n", buf);
}





void log_msg(char* msg) {
  printf("%s\n", msg);
}

void log_main(char* msg, int c) {
  char buf[MAX_PRINT_LEN];
  bzero(buf, MAX_PRINT_LEN);
  sprintf(buf, "(m:%d)", c);
  server_log(msg, buf);
}

void log_thr(char* msg, int c, int t) {
  char buf[MAX_PRINT_LEN];
  bzero(buf, MAX_PRINT_LEN);
  sprintf(buf, "(m:%d)(t:%d)", c, t);
  server_log(msg, buf);
}

void log_req(char* msg, int c, int t, int r) {
  char buf[MAX_PRINT_LEN];
  bzero(buf, MAX_PRINT_LEN);
  sprintf(buf, "(m:%d)(t:%d)(r:%d)", c, t, r);
  server_log(msg, buf);
}

void server_log(char* message, char* db) {
  
  if(DB_LOG == 2) {
    char buf[MAX_PRINT_LEN];
    bzero(buf, MAX_PRINT_LEN);
    sprintf(buf, "db_%s: %s", db, message);
    printf("%s\n", buf);
  }
  if(DB_LOG == 1) {
    //sprintf(buf, "%s ", message);
    printf("%s\n", message);
  }
  //bzero(message, sizeof(message));
}