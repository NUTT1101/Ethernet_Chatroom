#include "./SelectFileButtonClick/SelectFileButtonClick.hpp"
#include <QFileDialog>
#include <QMessageBox>
#include <pcap.h>

SelectFileButtonClick::SelectFileButtonClick() { }
SelectFileButtonClick::~SelectFileButtonClick() { }

void SelectFileButtonClick::selectFile() {
    QString fileName = QFileDialog::getOpenFileName(mainWindow,
        tr("選擇一個圖檔"), "C:/", tr("Image Files (*)"));

    if (global_openedInterface == nullptr) {
        return;
    }
    
    u_char packet[1500] = {'\0'};

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(mainWindow, "錯誤", "檔案開啟錯誤", QMessageBox::Ok);
        file.close();
        return;
    }
    
    QByteArray fileByteArray = file.readAll();
    
    for (int i=0; i < 6; i++) {
        packet[i] = 0xff;
    }
    
    for (int i=6; i < 12; i++) {
        packet[i] = i + 4;
    }
    
    packet[12] = 0xff;
    packet[13] = 14; // 組別編號
    
    // 把輸入的訊息裝進封包內

    int packetLength = fileByteArray.size();

    packet[16] = number / 256; // 封包編號，用於紀錄用
    packet[17] = number % 256; // 封包編號，用於紀錄用
    packet[19] = 1;

    // 檔名傳進去
    QString fileNameS = QFileInfo(file).baseName();

    int j;
    for (j=20; j < fileNameS.size() + 20; j++) {
        packet[j] = fileNameS.at(j - 20).unicode();
    }

    packet[j++] = '\0';

    QString fileEx = QFileInfo(file).completeSuffix();
    if (fileEx.contains('.')) {
        fileEx.replace('.', '\0');
    }

    int a;
    for (a=j; a < fileEx.size() + j; a++) {
        packet[a] = fileEx.at(a - j).unicode();
    }

    packet[a++] = '\0';

    int b;
    QByteArray userNameUtf8 = userName.toUtf8();
    for (b = a; b < userNameUtf8.size() + a; b++) {
        packet[b] = userNameUtf8.at(b - a);
    }
    packet[b++] = '\0';

    int packetParameterLength = b;

    pcap_sendpacket(global_openedInterface, packet, packetParameterLength);

    if (packetLength > 1500) {
        int packetTotalLength = packetLength;
        int currentMessage = 20;
        packet[18] = 0;

        while (packetTotalLength > 0) {
            int currentLength = packetTotalLength > 1500 ? 1500 : packetTotalLength + 20;
            for (int i = 20; i < currentLength; i++) {
                packet[i] = (char) fileByteArray.at(currentMessage++ - 20);
            }

            pcap_sendpacket(global_openedInterface, packet, currentLength);
            packetTotalLength -= 1480;
            
            packet[18] = packetTotalLength < 1500 ? 1 : 0;
        }
        
    } else {
        packet[18] = 1;
        for (int i = 20; i < packetLength + 20; i++) {
            packet[i] = fileByteArray[i - 20];
        }

        pcap_sendpacket(global_openedInterface, packet, packetLength + 20);
    }   

    /* if (clearMessageLine) {
        sendBar->getMessageLine()->setText("");
    } */
    
    number++;

}