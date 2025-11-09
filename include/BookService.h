#ifndef BOOK_SERVICE_H
#define BOOK_SERVICE_H

#include <string>
#include <vector>
#include "Book.h"

struct FilterOptions {
    std::string author;
    int year = 0;
    std::string genre;
    std::string prompt;
};

class BookService {
public:
    static std::vector<Book> getAllBooks();
    static std::vector<Book> filterBooks(const FilterOptions& filters);
    static Book* getBookById(const std::string& id);
    static std::vector<Book> getBooksByIds(const std::vector<std::string>& ids);
};

#endif // BOOK_SERVICE_H

