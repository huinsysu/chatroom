#include "chatServer.h"

chatServer::chatServer(int p) {
    port = p;

    for (int i = 0; i < MAX_THREAD_NUM; i++)
        connfd_arr[i] = -1;
}

chatServer::~chatServer(){}

void chatServer::initSock() {

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(listenfd, 10);
    printf("服务器启动监听。\n");

}

void *chatServer::talk_thread(void *param) {

    thread_para_t *thread_para = static_cast<thread_para_t *>(param);
    chatServer *p_session = thread_para->p_session;
    int connfd_index = thread_para->connfd_index;
    int connfd = p_session->connfd_arr[connfd_index];

    char message[MAX_LINE_LEN];
  
    while(true) {
        int mes_len = recv(connfd, message, MAX_LINE_LEN, 0);
        message[mes_len] = '\0';
        printf("%s\n", message);
      
        for (int i = 0; i < MAX_THREAD_NUM; i++) {
            if (p_session->connfd_arr[i] != -1) {
                printf("%d\n", connfd);
                send(p_session->connfd_arr[i], message, mes_len, 0);
            }
        }
    }

}

int chatServer::get_valid_connfd_index() {
    
    int i;
    for (i = 0; i < MAX_THREAD_NUM; i++) {
        if (connfd_arr[i] == -1)
            return i;
    }

}

void chatServer::run() {

    initSock();

    while (true) {
        int connfd;
        char ret_buf[MAX_LINE_LEN];
        thread_para_t *thread_para;
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

        printf("new user in %d\n", connfd);
        int connfd_index = get_valid_connfd_index();        
        connfd_arr[connfd_index] = connfd;

        thread_para = new thread_para_t;
        thread_para->p_session = this;
        thread_para->connfd_index = connfd_index;

        snprintf(ret_buf, MAX_LINE_LEN, "welcome!");
        send(connfd, ret_buf, strlen(ret_buf), 0);

        pthread_create(&thread[connfd_index], NULL, talk_thread, thread_para);

    }

}
