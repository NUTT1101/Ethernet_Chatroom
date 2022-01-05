#include <QObject>
#include <pcap.h>

class ThumbSupButtonClick : public QObject{
    Q_OBJECT

    public slots:
        void sendThumbSup();

    public:
        ThumbSupButtonClick();
        ~ThumbSupButtonClick();
};