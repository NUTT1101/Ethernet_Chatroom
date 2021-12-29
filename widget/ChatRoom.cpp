#include <Qwidget>
#include <QStringList>
#include <QAbstractItemModel>
#include <QStringListModel>
#include <QListView>
#include <QGridLayout>

class ChatRoom : public QWidget {

    public:
        ChatRoom(QWidget *parent) {
            QStringList message;
            
            QAbstractItemModel *model = new QStringListModel(message);
            
            QListView *view = new QListView;
        
            view->setFixedWidth(1000);
            view->setFixedHeight(350);
            view->setEditTriggers(QAbstractItemView::NoEditTriggers);
            view->setModel(model);
            
            QGridLayout *layout = new QGridLayout();
            layout->addWidget(view);

            this->setLayout(layout);
            this->setParent(parent);
        }

};