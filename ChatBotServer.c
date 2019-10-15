#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include "ChatIndex.h" //delCmdAndSpace 정의

#define PORT 10000
#define SERVERMESSAGE "Hi, I'm server\n"
#define __BUFFSIZE 100
char rcvBuffer[__BUFFSIZE];
char * sendBuffer;

int main(){
	int c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int len;
	int n;
	char *delCmd[__BUFFSIZE];
	
	// 1. 서버 소켓 생성
	//서버 소켓 = 클라이언트의 접속 요청을 처리(허용)해 주기 위한 소켓
	s_socket = socket(PF_INET, SOCK_STREAM, 0); //TCP/IP 통신을 위한 서버 소켓 생성
	
	//2. 서버 소켓 주소 설정
	memset(&s_addr, 0, sizeof(s_addr)); //s_addr의 값을 모두 0으로  초기화
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY); //IP 주소 설정
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT);

	//3. 서버 소켓바인딩
	if(bind(s_socket,(struct sockaddr *) &s_addr, sizeof(s_addr)) == -1){ 
		//바인딩 작업 실패 시, Cannot Bind 메시지 출력 후 프로그램 종료
		printf("Cannot Bind\n");
		return -1;
	}
	
	//4.listen() 함수 실행
	if(listen(s_socket, 5) == -1){
		printf("listen Fail\n");
		return -1;
	}

	//5. 클라이언트 요청 처리
	// 요청을 허용한 후, Hello World 메세지를 전송함
	while(1){ //무한 루프
		len = sizeof(c_addr);
		printf("클라이언트 접속을 기다리는 중....\n");
		c_socket = accept(s_socket, (struct sockaddr *)&c_addr, &len); 
		//클라이언트의 요청이 오면 허용(accept)해 주고, 해당 클라이언트와 통신할 수 있도록 클라이언트 소켓(c_socket)을 반환함.
		printf("/client is connected\n");
		printf("클라이언트 접속 허용\n");
		//클라이언트입장시  메세지 전송
		write(c_socket,SERVERMESSAGE,strlen(SERVERMESSAGE));
		while(1){	//클라이언트가 보낸 메세지 받고 출력 반복
			
			memset(rcvBuffer,'\0',sizeof(rcvBuffer));
			n = read(c_socket, rcvBuffer, sizeof(rcvBuffer));
			printf("Client message : %s\n", rcvBuffer);
			//클라이언트에서 보낸 종료명령 확인
			if(strncmp(rcvBuffer, "quit", 4) == 0 || strncmp(rcvBuffer, "kill server", 11) == 0)
				break;
				//서버 대답 확인
			if(strcmp(rcvBuffer,"안녕하세요.\n")==0){
				sendBuffer = "안녕하세요. 만나서 반갑습니다.\n";
			}
			else if(strcmp(rcvBuffer,"이름이 머야?\n")==0){
				sendBuffer="내 이름은 XXX야.\n";
			}
			else if(strcmp(rcvBuffer,"몇 살이야?\n")==0){
				sendBuffer="나는 XX살이야\n";
			}
			else
				sendBuffer=rcvBuffer;//목록에 없으면 echo 기능수행

			//클라이언트 문자열 명령 입력
			if(strncmp(rcvBuffer,"strlen",6)==0){
				sendBuffer = delCmdAndSpace(rcvBuffer,"strlen");
				int length = strlen(sendBuffer)-1;//문자열끝 \n 세지않음
				sprintf(sendBuffer,"%d\n",length);
			}
			else if(strncmp(rcvBuffer,"strcmp",6)==0){
					sendBuffer = delCmdAndSpace(rcvBuffer,"strcmp");
					int result = ClientCmdCmp(sendBuffer);
					sprintf(sendBuffer,"%d\n",result);
					
			}
			else if(strncmp(rcvBuffer,"readfile",8)==0){
				sendBuffer = delCmdAndSpace(rcvBuffer,"readfile");
				rcvBuffer[n-1] = '\0'; //개행문자 제거
				FILE *fp = fopen(sendBuffer,"r");
				if(fp){
					char reader[BUFSIZ];
					if(fp){
						while(fgets(reader,BUFSIZ,(FILE *)fp)){
							printf("%s",reader);
							sendBuffer = reader;
						}
					}
				fclose(fp);
				}
				else
					sendBuffer = "no file\n";
			}
			else if(strncmp(rcvBuffer,"exec",4)==0){
				sendBuffer = delCmdAndSpace(rcvBuffer,"exec");
				int chk = system(sendBuffer);
				if(!chk)
					sendBuffer = ("command is executed\n");
				else
					sendBuffer = ("command failed\n");

			}
			n=strlen(sendBuffer);
			write(c_socket, sendBuffer, n); //클라이언트에게 buffer의 내용을 전송함
			printf("Server send : %s\n",sendBuffer);
		}

		close(c_socket);
		if (strncasecmp(rcvBuffer, "kill server", 11) == 0)
			break;
	}
	close(s_socket);
	return 0;	
}
