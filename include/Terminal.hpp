#ifndef TERMINAL_NDL
#define TERMINAL_NDL

#include <iostream>
#include <stdlib.h>

#include "Interact/TInteract.hpp"
#include "Interact/UInteract.hpp"

#include "User/User.hpp"
#include "User/LocalUser.hpp"

#include "CMD/CMD.hpp"
#include "Config.hpp"

class Terminal
{
public:
    CMD cmd;
    Config config;
    LocalUser lu;
    TInteract ti;
    UInteract ui;

    // NDLS version
    static std::string Nversion;
    // Terminal version
    static std::string Tversion;
    // CMD version
    static std::string Cversion;

    Terminal();
};

std::string Terminal::Nversion = "Beta 0.0.1";
std::string Terminal::Tversion = "Beta 0.0.1";
std::string Terminal::Cversion = "Beta 0.0.1";

Terminal::Terminal() {
    config = Config();


    bool isConfig = config.init();
    bool isUser = lu.load(config.dir);

    if (!isConfig) {
        ui = UInteract(ti, config);
    }

    if (!isUser) {
        lu = ui.FirstTimeChoose();
        lu.save(config.dir);
    }else{
        if (!ui.verifUser(lu.username)) config.createUser(lu.username);
    }

    cmd = CMD(ti, config, lu);

    cmd.run();
}

#endif
