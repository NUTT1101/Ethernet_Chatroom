#include <QThread>
#include <QListWidget>

class ChatRoomThread : public QThread {
    Q_OBJECT

    private:
        QListWidget *view;

    public: 
        ChatRoomThread(QListWidget *view);
        ~ChatRoomThread();

    protected:
        void run();
};
