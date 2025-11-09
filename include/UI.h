#ifndef UI_H
#define UI_H

#include <string>
#include "Book.h"
#include "ReadingList.h"

class UI {
public:
    static void clearScreen();
    static void printHeader(const std::string& title);
    static void printSeparator();
    static void printBook(const Book& book, int index = -1);
    static void printBookList(const std::vector<Book>& books);
    static void printMenu(const std::vector<std::string>& options);
    static int getChoice(int maxChoice);
    static std::string getInput(const std::string& prompt);
    static int getIntInput(const std::string& prompt);
    static void waitForEnter();
    static void printMessage(const std::string& message, bool isError = false);
    
    // Specific UI screens
    static void showWelcomeScreen();
    static void showAuthMenu();
    static void showLoginScreen();
    static void showRegisterScreen();
    static void showDashboard();
    static void showBrowseBooks(const std::vector<Book>& books);
    static void showReadingList(const std::vector<Book>& books);
    static void showFilterMenu();
    static void showBookDetails(const Book& book);
};

#endif // UI_H

