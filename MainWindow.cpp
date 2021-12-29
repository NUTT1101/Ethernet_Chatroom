#include <Qlabel>
#include <Qwidget>
#include <QPushButton>

class MainWindow : public QWidget {
    private:

    public:
        MainWindow() {
            this->setFixedHeight(500);
            this->setFixedWidth(1000);
            this->setWindowTitle("聊天室");
        }
};