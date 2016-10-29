#include "chatServer.h"

chatServer::chatServer(int p) {
    port = p;
}

chatServer::~chatServer(){}

void chatServer::initSock() {

    printf("hhh\n");
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    printf("%d\n", htonl(INADDR_ANY));

    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(listenfd, 10);
    printf("服务器启动监听。\n");

}

void chatServer::run() {

    initSock();

    while (true) {
        int connfd;
        char ret_buf[MAX_LINE_LEN];
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        snprintf(ret_buf, MAX_LINE_LEN, "welcome!");
        send(connfd, ret_buf, strlen(ret_buf), 0);
       // close(connfd);
    }

}
