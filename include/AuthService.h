#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include <string>
#include "User.h"

class AuthService {
public:
    static User* login(const std::string& email, const std::string& password);
    static User* registerUser(const std::string& email, const std::string& password, 
                             const std::string& name);
    static void logout();
    static User* getCurrentUser();
    static bool isLoggedIn();
    
private:
    static User* currentUser;
    static std::string generateUserId();
};

#endif // AUTH_SERVICE_H

