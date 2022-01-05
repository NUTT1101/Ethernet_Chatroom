#include <Qwidget>
#include <QListView>
#include <QListWidget>
#include <QGridLayout>

#include <QThread>

class ChatRoom : public QWidget {

    private:
        QListWidget *view = new QListWidget;
        
    public:
        ChatRoom(QWidget *parent);
        ~ChatRoom();
        QListWidget *getChatRoom();
        void sendMessage(std::string message);
};

ChatRoom::ChatRoom(QWidget *parent) {
    this->view->setFont(QFont("Microsoft JhengHei", 9));
    this->view->addItem("🟢 頁面初始化完成!!!");
    this->view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->view->setFixedWidth(950);
    this->view->setFixedHeight(350);
    this->view->setWordWrap(true);
    
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(this->view);

    this->setLayout(layout);
    this->setParent(parent);
}

ChatRoom::~ChatRoom() {}

QListWidget *ChatRoom::getChatRoom() {
    return this->view;
}

void ChatRoom::sendMessage(std::string message) {
    this->view->addItem(QString::fromStdString(message));
    
    this->view->scrollToBottom();
}
