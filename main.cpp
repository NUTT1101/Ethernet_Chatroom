#include "global.hpp"
#include "./event/OpenButtonClickEvent.cpp"
#include "./event/CloseButtonClickEvent.cpp"
#include "./event/SendButtonClickEvent.cpp"
#include "./event/MessageLineEnterPressEvent.cpp"
#include "./event/EmojiButtonClickEvent.cpp"
#include "./event/SelectFileButtonClickEvent.cpp"
#include "./event/ThumbSupButtonClickEvent.cpp"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    mainWindow = new MainWindow();
    sendBar = new SendBar(mainWindow);
    menu = new InterfaceDropDownMenu(mainWindow);
    chatRoom = new ChatRoom(mainWindow);

    OpenButtonClick openButton;
    CloseButtonClick closeButton;
    SendButtonClick sendButton;
    MessageLineEnterPress enterPress;
    ThumbSupButtonClick thumpSupClick;
    EmojiButtonClick emojiClick;
    SelectFileButtonClick selectFileClick;
    
    QObject::connect(menu->getOpenButton(), SIGNAL(clicked()), &openButton, SLOT(openInterface()));
    QObject::connect(menu->getCloseButton(), SIGNAL(clicked()), &closeButton, SLOT(closeInterface()));
    QObject::connect(sendBar->getSendButton(), SIGNAL(clicked()), &sendButton, SLOT(sendMessage()));
    QObject::connect(sendBar->getMessageLine(), SIGNAL(returnPressed()), &enterPress, SLOT(clickSendButton()));
    QObject::connect(sendBar->getThumbSupButton(), SIGNAL(clicked()), &thumpSupClick, SLOT(sendThumbSup()));
    QObject::connect(sendBar->getEmojisButton(), SIGNAL(clicked()), &emojiClick, SLOT(selectEmoji()));
    QObject::connect(sendBar->getSelectFileButton(), SIGNAL(clicked()), &selectFileClick, SLOT(selectFile()));
    

    QGridLayout *layout = new QGridLayout();
    layout->addWidget(menu, 0, 0, Qt::AlignTop);
    layout->addWidget(chatRoom, 1, 0, Qt::AlignLeft);
    layout->addWidget(sendBar, 2, 0, Qt::AlignBottom);
    mainWindow->setLayout(layout);
    
    mainWindow->show();

    while (userName == "") {
        QString name = QInputDialog::getText(mainWindow, "輸入欄", "輸入您的名字: ");
        if (name.size() > 10) continue;
        
        for (int i=0; i < name.size(); i++) {
            userName[i] = name.at(i).unicode();
        }
    }
    
    return app.exec();
}

