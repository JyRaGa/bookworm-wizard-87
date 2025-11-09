#include "../build/httplib.h"
// The build script will download httplib.h to build/httplib.h
// Or download manually from: https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h
#include "../include/BookService.h"
#include "../include/AuthService.h"
#include "../include/Storage.h"
#include "../include/JsonHelper.h"
#include <iostream>
#include <sstream>

int main() {
    // Initialize storage
    Storage::initializeDefaultData();
    
    httplib::Server svr;
    
    // Enable CORS
    svr.set_default_headers({
        {"Access-Control-Allow-Origin", "*"},
        {"Access-Control-Allow-Methods", "GET, POST, DELETE, OPTIONS"},
        {"Access-Control-Allow-Headers", "Content-Type"}
    });
    
    // Handle OPTIONS requests for CORS
    svr.Options(".*", [](const httplib::Request&, httplib::Response& res) {
        return;
    });
    
    // Authentication endpoints
    svr.Post("/api/auth/login", [](const httplib::Request& req, httplib::Response& res) {
        std::string email, password;
        if (JsonHelper::parseLoginRequest(req.body, email, password)) {
            User* user = AuthService::login(email, password);
            if (user) {
                res.set_content(JsonHelper::userToJson(*user), "application/json");
            } else {
                res.status = 401;
                res.set_content(JsonHelper::createErrorResponse("Invalid email or password"), "application/json");
            }
        } else {
            res.status = 400;
            res.set_content(JsonHelper::createErrorResponse("Invalid request format"), "application/json");
        }
    });
    
    svr.Post("/api/auth/register", [](const httplib::Request& req, httplib::Response& res) {
        std::string email, password, name;
        if (JsonHelper::parseRegisterRequest(req.body, email, password, name)) {
            User* user = AuthService::registerUser(email, password, name);
            if (user) {
                res.set_content(JsonHelper::userToJson(*user), "application/json");
            } else {
                res.status = 400;
                res.set_content(JsonHelper::createErrorResponse("Email already exists"), "application/json");
            }
        } else {
            res.status = 400;
            res.set_content(JsonHelper::createErrorResponse("Invalid request format"), "application/json");
        }
    });
    
    // Book endpoints
    svr.Get("/api/books", [](const httplib::Request&, httplib::Response& res) {
        std::vector<Book> books = BookService::getAllBooks();
        res.set_content(JsonHelper::booksToJson(books), "application/json");
    });
    
    svr.Get("/api/books/filter", [](const httplib::Request& req, httplib::Response& res) {
        FilterOptions filters;
        
        // Get query parameters
        if (req.has_param("author")) filters.author = req.get_param_value("author");
        if (req.has_param("year")) {
            try {
                filters.year = std::stoi(req.get_param_value("year"));
            } catch (...) {
                filters.year = 0;
            }
        }
        if (req.has_param("genre")) filters.genre = req.get_param_value("genre");
        if (req.has_param("prompt")) filters.prompt = req.get_param_value("prompt");
        
        std::vector<Book> filtered = BookService::filterBooks(filters);
        res.set_content(JsonHelper::booksToJson(filtered), "application/json");
    });
    
    svr.Get(R"(/api/books/(\d+))", [](const httplib::Request& req, httplib::Response& res) {
        std::string id = req.matches[1];
        Book* book = BookService::getBookById(id);
        if (book) {
            res.set_content(JsonHelper::bookToJson(*book), "application/json");
        } else {
            res.status = 404;
            res.set_content(JsonHelper::createErrorResponse("Book not found"), "application/json");
        }
    });
    
    // Reading list endpoints
    svr.Get(R"(/api/reading-list/(.+))", [](const httplib::Request& req, httplib::Response& res) {
        std::string userId = req.matches[1];
        ReadingList* list = Storage::getReadingList(userId);
        std::vector<std::string> bookIds = list->getBookIds();
        std::vector<Book> books = BookService::getBooksByIds(bookIds);
        res.set_content(JsonHelper::readingListToJson(*list, books), "application/json");
    });
    
    svr.Post("/api/reading-list", [](const httplib::Request& req, httplib::Response& res) {
        std::string userId, bookId, statusStr;
        if (JsonHelper::parseReadingListRequest(req.body, userId, bookId, statusStr)) {
            ReadingList* list = Storage::getReadingList(userId);
            ReadingStatus status = ReadingStatus::WANT_TO_READ;
            if (statusStr == "reading") {
                status = ReadingStatus::READING;
            } else if (statusStr == "completed") {
                status = ReadingStatus::COMPLETED;
            }
            list->addBook(bookId, status);
            Storage::saveReadingList(*list);
            res.set_content("{\"success\":true}", "application/json");
        } else {
            res.status = 400;
            res.set_content(JsonHelper::createErrorResponse("Invalid request format"), "application/json");
        }
    });
    
    svr.Delete(R"(/api/reading-list/(.+))", [](const httplib::Request& req, httplib::Response& res) {
        std::string bookId = req.matches[1];
        // Note: In a real app, we'd need userId from session/auth
        // For now, we'll need to get it from query param or body
        std::string userId = req.get_param_value("userId");
        if (!userId.empty()) {
            ReadingList* list = Storage::getReadingList(userId);
            list->removeBook(bookId);
            Storage::saveReadingList(*list);
            res.set_content("{\"success\":true}", "application/json");
        } else {
            res.status = 400;
            res.set_content(JsonHelper::createErrorResponse("User ID required"), "application/json");
        }
    });
    
    std::cout << "BookWise Backend Server starting on http://localhost:8080\n";
    std::cout << "API endpoints available at http://localhost:8080/api\n";
    
    svr.listen("0.0.0.0", 8080);
    
    return 0;
}

