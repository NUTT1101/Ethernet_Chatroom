#include <QObject>

class SendButtonClick : public QObject {
    Q_OBJECT

    public slots:
        void sendMessage();

    public:
        SendButtonClick();
        ~SendButtonClick();
};