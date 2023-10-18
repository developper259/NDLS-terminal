#ifndef USER_NDL
#define USER_NDL

#include "UserStats.hpp"

class User {
    public:
        std::string id;
        UserStats US;

        User(std::string id, UserStats US);
        User();

        static User empty();
        bool isEmpty();

        static User getUser(std::string username, std::string password);
};

User::User(std::string id, UserStats US) {
    this->id = id;
    this->US = US;
}

User::User() {
    this->id = "";
    this->US = UserStats::empty();
}

User User::empty() {
    return User(
        "",
        UserStats::empty()
    );
}

bool User::isEmpty() {
    if (id == "") {
        return true;
    }

    return false;
}

User User::getUser(std::string username, std::string password) {
    return User::empty();
}

#endif