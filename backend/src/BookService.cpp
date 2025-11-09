#include "../include/BookService.h"
#include "../include/Storage.h"
#include "../include/Book.h"
#include <algorithm>

std::vector<Book> BookService::getAllBooks() {
    return Storage::loadBooks();
}

std::vector<Book> BookService::filterBooks(const FilterOptions& filters) {
    std::vector<Book> allBooks = Storage::loadBooks();
    std::vector<Book> filtered;
    
    for (const auto& book : allBooks) {
        if (book.matchesFilter(filters.author, filters.year,
                              filters.genre, filters.prompt)) {
            filtered.push_back(book);
        }
    }
    
    return filtered;
}

Book* BookService::getBookById(const std::string& id) {
    static Book foundBook;
    auto books = Storage::loadBooks();
    for (const auto& book : books) {
        if (book.id == id) {
            foundBook = book;
            return &foundBook;
        }
    }
    return nullptr;
}

std::vector<Book> BookService::getBooksByIds(const std::vector<std::string>& ids) {
    std::vector<Book> result;
    auto allBooks = Storage::loadBooks();
    
    for (const auto& id : ids) {
        for (const auto& book : allBooks) {
            if (book.id == id) {
                result.push_back(book);
                break;
            }
        }
    }
    
    return result;
}

