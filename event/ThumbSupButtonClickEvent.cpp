#include "./ThumbSupButtonClick/ThumbSupButtonClick.hpp"

ThumbSupButtonClick::ThumbSupButtonClick() { }
ThumbSupButtonClick::~ThumbSupButtonClick() { }

void ThumbSupButtonClick::sendThumbSup() {
    int sendResult = packetSend(userName, "๐", false);
    
    if (sendResult == -1) {
        QMessageBox::warning(mainWindow, "warning", 
            "<h3>ๆฒๆ้ไป้ขไฝ ๆฏ่ฆ้ๅๆฏ?</h3>", QMessageBox::Ok);
        return;
    }
}