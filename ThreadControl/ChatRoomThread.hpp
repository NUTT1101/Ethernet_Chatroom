#include <QThread>
#include <QTextBrowser>
#include <pcap.h>

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
