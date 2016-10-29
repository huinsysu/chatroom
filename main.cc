#include "chatServer.cc"

int main(int argc, char** argv) {

    chatServer *chat = new chatServer(7894);
    chat->run();
    return 0;

}
