#include <QObject>
#include <pcap.h>

class OpenButtonClick : public QObject {
    Q_OBJECT

    private:
        pcap_t *opened_interface;
        char *errBuffer;

    public slots:
        void openInterface();        

    public:
        OpenButtonClick();
        ~OpenButtonClick();
};