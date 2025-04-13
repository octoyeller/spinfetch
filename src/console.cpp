#include "console.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <cstdlib>




bool Console::set_size () {

    struct winsize w;
    int e = ioctl (STDOUT_FILENO, TIOCGWINSZ, &w);
    width = w.ws_row;
    height = w.ws_col;


    if (e < 0) {
        perror ("ioctl");
        return false;
    }


    return true;
}




bool Console::set_shell () {
    
    const char* name = std::getenv ("SHELL");

    if (!name) {
        return false;
    }

    std::string crop = name;
    size_t offset = crop.find_last_of ('/');
    if (offset) {
        ++offset;
    }

    shell = crop.substr (offset);
    return true;
}




Console::Console () {
    successed = set_size ();
    if (!successed) {
        std::cerr << "Failed fetching console size" << std::endl;
    }
}


unsigned Console::get_width () {
    return width;
}

unsigned Console::get_height () {
    return height;
}

std::string Console::get_shell () {
    return shell;
}



// ai code but works compared to everything else
char getch () {
    struct termios oldt, newt;
    char ch;

    // Get the current terminal settings
    tcgetattr (STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable canonical and echo
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar ();


    // Restore the old terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
