#include <QObject>
#include <pcap.h>
#include <QMessageBox>

class CloseButtonClick : public QObject {
    Q_OBJECT

    private:
        bool status;

    public slots:
        void closeInterface();        

    public:
        CloseButtonClick();
        ~CloseButtonClick();
};