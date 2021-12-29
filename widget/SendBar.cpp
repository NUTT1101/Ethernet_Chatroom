#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>

class SendBar : public QWidget {
    
    public:
        SendBar(QWidget *parent) {
            QGridLayout *layout = new QGridLayout;
            
            QLineEdit *messageLine = new QLineEdit;
            QPushButton *button = new QPushButton("Send");

            messageLine->setFixedHeight(30);
            messageLine->setFixedWidth(600);

            button->setFixedHeight(30);
            button->setFixedWidth(100);

            layout->addWidget(messageLine, 0, 0, Qt::AlignLeft);
            layout->addWidget(button, 0, 1, Qt::AlignLeft);
            
            this->setLayout(layout);
            this->setParent(parent);
        }

};