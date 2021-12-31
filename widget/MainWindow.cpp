#include <Qlabel>
#include <Qwidget>
#include <QPushButton>

class MainWindow : public QWidget {
    public:
        MainWindow() {
            this->setFixedHeight(500);
            this->setFixedWidth(1000);
            this->setWindowTitle("聊天室");
            this->setFont(QFont("Microsoft JhengHei"));
        }
};