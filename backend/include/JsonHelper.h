#ifndef JSON_HELPER_H
#define JSON_HELPER_H

#include <string>
#include <vector>
#include "Book.h"
#include "User.h"
#include "ReadingList.h"

class JsonHelper {
public:
    // Book serialization
    static std::string bookToJson(const Book& book);
    static std::string booksToJson(const std::vector<Book>& books);
    
    // User serialization
    static std::string userToJson(const User& user);
    
    // Reading list serialization
    static std::string readingListToJson(const ReadingList& list, const std::vector<Book>& books);
    
    // JSON parsing
    static bool parseLoginRequest(const std::string& json, std::string& email, std::string& password);
    static bool parseRegisterRequest(const std::string& json, std::string& email, 
                                    std::string& password, std::string& name);
    static bool parseReadingListRequest(const std::string& json, std::string& userId,
                                       std::string& bookId, std::string& status);
    
    // Filter parsing from query string
    static void parseFilterQuery(const std::string& query, std::string& author,
                                int& year, std::string& genre, std::string& prompt);
    
    // Utility
    static std::string escapeJson(const std::string& str);
    static std::string createErrorResponse(const std::string& message);
    static std::string createSuccessResponse(const std::string& data);
};

#endif // JSON_HELPER_H

