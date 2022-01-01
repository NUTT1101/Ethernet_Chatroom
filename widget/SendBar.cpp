#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QKeyEvent>
#include <QMessageBox>

class SendBar : public QWidget {
    private:
        QGridLayout *layout = new QGridLayout;    
        QLineEdit *messageLine = new QLineEdit;
        QPushButton *button = new QPushButton("Send");
        QWidget *parent;

    public:
        SendBar(QWidget *parent);
        ~SendBar();
        QLineEdit *getMessageLine();
        QPushButton *getSendButton();
        void testEvent(QKeyEvent *event);
};

SendBar::SendBar(QWidget *parent) {
    this->parent = parent;
    this->messageLine->setFixedHeight(30);
    this->messageLine->setFixedWidth(600);

    this->button->setFixedHeight(30);
    this->button->setFixedWidth(100);

    this->layout->addWidget(this->messageLine, 0, 0, Qt::AlignLeft);
    this->layout->addWidget(this->button, 0, 1, Qt::AlignLeft);
    
    this->setLayout(this->layout);
    this->setParent(this->parent);
}

SendBar::~SendBar() {}

QLineEdit *SendBar::getMessageLine() {
    return this->messageLine;
}

QPushButton *SendBar::getSendButton() {
    return this->button;
}