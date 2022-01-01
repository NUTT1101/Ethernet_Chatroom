#include "ChatRoomThread.cpp"

ChatRoomThread::ChatRoomThread(QListWidget *view) {
    this->view = view;
}

ChatRoomThread::~ChatRoomThread() {}

void ChatRoomThread::run() {
    while (true) {
        QThread::sleep(1);
    }
}
