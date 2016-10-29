#ifndef CHATSERVER_H_
#define CHATSERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>
#include <set>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAX_THREAD_NUM 100
#define MAX_LINE_LEN 4096

class chatServer {

    private:
        std::map<int, std::string> m_users;
        std::set<std::string> s_users;
        pthread_t thread[MAX_THREAD_NUM];
        struct sockaddr_in servaddr;
        int listenfd;
        int connfd_arr[MAX_THREAD_NUM];
        int cur_thread_num;
        int port;

    public:
        chatServer(int p);
        ~chatServer();
        void initSock();
        void run();
};

#endif
