#ifndef USER_INTERACT_NDL
#define USER_INTERACT_NDL

#if defined(_WIN32) || defined(_WIN64)
    #include <direct.h>
#else
    #include <sys/stat.h>
#endif

#include <cstdlib>
#include <algorithm>

#include "User/LocalUser.hpp"
#include "User/User.hpp"

#include "TInteract.hpp"
#include "Config.hpp"

class UInteract {
    public:
        TInteract ti;
        Config config;

        UInteract();
        UInteract(TInteract ti, Config config);

        bool verifUser(std::string usr);

        LocalUser FirstTimeChoose();
};

UInteract::UInteract() {}

UInteract::UInteract(TInteract ti, Config config) {
    this->ti = ti;
    this->config = config;
}

LocalUser UInteract::FirstTimeChoose() {
    std::string username = "";
    std::string password = "";

    while(true) {
        username = ti.answer("Enter username : ");
        password = ti.answer("Enter password : ");
        if (username == "" || password == "") {
            ti.printError("\nInvalid username or password !\n");
        }else{
            break;
        }
    }

    std::string Nusername = ti.answer("Enter NDL username (optional) : ");
    User u;
    if (Nusername != "") {
        std::string Npassword = ti.answer("Enter NDL password : ");
        u = User::getUser(Nusername, Npassword);

        ti.printError("No NDL user found ! Please retry later !");
    }

    if (!verifUser(username)) config.createUser(username);

    if (u.isEmpty()) return LocalUser(username, password);
    else return LocalUser(password, u);
}

bool UInteract::verifUser(std::string usr) {
    std::string uFolder = config.dir + "usr/" + usr + "/";

    std::cout << uFolder << std::endl;

    #if defined(_WIN32) || defined(_WIN64)
        if (_access(uFolder.c_str(), 0) == 0){
            return true;
        }
    #else
        struct stat info;
        if (stat(uFolder.c_str(), &info) == 0 && S_ISDIR(info.st_mode)) return true;
    #endif

    return false;
}

#endif
