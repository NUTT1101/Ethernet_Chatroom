#include "./ThumbSupButtonClick/ThumbSupButtonClick.hpp"

ThumbSupButtonClick::ThumbSupButtonClick() { }
ThumbSupButtonClick::~ThumbSupButtonClick() { }

void ThumbSupButtonClick::sendThumbSup() {
    int sendResult = packetSend(userName, "👍", false);
    
    if (sendResult == -1) {
        QMessageBox::warning(mainWindow, "warning", 
            "<h3>沒有開介面你是要送個毛?</h3>", QMessageBox::Ok);
        return;
    }
}