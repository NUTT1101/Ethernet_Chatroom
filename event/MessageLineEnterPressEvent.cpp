#include "./MessageLineEnterPress/MessageLineEnterPress.hpp"

MessageLineEnterPress::MessageLineEnterPress() {}
MessageLineEnterPress::~MessageLineEnterPress() {}

void MessageLineEnterPress::clickSendButton() {
    sendBar->getSendButton()->click();
}