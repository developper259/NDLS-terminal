#ifndef USER_STATS_NDL
#define USER_STATS_NDL

class UserStats {
    public:
        std::string username;
        std::string name;
        std::string email;
        std::string num;
        int age;

        std::string grade;
        std::string subscription;


        UserStats(
            std::string username,
            std::string name,
            std::string email,
            std::string num,
            int age,
            std::string grade,
            std::string subscription);
        UserStats();
        
        static UserStats empty();
        bool isEmpty();
};

UserStats::UserStats(
            std::string username,
            std::string name,
            std::string email,
            std::string num,
            int age,
            std::string grade,
            std::string subscription) {

    this->username = username;
    this->name = name;
    this->email = email;
    this->num = num;
    this->age = age;
    this->grade = grade;
    this->subscription = subscription;

}

UserStats::UserStats() {
    username = "";
    name = "";
    email = "";
    num = "";
    age = 0;
    grade = "";
    subscription = "";
}


UserStats UserStats::empty() {
    return UserStats(
        "",
        "",
        "",
        "",
        0,
        "",
        ""
    );
}

bool UserStats::isEmpty() {
    if (grade == "") {
        return true;
    }

    return false;
}

#endif