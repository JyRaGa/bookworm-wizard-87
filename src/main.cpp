#include "../include/UI.h"
#include "../include/AuthService.h"
#include "../include/BookService.h"
#include "../include/Storage.h"
#include "../include/ReadingList.h"
#include "../include/Book.h"
#include "../include/User.h"
#include <iostream>
#include <vector>

int main() {
    // Initialize storage
    Storage::initializeDefaultData();
    
    bool running = true;
    
    while (running) {
        if (!AuthService::isLoggedIn()) {
            // Not logged in - show welcome/auth menu
            UI::showWelcomeScreen();
            UI::showAuthMenu();
            
            int choice = UI::getChoice(3);
            
            switch (choice) {
                case 1: // Login
                    UI::showLoginScreen();
                    break;
                case 2: // Register
                    UI::showRegisterScreen();
                    break;
                case 3: // Exit
                    running = false;
                    std::cout << "Thank you for using BookWise!\n";
                    break;
                default:
                    UI::printMessage("Invalid choice. Please try again.", true);
                    UI::waitForEnter();
                    break;
            }
        } else {
            // Logged in - show dashboard
            UI::showDashboard();
            
            int choice = UI::getChoice(4);
            
            switch (choice) {
                case 1: { // Browse Books
                    std::vector<Book> books = BookService::getAllBooks();
                    UI::showBrowseBooks(books);
                    break;
                }
                case 2: { // My Reading List
                    User* user = AuthService::getCurrentUser();
                    if (user) {
                        ReadingList* list = Storage::getReadingList(user->id);
                        std::vector<std::string> bookIds = list->getBookIds();
                        std::vector<Book> books = BookService::getBooksByIds(bookIds);
                        UI::showReadingList(books);
                    }
                    break;
                }
                case 3: // Filter Books
                    UI::showFilterMenu();
                    break;
                case 4: // Logout
                    AuthService::logout();
                    UI::printMessage("You have been logged out.");
                    UI::waitForEnter();
                    break;
                default:
                    UI::printMessage("Invalid choice. Please try again.", true);
                    UI::waitForEnter();
                    break;
            }
        }
    }
    
    return 0;
}

