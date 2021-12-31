#include <Qwidget>
#include <QStringList>
#include <QAbstractItemModel>
#include <QStringListModel>
#include <QListView>
#include <QListWidget>
#include <QGridLayout>

#include <QThread>

class ChatRoom : public QWidget {

    private:
        QStringList message;
        
    public:
        ChatRoom(QWidget *parent) {
            QListWidget *view = new QListWidget;
            view->setAutoScroll(true);

            for (int i=0; i < 1000; i++) {
                view->addItem(QVariant(i).toString());
            }


            view->setEditTriggers(QAbstractItemView::NoEditTriggers);

            view->setFixedWidth(800);
            view->setFixedHeight(350);
            
            QGridLayout *layout = new QGridLayout();
            layout->addWidget(view);

            this->setLayout(layout);
            this->setParent(parent);
        }
};