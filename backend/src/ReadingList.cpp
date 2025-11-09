#include "../include/ReadingList.h"
#include "../include/Storage.h"
#include <algorithm>

ReadingListItem::ReadingListItem() : status(ReadingStatus::WANT_TO_READ) {
    addedAt = Storage::getCurrentDateTime();
}

ReadingListItem::ReadingListItem(const std::string& bookId, ReadingStatus status)
    : bookId(bookId), status(status) {
    addedAt = Storage::getCurrentDateTime();
}

ReadingList::ReadingList() {}

ReadingList::ReadingList(const std::string& userId) : userId(userId) {}

void ReadingList::addBook(const std::string& bookId, ReadingStatus status) {
    auto it = std::find_if(items.begin(), items.end(),
        [&bookId](const ReadingListItem& item) { return item.bookId == bookId; });
    
    if (it == items.end()) {
        items.push_back(ReadingListItem(bookId, status));
    }
}

void ReadingList::removeBook(const std::string& bookId) {
    items.erase(
        std::remove_if(items.begin(), items.end(),
            [&bookId](const ReadingListItem& item) { return item.bookId == bookId; }),
        items.end()
    );
}

bool ReadingList::hasBook(const std::string& bookId) const {
    return std::any_of(items.begin(), items.end(),
        [&bookId](const ReadingListItem& item) { return item.bookId == bookId; });
}

std::vector<std::string> ReadingList::getBookIds() const {
    std::vector<std::string> ids;
    for (const auto& item : items) {
        ids.push_back(item.bookId);
    }
    return ids;
}

std::string ReadingList::toJson() const {
    std::string json = "{\"userId\":\"" + userId + "\",\"items\":[";
    for (size_t i = 0; i < items.size(); ++i) {
        if (i > 0) json += ",";
        json += "{\"bookId\":\"" + items[i].bookId + "\",\"status\":\"" +
                (items[i].status == ReadingStatus::WANT_TO_READ ? "want-to-read" :
                 items[i].status == ReadingStatus::READING ? "reading" : "completed") + "\"}";
    }
    json += "]}";
    return json;
}

ReadingList ReadingList::fromJson(const std::string& json) {
    ReadingList list;
    size_t pos = json.find("\"userId\":\"");
    if (pos != std::string::npos) {
        pos += 10;
        size_t end = json.find("\"", pos);
        if (end != std::string::npos) list.userId = json.substr(pos, end - pos);
    }
    return list;
}

