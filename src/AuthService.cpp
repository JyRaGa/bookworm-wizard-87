#include "../include/AuthService.h"
#include "../include/Storage.h"
#include "../include/User.h"
#include <sstream>
#include <random>

User* AuthService::currentUser = nullptr;

User* AuthService::login(const std::string& email, const std::string& password) {
    User* user = Storage::findUserByEmail(email);
    if (user && user->verifyPassword(password)) {
        currentUser = user;
        return user;
    }
    return nullptr;
}

User* AuthService::registerUser(const std::string& email, const std::string& password,
                                const std::string& name) {
    // Check if user already exists
    if (Storage::findUserByEmail(email) != nullptr) {
        return nullptr;
    }
    
    std::string id = generateUserId();
    User newUser(id, email, name, password);
    Storage::addUser(newUser);
    
    currentUser = Storage::findUserByEmail(email);
    return currentUser;
}

void AuthService::logout() {
    currentUser = nullptr;
}

User* AuthService::getCurrentUser() {
    return currentUser;
}

bool AuthService::isLoggedIn() {
    return currentUser != nullptr;
}

std::string AuthService::generateUserId() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1000, 9999);
    
    std::ostringstream oss;
    oss << "user_" << dis(gen);
    return oss.str();
}

