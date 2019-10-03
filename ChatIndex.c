#include "ChatIndex.h"


char * delCmdAndSpace(char * dest,char * cmmd){
	int cnt = 0;
	//명령어와 문자열에있는 문자열 비교
	while(*dest!='\0' && *cmmd!='\0' && *dest==*cmmd){
		cnt++;
		dest++;
		cmmd++;
	} //명령어와 문자열사이의 공백 제거
	while(*dest== ' ' || *cmmd == ' '){
		cnt++;
		dest++;
		cmmd++;
	}

	return dest;
}
	//클라이언트가 보내준 메세지 비교하는함수
int ClientCmdCmp(char *str){
	int result;
	char *token1 = strtok(str," ");
	str = strtok(NULL,"\n");
	result = strcmp(token1,str);
	return result;

}
