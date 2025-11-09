#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    std::string id;
    std::string email;
    std::string name;
    std::string password; // In production, this should be hashed

    User();
    User(const std::string& id, const std::string& email, 
         const std::string& name, const std::string& password);
    
    bool verifyPassword(const std::string& password) const;
    std::string toJson() const;
    static User fromJson(const std::string& json);
};

#endif // USER_H

