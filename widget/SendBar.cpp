#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QComboBox>

class SendBar : public QWidget {
    private:
        QGridLayout *layout;    
        QLineEdit *messageLine;
        QPushButton *sendButton;
        QPushButton *thumbSupButton;
        QPushButton *emojisButton;
        QPushButton *selectFileButton;
        QWidget *parent;

    public:
        SendBar(QWidget *parent);
        ~SendBar();

        QLineEdit *getMessageLine();
        QPushButton *getSendButton();
        QPushButton *getThumbSupButton();
        QPushButton *getEmojisButton();
        QPushButton *getSelectFileButton();
};

SendBar::SendBar(QWidget *parent) {
    layout = new QGridLayout();    
    messageLine = new QLineEdit();
    sendButton = new QPushButton("發送");
    thumbSupButton = new QPushButton("👍");
    emojisButton = new QPushButton("傳圖片...");
    selectFileButton = new QPushButton("傳檔案...");

    this->parent = parent;
    this->messageLine->setFixedHeight(30);
    this->messageLine->setFixedWidth(600);

    this->sendButton->setFixedHeight(30);
    this->sendButton->setFixedWidth(100);

    this->thumbSupButton->setFixedHeight(30);
    this->thumbSupButton->setFixedWidth(40);
    
    this->emojisButton->setFixedHeight(30);
    this->emojisButton->setFixedWidth(80);

    this->selectFileButton->setFixedHeight(30);
    this->selectFileButton->setFixedWidth(100);

    this->layout->addWidget(this->messageLine, 0, 0, Qt::AlignLeft);
    this->layout->addWidget(this->sendButton, 0, 1, Qt::AlignLeft);
    this->layout->addWidget(this->thumbSupButton, 0, 2, Qt::AlignLeft);
    this->layout->addWidget(this->emojisButton, 0, 3, Qt::AlignLeft);
    this->layout->addWidget(this->selectFileButton, 0, 4, Qt::AlignLeft);
    
    this->setLayout(this->layout);
    this->setParent(this->parent);
}

SendBar::~SendBar() {}

QLineEdit *SendBar::getMessageLine() {
    return this->messageLine;
}

QPushButton *SendBar::getSendButton() {
    return this->sendButton;
}

QPushButton *SendBar::getThumbSupButton() {
    return this->thumbSupButton;
}
        
QPushButton *SendBar::getEmojisButton() {
    return this->emojisButton;
}

QPushButton *SendBar::getSelectFileButton() {
    return this->selectFileButton;
}