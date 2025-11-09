#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

class Book {
public:
    std::string id;
    std::string title;
    std::string author;
    std::string description;
    std::string coverImage;
    int year;
    std::vector<std::string> genres;
    std::string isbn;
    double rating;

    Book();
    Book(const std::string& id, const std::string& title, const std::string& author,
         const std::string& description, const std::string& coverImage, int year,
         const std::vector<std::string>& genres, const std::string& isbn, double rating);
    
    bool matchesFilter(const std::string& authorFilter, int yearFilter, 
                      const std::string& genreFilter, const std::string& promptFilter) const;
    std::string toJson() const;
    static Book fromJson(const std::string& json);
};

#endif // BOOK_H

