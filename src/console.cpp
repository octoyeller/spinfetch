#include "console.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>



bool Console::set_size () {

    struct winsize w;
    int e = ioctl (STDOUT_FILENO, TIOCGWINSZ, &w);
    width = w.ws_row;
    height = w.ws_col;


    if (e < 0) {
        return false;
    }


    return true;
}




Console::Console () {
    successed = set_size ();
    if (!successed) {
        std::cout << "Failed fetching console size" << std::endl;
    }
}


unsigned Console::get_width () {
    return width;
}

unsigned Console::get_height () {
    return height;
}
