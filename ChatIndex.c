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
