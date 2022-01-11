#include <Qwidget>
#include <QTextBrowser>
#include <QGridLayout>
#include <QScrollBar>
#include <QThread>

class ChatRoom : public QWidget {

    private:
        QTextBrowser *view;
        
    public:
        ChatRoom(QWidget *parent);
        ~ChatRoom();
        QTextBrowser *getChatRoom();
        void sendMessage(std::string message);
};

ChatRoom::ChatRoom(QWidget *parent) {
    view = new QTextBrowser();
    
    this->view->setFont(QFont("Microsoft JhengHei", 10));
    this->view->append("🟢 頁面初始化完成!!!");

    this->view->setFixedWidth(950);
    this->view->setFixedHeight(550);

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(this->view);
    this->setLayout(layout);
    this->setParent(parent);
}

ChatRoom::~ChatRoom() {}

QTextBrowser *ChatRoom::getChatRoom() {
    return this->view;
}

void ChatRoom::sendMessage(std::string message) {
    QString m = QString::fromStdString(message);
    this->view->append(m);
}
