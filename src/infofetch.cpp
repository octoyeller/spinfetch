#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/utsname.h>
#include <filesystem>
#include <fstream>
#include "infofetch.h"






void OS_info::System::set_username () {
    username = getenv ("USER");
}

void OS_info::System::set_hostname () {
    char buffer [1024];
    gethostname (buffer, 1024);
    hostname = buffer;
}

bool OS_info::System::set_os () {

    std::string file_contents [7];
    std::filesystem::path os_rel_path = "/etc/os-release";
    if (!std::filesystem::exists (os_rel_path) ) {
        std::cerr << os_rel_path << " does not exist" << std::endl;
        return false;
    }
    
    std::fstream os_rel;
    os_rel.open (os_rel_path, std::ios::in);
    if (!os_rel.good ()) {
        os_rel.close ();
        perror ("good");
        std::cerr << "Could not read " << os_rel_path << std::endl;
        return false;
    }

    os_rel.seekg (0, std::ios::beg);;
    for (int i = 0; i < 7; ++i) {
        getline (os_rel, file_contents [i]);
    }
    os_rel.close ();


    size_t first, len;
    first = file_contents [1].find_first_of ('\"');
    len = file_contents [1] .find_last_of ('\"') - first;
    name = file_contents [1].substr (first + 1, len - 1);

    first = file_contents [2].find_first_of ('\"');
    len = file_contents [2] .find_last_of ('\"') - first;
    release = file_contents [2].substr (first + 1, len - 1);

    first = file_contents [4].find_first_of ('=');
    len = file_contents [4].length () - first;
    codename = file_contents [4].substr (first + 1, len);


    struct utsname buffer;
    if (uname (&buffer) != 0) {
        perror ("uname");
        std::cerr << "Could not get kernel version" << std::endl;
        return false;
    }
    kernel = buffer.release;




    return true;
}









std::string OS_info::System::get_username () {
    return username;
}

std::string OS_info::System::get_hostname () {
    return hostname;
}

std::string OS_info::System::get_name () {
    return name;
}

std::string OS_info::System::get_release () {
    return release;
}

std::string OS_info::System::get_codename () {
    return codename;
}

std::string OS_info::System::get_kernel () {
    return kernel;
}

