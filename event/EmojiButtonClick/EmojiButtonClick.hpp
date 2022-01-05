#include <QObject>

class EmojiButtonClick : public QObject{
    Q_OBJECT

    public slots:
        void selectEmoji();

    public:
        EmojiButtonClick();
        ~EmojiButtonClick();
};
