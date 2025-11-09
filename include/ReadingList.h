#ifndef READING_LIST_H
#define READING_LIST_H

#include <string>
#include <vector>
#include "Book.h"

enum class ReadingStatus {
    WANT_TO_READ,
    READING,
    COMPLETED
};

struct ReadingListItem {
    std::string bookId;
    std::string addedAt;
    ReadingStatus status;
    
    ReadingListItem();
    ReadingListItem(const std::string& bookId, ReadingStatus status);
};

class ReadingList {
public:
    std::string userId;
    std::vector<ReadingListItem> items;

    ReadingList();
    ReadingList(const std::string& userId);
    
    void addBook(const std::string& bookId, ReadingStatus status);
    void removeBook(const std::string& bookId);
    bool hasBook(const std::string& bookId) const;
    std::vector<std::string> getBookIds() const;
    std::string toJson() const;
    static ReadingList fromJson(const std::string& json);
};

#endif // READING_LIST_H

