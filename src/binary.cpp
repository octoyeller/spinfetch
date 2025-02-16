#include "binary.h"
#include <iostream>
#include <vector>
#include <unistd.h>




std::string Binary::get_name () {
    return name;
}


std::string Binary::get_directory () {
    return directory;
}


std::string Binary::get_path () {
    return path;
}


bool Binary::find_me () {

    // directory
    std::vector<char> buffer (1024);
    ssize_t len = readlink("/proc/self/exe", buffer.data (), buffer.size () - 1);
    if (len < 0) {
        perror ("readlink");
        return false;
    }
    buffer [len] = '\0';
    std::string tmp (buffer.data ());
    directory = tmp.substr (0, tmp.find_last_of ('/') + 1);


    // path
    len = readlink ("/proc/self/exe", buffer.data (), buffer.size () - 1);
    if (len < 0) {
        perror ("readlink");
        return false;
    }
    buffer [len] = '\0';
    path = std::string (buffer.data ());


    // name
    name = path.substr (path.find_last_of ('/') + 1, path.size());

    return true;
}


Binary::Binary () {

    successed = find_me ();

    if (!successed) {
        std::cout << "Failed to fetch path to the binary." << std::endl;
    }
    
}
