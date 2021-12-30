#include <QObject>
#include <pcap.h>

class OpenButtonClick : public QObject {
    Q_OBJECT

    private:
        pcap_t *openedInterface;

    public slots:
        void openInterface();        

    public:
        OpenButtonClick();
        ~OpenButtonClick();
        pcap_t *getOpenedInterface();
};