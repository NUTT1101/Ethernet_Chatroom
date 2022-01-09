#include <pcap.h>
#include <QThread>
#include <QTextBrowser>
#include <string>
#include <sstream>
#include <QMap>
#include <QDir>

class ChatRoomThread : public QThread {
    Q_OBJECT

    private:
        QTextBrowser *view;

    public: 
        ChatRoomThread(QTextBrowser *view);
        ~ChatRoomThread();

    protected:
        void run();
};
