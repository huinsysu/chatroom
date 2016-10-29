#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char** argv) {

    int sockfd, n;
    char recvline[4096];
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(7894);
    inet_pton(AF_INET, "172.18.71.129", &servaddr.sin_addr);

    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    while (true) {
    n = recv(sockfd, recvline, 4096, 0);
    recvline[n] = '\0';
    printf("from server %s \n", recvline);
    close(sockfd);
    break;
    }

}
