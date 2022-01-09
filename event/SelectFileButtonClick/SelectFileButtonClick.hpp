#include <QObject>
#include <QFileDialog>
#include <pcap.h>

class SelectFileButtonClick : public QObject {
    Q_OBJECT

    public slots:
        void selectFile();
        
    public:
        SelectFileButtonClick();
        ~SelectFileButtonClick();
};