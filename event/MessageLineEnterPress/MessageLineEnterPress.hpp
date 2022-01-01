#include <QObject>

class MessageLineEnterPress : public QObject{
    Q_OBJECT

    public slots:
        void clickSendButton();

    public:
        MessageLineEnterPress();
        ~MessageLineEnterPress();
};
