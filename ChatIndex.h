#ifndef __CHATBOT_INDEX_H__
#define __CHATBOT_INDEX_H__

#include <string.h>
#define SERVERMESSAGE "Hi, I'm server\n"
#define __BUFFSIZE 100

char * delCmdAndSpace(char * dest,char * cmmd);
int ClientCmdCmp(char *str);
#endif
