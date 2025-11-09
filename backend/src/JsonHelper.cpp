#include "../include/JsonHelper.h"
#include <sstream>
#include <algorithm>
#include <iomanip>

std::string JsonHelper::escapeJson(const std::string& str) {
    std::ostringstream o;
    for (size_t i = 0; i < str.length(); ++i) {
        switch (str[i]) {
            case '"': o << "\\\""; break;
            case '\\': o << "\\\\"; break;
            case '\b': o << "\\b"; break;
            case '\f': o << "\\f"; break;
            case '\n': o << "\\n"; break;
            case '\r': o << "\\r"; break;
            case '\t': o << "\\t"; break;
            default:
                if ('\x00' <= str[i] && str[i] <= '\x1f') {
                    o << "\\u" << std::hex << std::setw(4) << std::setfill('0') << (int)str[i];
                } else {
                    o << str[i];
                }
        }
    }
    return o.str();
}

std::string JsonHelper::bookToJson(const Book& book) {
    std::ostringstream oss;
    oss << "{"
        << "\"id\":\"" << escapeJson(book.id) << "\","
        << "\"title\":\"" << escapeJson(book.title) << "\","
        << "\"author\":\"" << escapeJson(book.author) << "\","
        << "\"description\":\"" << escapeJson(book.description) << "\","
        << "\"coverImage\":\"" << escapeJson(book.coverImage) << "\","
        << "\"year\":" << book.year << ","
        << "\"genre\":[";
    for (size_t i = 0; i < book.genres.size(); ++i) {
        if (i > 0) oss << ",";
        oss << "\"" << escapeJson(book.genres[i]) << "\"";
    }
    oss << "],"
        << "\"isbn\":\"" << escapeJson(book.isbn) << "\","
        << "\"rating\":" << std::fixed << std::setprecision(1) << book.rating
        << "}";
    return oss.str();
}

std::string JsonHelper::booksToJson(const std::vector<Book>& books) {
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < books.size(); ++i) {
        if (i > 0) oss << ",";
        oss << bookToJson(books[i]);
    }
    oss << "]";
    return oss.str();
}

std::string JsonHelper::userToJson(const User& user) {
    std::ostringstream oss;
    oss << "{"
        << "\"id\":\"" << escapeJson(user.id) << "\","
        << "\"email\":\"" << escapeJson(user.email) << "\","
        << "\"name\":\"" << escapeJson(user.name) << "\""
        << "}";
    return oss.str();
}

std::string JsonHelper::readingListToJson(const ReadingList& list, const std::vector<Book>& books) {
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < books.size(); ++i) {
        if (i > 0) oss << ",";
        std::string bookJson = bookToJson(books[i]);
        // Find status for this book
        std::string status = "want-to-read";
        for (const auto& item : list.items) {
            if (item.bookId == books[i].id) {
                status = (item.status == ReadingStatus::WANT_TO_READ ? "want-to-read" :
                         item.status == ReadingStatus::READING ? "reading" : "completed");
                break;
            }
        }
        // Insert status into JSON before the closing brace
        bookJson.pop_back(); // Remove closing }
        oss << bookJson << ",\"status\":\"" << status << "\"}";
    }
    oss << "]";
    return oss.str();
}

bool JsonHelper::parseLoginRequest(const std::string& json, std::string& email, std::string& password) {
    size_t pos = json.find("\"email\":\"");
    if (pos == std::string::npos) return false;
    pos += 9;
    size_t end = json.find("\"", pos);
    if (end == std::string::npos) return false;
    email = json.substr(pos, end - pos);
    
    pos = json.find("\"password\":\"");
    if (pos == std::string::npos) return false;
    pos += 11;
    end = json.find("\"", pos);
    if (end == std::string::npos) return false;
    password = json.substr(pos, end - pos);
    
    return true;
}

bool JsonHelper::parseRegisterRequest(const std::string& json, std::string& email,
                                     std::string& password, std::string& name) {
    size_t pos = json.find("\"email\":\"");
    if (pos == std::string::npos) return false;
    pos += 9;
    size_t end = json.find("\"", pos);
    if (end == std::string::npos) return false;
    email = json.substr(pos, end - pos);
    
    pos = json.find("\"password\":\"");
    if (pos == std::string::npos) return false;
    pos += 11;
    end = json.find("\"", pos);
    if (end == std::string::npos) return false;
    password = json.substr(pos, end - pos);
    
    pos = json.find("\"name\":\"");
    if (pos == std::string::npos) return false;
    pos += 8;
    end = json.find("\"", pos);
    if (end == std::string::npos) return false;
    name = json.substr(pos, end - pos);
    
    return true;
}

bool JsonHelper::parseReadingListRequest(const std::string& json, std::string& userId,
                                        std::string& bookId, std::string& status) {
    size_t pos = json.find("\"userId\":\"");
    if (pos != std::string::npos) {
        pos += 10;
        size_t end = json.find("\"", pos);
        if (end != std::string::npos) {
            userId = json.substr(pos, end - pos);
        }
    }
    
    pos = json.find("\"bookId\":\"");
    if (pos == std::string::npos) return false;
    pos += 10;
    size_t end = json.find("\"", pos);
    if (end == std::string::npos) return false;
    bookId = json.substr(pos, end - pos);
    
    pos = json.find("\"status\":\"");
    if (pos != std::string::npos) {
        pos += 10;
        end = json.find("\"", pos);
        if (end != std::string::npos) {
            status = json.substr(pos, end - pos);
        }
    }
    
    return true;
}

void JsonHelper::parseFilterQuery(const std::string& query, std::string& author,
                                  int& year, std::string& genre, std::string& prompt) {
    // Simple query string parsing
    size_t pos = query.find("author=");
    if (pos != std::string::npos) {
        pos += 7;
        size_t end = query.find("&", pos);
        if (end == std::string::npos) end = query.length();
        author = query.substr(pos, end - pos);
    }
    
    pos = query.find("year=");
    if (pos != std::string::npos) {
        pos += 6;
        size_t end = query.find("&", pos);
        if (end == std::string::npos) end = query.length();
        try {
            year = std::stoi(query.substr(pos, end - pos));
        } catch (...) {
            year = 0;
        }
    }
    
    pos = query.find("genre=");
    if (pos != std::string::npos) {
        pos += 6;
        size_t end = query.find("&", pos);
        if (end == std::string::npos) end = query.length();
        genre = query.substr(pos, end - pos);
    }
    
    pos = query.find("prompt=");
    if (pos != std::string::npos) {
        pos += 7;
        size_t end = query.find("&", pos);
        if (end == std::string::npos) end = query.length();
        prompt = query.substr(pos, end - pos);
    }
}

std::string JsonHelper::createErrorResponse(const std::string& message) {
    return "{\"error\":\"" + escapeJson(message) + "\"}";
}

std::string JsonHelper::createSuccessResponse(const std::string& data) {
    return "{\"success\":true,\"data\":" + data + "}";
}

