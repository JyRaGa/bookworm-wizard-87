#include "../include/User.h"

User::User() {}

User::User(const std::string& id, const std::string& email,
           const std::string& name, const std::string& password)
    : id(id), email(email), name(name), password(password) {}

bool User::verifyPassword(const std::string& password) const {
    return this->password == password;
}

std::string User::toJson() const {
    return "{\"id\":\"" + id + "\",\"email\":\"" + email + "\",\"name\":\"" + name + "\"}";
}

User User::fromJson(const std::string& json) {
    User user;
    // Simple JSON parsing
    size_t pos = json.find("\"id\":\"");
    if (pos != std::string::npos) {
        pos += 6;
        size_t end = json.find("\"", pos);
        if (end != std::string::npos) user.id = json.substr(pos, end - pos);
    }
    pos = json.find("\"email\":\"");
    if (pos != std::string::npos) {
        pos += 9;
        size_t end = json.find("\"", pos);
        if (end != std::string::npos) user.email = json.substr(pos, end - pos);
    }
    pos = json.find("\"name\":\"");
    if (pos != std::string::npos) {
        pos += 8;
        size_t end = json.find("\"", pos);
        if (end != std::string::npos) user.name = json.substr(pos, end - pos);
    }
    return user;
}

