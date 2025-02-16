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



void Binary::set_version () {

    version = "v0.1";
    release = "none";

#if defined(__i386__) || defined(_M_IX86)
    architecture = "x86_32";
#endif

#if defined(__x86_64__) || defined(_M_X64)
    architecture = "x86_64";
#endif

#if defined(__arm__) || defined(_M_ARM)
    architecture = "ARM_x32";
#endif

#if defined(__aarch64__) || defined(_M_ARM64)
    architecture = "ARM_x64";
#endif

}




std::string Binary::get_version () {
    return version;
}


std::string Binary::get_release () {
    return release;
}


std::string Binary::get_architecture () {
    return architecture;
}


void Binary::print_version () {
    std::cout << "Spinfetch!\n";
    std::cout << "Version: " << get_version() << "\nRlease: " << get_release() << "\nArchitecture: " << get_architecture() << '\n';
    std::cout << "Maintainer: Alexander Yell\nSource: https://github.com/octoyeller/spinfetch/\n";
    std::cout << "Located at: " << get_path() << std::endl;
}



Binary::Binary () {

    successed = find_me ();

    if (!successed) {
        std::cerr << "Failed to fetch path to the binary." << std::endl;
    }
    
}
