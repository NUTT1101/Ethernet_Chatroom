#include <QObject>
#include <pcap.h>
#include <QFileDialog>

class EmojiButtonClick : public QObject{
    Q_OBJECT

    public slots:
        void selectEmoji();

    public:
        EmojiButtonClick();
        ~EmojiButtonClick();
};
