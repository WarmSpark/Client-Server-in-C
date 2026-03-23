//
// Created by divyansh_1410 on 22/03/26.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>

void error(const char* mssg) {
    perror(mssg);
    exit(1);
}
int main(int argc,char* argv[]) {
    if (argc <2) {
        fprintf(stderr,"the port number is not defined");
        exit(1);
    }
    int sockfd,newsockfd,portno,n;
    char buffer[255];
    struct sockaddr_in serv_addr,cli_addr;
    socklen_t cllilen;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if (sockfd<0) {
        error("socket fails");
    }
    bzero((char*) &serv_addr,sizeof(serv_addr));
    portno=atoi(argv[1]);
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port=htons(portno);
    if (bind(sockfd,(struct sockaddr *)& serv_addr,sizeof(serv_addr))<0) {
        error("binding fails");
    }
    listen(sockfd,5);
    cllilen=sizeof(cli_addr);
    newsockfd= accept(sockfd,(struct sockaddr *)& cli_addr,&cllilen);
    if (newsockfd<0) {
        error("accept fails");
    }
    while(1) {
        bzero(buffer,255);
        n=read(newsockfd,buffer,255);
        if (n<0) {
            error("read fails");
        }
        printf("Client: %s\n",buffer);
        bzero(buffer,255);
        fgets(buffer,255,stdin);
        n=write(newsockfd,buffer,strlen(buffer));
        if (n<0) {
            error("write fails");
        }
        int i=strcmp("bye\n",buffer);
        if (i==0) {
            break;
        }
    }
    close(newsockfd);
    close(sockfd);
    return 0;
}