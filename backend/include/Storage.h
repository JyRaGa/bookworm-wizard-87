#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include "Book.h"
#include "User.h"
#include "ReadingList.h"

class Storage {
public:
    static const std::string BOOKS_FILE;
    static const std::string USERS_FILE;
    static const std::string READING_LISTS_FILE;

    // Book operations
    static std::vector<Book> loadBooks();
    static void saveBooks(const std::vector<Book>& books);
    static void addBook(const Book& book);
    
    // User operations
    static std::vector<User> loadUsers();
    static void saveUsers(const std::vector<User>& users);
    static void addUser(const User& user);
    static User* findUserByEmail(const std::string& email);
    
    // Reading list operations
    static std::vector<ReadingList> loadReadingLists();
    static void saveReadingLists(const std::vector<ReadingList>& lists);
    static ReadingList* getReadingList(const std::string& userId);
    static void saveReadingList(const ReadingList& list);
    
    // Utility
    static std::string getCurrentDateTime();
    static void initializeDefaultData();
};

#endif // STORAGE_H

