#include "../include/UI.h"
#include "../include/BookService.h"
#include "../include/AuthService.h"
#include "../include/Storage.h"
#include "../include/Book.h"
#include "../include/User.h"
#include "../include/ReadingList.h"
#include <iostream>
#include <iomanip>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#endif

void UI::clearScreen() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

void UI::printHeader(const std::string& title) {
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "  " << title << "\n";
    std::cout << "========================================\n";
}

void UI::printSeparator() {
    std::cout << "----------------------------------------\n";
}

void UI::printBook(const Book& book, int index) {
    if (index >= 0) {
        std::cout << "[" << index << "] ";
    }
    std::cout << book.title << " by " << book.author << "\n";
    std::cout << "   Year: " << book.year << " | Rating: " << std::fixed 
              << std::setprecision(1) << book.rating << " | Genres: ";
    for (size_t i = 0; i < book.genres.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << book.genres[i];
    }
    std::cout << "\n";
    std::cout << "   " << book.description << "\n";
    std::cout << "\n";
}

void UI::printBookList(const std::vector<Book>& books) {
    if (books.empty()) {
        std::cout << "No books found.\n";
        return;
    }
    
    for (size_t i = 0; i < books.size(); ++i) {
        printBook(books[i], i + 1);
        if (i < books.size() - 1) {
            printSeparator();
        }
    }
}

void UI::printMenu(const std::vector<std::string>& options) {
    std::cout << "\n";
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << options[i] << "\n";
    }
    std::cout << "\n";
}

int UI::getChoice(int maxChoice) {
    int choice;
    std::cout << "Enter your choice (1-" << maxChoice << "): ";
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (std::cin.fail() || choice < 1 || choice > maxChoice) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    
    return choice;
}

std::string UI::getInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

int UI::getIntInput(const std::string& prompt) {
    int value;
    std::cout << prompt;
    std::cin >> value;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return value;
}

void UI::waitForEnter() {
    std::cout << "\nPress Enter to continue...";
    #ifdef _WIN32
    _getch();
    #else
    std::cin.get();
    #endif
}

void UI::printMessage(const std::string& message, bool isError) {
    if (isError) {
        std::cout << "ERROR: " << message << "\n";
    } else {
        std::cout << message << "\n";
    }
}

void UI::showWelcomeScreen() {
    clearScreen();
    printHeader("BookWise - Smart Book Recommendations");
    std::cout << "Discover your next great read with AI-powered book recommendations,\n";
    std::cout << "advanced filters, and personalized reading lists.\n\n";
    std::cout << "Features:\n";
    std::cout << "  - Smart Search: Describe what you're looking for\n";
    std::cout << "  - Advanced Filters: Filter by author, year, genre\n";
    std::cout << "  - Personal Library: Build and manage your reading list\n\n";
}

void UI::showAuthMenu() {
    std::vector<std::string> options = {
        "Login",
        "Register",
        "Exit"
    };
    printMenu(options);
}

void UI::showLoginScreen() {
    clearScreen();
    printHeader("Login");
    std::string email = getInput("Email: ");
    std::string password = getInput("Password: ");
    
    User* user = AuthService::login(email, password);
    if (user) {
        printMessage("Welcome back, " + user->name + "!");
        waitForEnter();
    } else {
        printMessage("Invalid email or password.", true);
        waitForEnter();
    }
}

void UI::showRegisterScreen() {
    clearScreen();
    printHeader("Create Account");
    std::string name = getInput("Full Name: ");
    std::string email = getInput("Email: ");
    std::string password = getInput("Password: ");
    
    User* user = AuthService::registerUser(email, password, name);
    if (user) {
        printMessage("Account created successfully! Welcome to BookWise, " + user->name + "!");
        waitForEnter();
    } else {
        printMessage("Registration failed. Email may already be in use.", true);
        waitForEnter();
    }
}

void UI::showDashboard() {
    clearScreen();
    User* user = AuthService::getCurrentUser();
    if (!user) {
        return;
    }
    
    printHeader("BookWise Dashboard");
    std::cout << "Welcome, " << user->name << "!\n\n";
    
    std::vector<std::string> options = {
        "Browse Books",
        "My Reading List",
        "Filter Books",
        "Logout"
    };
    printMenu(options);
}

void UI::showBrowseBooks(const std::vector<Book>& books) {
    clearScreen();
    printHeader("Browse Books");
    printBookList(books);
    waitForEnter();
}

void UI::showReadingList(const std::vector<Book>& books) {
    clearScreen();
    printHeader("My Reading List");
    if (books.empty()) {
        std::cout << "Your reading list is empty.\n";
        std::cout << "Start adding books to build your collection!\n";
    } else {
        printBookList(books);
    }
    waitForEnter();
}

void UI::showFilterMenu() {
    clearScreen();
    printHeader("Filter Books");
    
    FilterOptions filters;
    std::string input;
    
    input = getInput("Author (press Enter to skip): ");
    if (!input.empty()) filters.author = input;
    
    input = getInput("Minimum Year (press Enter to skip): ");
    if (!input.empty()) filters.year = std::stoi(input);
    
    input = getInput("Genre (press Enter to skip): ");
    if (!input.empty()) filters.genre = input;
    
    input = getInput("Search prompt (press Enter to skip): ");
    if (!input.empty()) filters.prompt = input;
    
    std::vector<Book> filtered = BookService::filterBooks(filters);
    showBrowseBooks(filtered);
}

void UI::showBookDetails(const Book& book) {
    clearScreen();
    printHeader("Book Details");
    printBook(book);
    waitForEnter();
}

