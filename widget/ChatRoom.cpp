#include <Qwidget>
#include <QStringList>
#include <QAbstractItemModel>
#include <QStringListModel>
#include <QListView>
#include <QGridLayout>

#include <QThread>

class ChatRoom : public QWidget {

    private:
        QStringList message;
        
    public:
        ChatRoom(QWidget *parent) {

            QAbstractItemModel *model = new QStringListModel(this->message);
            
            QListView *view = new QListView;
        
            view->setEditTriggers(QAbstractItemView::NoEditTriggers);
            view->setModel(model);
            view->setFixedWidth(1000);
            view->setFixedHeight(350);
            
            QGridLayout *layout = new QGridLayout();
            layout->addWidget(view);

            this->setLayout(layout);
            this->setParent(parent);
        }
};