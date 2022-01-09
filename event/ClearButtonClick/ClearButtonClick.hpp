#include <QObject>
#include <pcap.h>
#include <QMessageBox>

class ClearButtonClick : public QObject {
    Q_OBJECT

    private:
        bool status;

    public slots:
        void clearChatRoom();        

    public:
        ClearButtonClick();
        ~ClearButtonClick();
};