#include "./MessageLineEnterPress/MessageLineEnterPress.cpp"

MessageLineEnterPress::MessageLineEnterPress() {}
MessageLineEnterPress::~MessageLineEnterPress() {}

void MessageLineEnterPress::clickSendButton() {
    sendBar->getSendButton()->click();
}