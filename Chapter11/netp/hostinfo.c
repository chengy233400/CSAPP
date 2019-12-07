
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
int main(void){

	const char *host = "www.baidu.com";
	const char *service = NULL;
	struct addrinfo *hints = malloc(sizeof(struct addrinfo));

	struct addrinfo *listp = NULL;

	memset(hints,0,sizeof(struct addrinfo));
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_STREAM;

	int resCode = getaddrinfo(host,service,hints,&listp);
	if(resCode == 0){
		struct addrinfo *p = listp;
		char dstStr[INET_ADDRSTRLEN];
		getnameinfo(p->ai_addr,p->ai_addrlen,dstStr,INET_ADDRSTRLEN,NULL,0,NI_NUMERICHOST);
		printf("%s\n",dstStr);
	}

	freeaddrinfo(listp);
	return 0;
}