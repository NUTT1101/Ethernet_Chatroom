#include "./OpenButtonClick/OpenButtonClick.hpp"
#include "../ThreadControl/ChatRoomThread.cpp"

OpenButtonClick::OpenButtonClick() {};
OpenButtonClick::~OpenButtonClick() {};

void OpenButtonClick::openInterface() {
    if (global_openedInterface == nullptr) {
        QMap<QString, QString> allDevices = menu->getAllDevicesMap();
        QString selectInterfaceDes = menu->getInterfaceMenu()->currentText();
        QString selectInterfaceName = allDevices[selectInterfaceDes];
        
        char open_interface[100];
        char errbuf[100];

        for (int i=0; i < 100; i++) {
            open_interface[i] = (char) selectInterfaceName.at(i).unicode();
        }
        
        /* 打開要監聽的介面 */
        this->openedInterface = pcap_open(open_interface,			// 監聽設備名稱
                            1500,				// portion of the packet to capture (only the first 100 bytes)
                            PCAP_OPENFLAG_PROMISCUOUS, 	// promiscuous mode
                            100,				// 讀取最大逾時
                            NULL,				// authentication on the remote machine
                            errbuf				// 錯誤訊息存放
                            );
        menu->getOpenButton()->setText("關閉");
        menu->getInterfaceMenu()->setEnabled(false);

        if (this->openedInterface != NULL) {
            QMessageBox::information(mainWindow, "Information", 
                "<h3>介面成功開啟介面，你現在可以開始聊天了!</h3>", QMessageBox::Ok);
            global_openedInterface = this->openedInterface;
        }

        ChatRoomThread *c = new ChatRoomThread(chatRoom->getChatRoom());
        c->start();
        
    } else if (global_openedInterface != nullptr) {
        pcap_close(global_openedInterface);
        global_openedInterface = nullptr;
        menu->getOpenButton()->setText("開啟");
        menu->getInterfaceMenu()->setEnabled(true);

        QMessageBox::information(mainWindow, "訊息", 
            "<h3>介面關閉成功!</h3>", QMessageBox::Ok);
    }
    
}