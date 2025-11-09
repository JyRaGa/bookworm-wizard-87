#include "../include/Storage.h"
#include "../include/Book.h"
#include "../include/User.h"
#include "../include/ReadingList.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

const std::string Storage::BOOKS_FILE = "data/books.txt";
const std::string Storage::USERS_FILE = "data/users.txt";
const std::string Storage::READING_LISTS_FILE = "data/reading_lists.txt";

std::vector<Book> Storage::loadBooks() {
    std::vector<Book> books;
    std::ifstream file(BOOKS_FILE);
    if (!file.is_open()) {
        initializeDefaultData();
        return loadBooks();
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            // Simple format: id|title|author|description|year|genres|isbn|rating
            std::istringstream iss(line);
            std::string id, title, author, description, yearStr, genresStr, isbn, ratingStr;
            
            std::getline(iss, id, '|');
            std::getline(iss, title, '|');
            std::getline(iss, author, '|');
            std::getline(iss, description, '|');
            std::getline(iss, yearStr, '|');
            std::getline(iss, genresStr, '|');
            std::getline(iss, isbn, '|');
            std::getline(iss, ratingStr, '|');
            
            std::vector<std::string> genres;
            std::istringstream genreStream(genresStr);
            std::string genre;
            while (std::getline(genreStream, genre, ',')) {
                genres.push_back(genre);
            }
            
            Book book(id, title, author, description, "", std::stoi(yearStr),
                     genres, isbn, std::stod(ratingStr));
            books.push_back(book);
        }
    }
    file.close();
    return books;
}

void Storage::saveBooks(const std::vector<Book>& books) {
    std::ofstream file(BOOKS_FILE);
    for (const auto& book : books) {
        std::string genresStr;
        for (size_t i = 0; i < book.genres.size(); ++i) {
            if (i > 0) genresStr += ",";
            genresStr += book.genres[i];
        }
        file << book.id << "|" << book.title << "|" << book.author << "|"
             << book.description << "|" << book.year << "|" << genresStr << "|"
             << book.isbn << "|" << book.rating << "\n";
    }
    file.close();
}

void Storage::addBook(const Book& book) {
    auto books = loadBooks();
    books.push_back(book);
    saveBooks(books);
}

std::vector<User> Storage::loadUsers() {
    std::vector<User> users;
    std::ifstream file(USERS_FILE);
    if (!file.is_open()) {
        return users;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            // Format: id|email|name|password
            std::istringstream iss(line);
            std::string id, email, name, password;
            
            std::getline(iss, id, '|');
            std::getline(iss, email, '|');
            std::getline(iss, name, '|');
            std::getline(iss, password, '|');
            
            users.push_back(User(id, email, name, password));
        }
    }
    file.close();
    return users;
}

void Storage::saveUsers(const std::vector<User>& users) {
    std::ofstream file(USERS_FILE);
    for (const auto& user : users) {
        file << user.id << "|" << user.email << "|" << user.name << "|"
             << user.password << "\n";
    }
    file.close();
}

void Storage::addUser(const User& user) {
    auto users = loadUsers();
    users.push_back(user);
    saveUsers(users);
}

User* Storage::findUserByEmail(const std::string& email) {
    static User foundUser;
    auto users = loadUsers();
    for (auto& user : users) {
        if (user.email == email) {
            foundUser = user;
            return &foundUser;
        }
    }
    return nullptr;
}

std::vector<ReadingList> Storage::loadReadingLists() {
    std::vector<ReadingList> lists;
    std::ifstream file(READING_LISTS_FILE);
    if (!file.is_open()) {
        return lists;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            // Format: userId|bookId1,bookId2,...
            std::istringstream iss(line);
            std::string userId, bookIdsStr;
            
            std::getline(iss, userId, '|');
            std::getline(iss, bookIdsStr, '|');
            
            ReadingList list(userId);
            std::istringstream bookStream(bookIdsStr);
            std::string bookId;
            while (std::getline(bookStream, bookId, ',')) {
                if (!bookId.empty()) {
                    list.addBook(bookId, ReadingStatus::WANT_TO_READ);
                }
            }
            lists.push_back(list);
        }
    }
    file.close();
    return lists;
}

void Storage::saveReadingLists(const std::vector<ReadingList>& lists) {
    std::ofstream file(READING_LISTS_FILE);
    for (const auto& list : lists) {
        std::string bookIdsStr;
        auto bookIds = list.getBookIds();
        for (size_t i = 0; i < bookIds.size(); ++i) {
            if (i > 0) bookIdsStr += ",";
            bookIdsStr += bookIds[i];
        }
        file << list.userId << "|" << bookIdsStr << "\n";
    }
    file.close();
}

ReadingList* Storage::getReadingList(const std::string& userId) {
    static ReadingList foundList;
    auto lists = loadReadingLists();
    for (auto& list : lists) {
        if (list.userId == userId) {
            foundList = list;
            return &foundList;
        }
    }
    // Create new list if not found
    foundList = ReadingList(userId);
    return &foundList;
}

void Storage::saveReadingList(const ReadingList& list) {
    auto lists = loadReadingLists();
    bool found = false;
    for (auto& l : lists) {
        if (l.userId == list.userId) {
            l = list;
            found = true;
            break;
        }
    }
    if (!found) {
        lists.push_back(list);
    }
    saveReadingLists(lists);
}

std::string Storage::getCurrentDateTime() {
    std::time_t now = std::time(nullptr);
    std::tm* timeinfo = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(timeinfo, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void Storage::initializeDefaultData() {
    // Create data directory
    #ifdef _WIN32
    system("mkdir data 2>nul");
    #else
    system("mkdir -p data");
    #endif
    
    // Create default books
    std::vector<Book> defaultBooks = {
        Book("1", "The Great Gatsby", "F. Scott Fitzgerald",
             "A classic American novel set in the Jazz Age that explores themes of wealth, love, and the American Dream.",
             "", 1925, {"Fiction", "Classic"}, "9780743273565", 4.5),
        Book("2", "1984", "George Orwell",
             "A dystopian social science fiction novel and cautionary tale about the dangers of totalitarianism.",
             "", 1949, {"Fiction", "Dystopian", "Science Fiction"}, "9780451524935", 4.7),
        Book("3", "To Kill a Mockingbird", "Harper Lee",
             "A gripping tale of racial injustice and childhood innocence in the American South.",
             "", 1960, {"Fiction", "Classic"}, "9780061120084", 4.8),
        Book("4", "Pride and Prejudice", "Jane Austen",
             "A romantic novel of manners that depicts the emotional development of protagonist Elizabeth Bennet.",
             "", 1813, {"Fiction", "Classic", "Romance"}, "9780141439518", 4.6),
        Book("5", "The Catcher in the Rye", "J.D. Salinger",
             "A controversial novel about teenage rebellion and alienation in post-World War II America.",
             "", 1951, {"Fiction", "Classic"}, "9780316769174", 4.3)
    };
    
    saveBooks(defaultBooks);
}

