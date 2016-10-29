#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void *recvFn(void *param) {

    int sockfd = *static_cast<int *>(param);
    int n;
    char recvLine[4096];

    while (true) {
        n = recv(sockfd, recvLine, 4096, 0);
        recvLine[n] = '\0';
        printf("%s\n", recvLine);
        fflush(stdout);
    }

}

void *sendFn(void *param) {

    int sockfd = *static_cast<int *>(param);
    char sendLine[4096];

    while (true) {
        fgets(sendLine, 4096, stdin);
        sendLine[strlen(sendLine) - 1] = 0;
        if (sendLine[0] == 'q')
            break;
        send(sockfd, sendLine, strlen(sendLine), 0);
    }
    pthread_exit(0);

}

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
    n = recv(sockfd, recvline, 4096, 0);
    recvline[n] = '\0';
    printf("from server %s \n", recvline);

    pthread_t thread_recv, thread_send;
    pthread_create(&thread_recv, NULL, recvFn, &sockfd);
    pthread_create(&thread_send, NULL, sendFn, &sockfd);
    pthread_join(thread_send, NULL);    

    close(sockfd);
    return 0;
}
