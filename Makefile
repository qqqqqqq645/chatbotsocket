server : ChatBotServer.o ChatIndex.o
	gcc -o ChatBotServer ChatBotServer.o ChatIndex.o
chatBotServer.o : ChatBotServer.c
	gcc -c ChatBotServer.c
ChatIndex.o : ChatIndex.c
