#include <iostream>
#include <stdlib.h>

#include "Terminal.hpp"
#include "debug/main.hpp"

int main(/*int argc, char *argv[]*/)
{
    bool debuging = false;
    if (debuging == true) {
        debug();
        return 0;
    }
    Terminal t = Terminal();
}
