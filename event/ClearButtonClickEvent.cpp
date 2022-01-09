#include "./ClearButtonClick/ClearButtonClick.hpp"

ClearButtonClick::ClearButtonClick() {}
ClearButtonClick::~ClearButtonClick() {}

void ClearButtonClick::clearChatRoom() {
    chatRoom->getChatRoom()->clear();
}