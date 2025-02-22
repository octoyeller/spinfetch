#include <iostream>
#include <cstdlib>
#include <vector>
#include <unistd.h>
#include <sys/sysinfo.h>
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

    os_rel.seekg (0, std::ios::beg);
    for (int i = 0; i < 7; ++i) {
        getline (os_rel, file_contents [i]);
    }
    os_rel.close ();


    size_t first, len;
    first = file_contents [1].find_first_of ('\"');
    len = file_contents [1] .find_last_of ('\"') - first;
    name = file_contents [1].substr (first + 1, len - 1);

    if (name != "Arch Linux") {
        first = file_contents [2].find_first_of ('\"');
        len = file_contents [2] .find_last_of ('\"') - first;
        release = file_contents [2].substr (first + 1, len - 1);
    } else {
        release = "Rolling";
    }

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







int OS_info::Uptime::get_days () {
    return days;
}

int OS_info::Uptime::get_hours () {
    return hours;
}

int OS_info::Uptime::get_minutes () {
    return minutes;
}

bool OS_info::Uptime::set_time () {

    struct sysinfo si;
    if (sysinfo (&si) != 0) {
        std::cerr << "Failed to get uptime." << std::endl;
        return false;
    }

    days = si.uptime / 60 / 60 / 24;
    hours = si.uptime / 60 / 60 - days * 24;
    minutes = si.uptime / 60 - days * 24 - hours * 60;

    return true;
}

OS_info::Uptime::Uptime () {
    set_time ();
}




bool OS_info::Hardware::set_battery () {


    // for BAT1 and BAT2 in the future
    // if (!std::filesystem::exists ("/sys/class/power_supply/BAT0") || !std::filesystem::is_directory ("/sys/class/power_supply/BAT0")) {
    //     return false;
    // }


    std::filesystem::path energy_full_path = "/sys/class/power_supply/BAT0/energy_full"; 
    std::filesystem::path energy_now_path = "/sys/class/power_supply/BAT0/energy_now";
    std::filesystem::path type_path = "/sys/class/power_supply/BAT0/type";
    std::filesystem::path status_path = "/sys/class/power_supply/BAT0/status";

    if (!std::filesystem::exists (energy_full_path) || !std::filesystem::exists (energy_now_path) || !std::filesystem::exists (type_path) || !std::filesystem::exists (status_path)) {
        return false;
    }

    
    std::fstream type;
    std::string cur_line;
    type.open (type_path, std::ios::in);
    if (!type.good ()) {
        std::cerr << "Failed reading battery type file." << std::endl;
        type.close ();
        return false;
    }
    type.seekg (0, std::ios::beg);
    getline (type, cur_line);
    if (cur_line != "Battery") {
        type.close ();
        return false;
    }


    std::fstream status;
    status.open (status_path, std::ios::in);
    if (!status.good ()) {
        status.close ();
        battery_status = "";
    }
    status.seekg (0, std::ios::beg);
    getline (status, battery_status);
    status.close ();


    std::fstream energy_full;
    energy_full.open (energy_full_path, std::ios::in);
    if (!energy_full.good ()) {
        energy_full.close ();
        return false;
    }
    energy_full.seekg (0, std::ios::beg);
    getline (energy_full, cur_line);
    energy_full.close ();
    float bat_full = std::stof (cur_line);


    std::fstream energy_now;
    energy_now.open (energy_now_path, std::ios::in);
    if (!energy_now.good ()) {
        energy_now.close ();
        return false;
    }
    energy_now.seekg (0, std::ios::beg);
    getline (energy_now, cur_line);
    energy_now.close ();
    float bat_now = std::stof (cur_line);


    battery_percent = bat_now / bat_full * 100;

    return true;
}


void OS_info::Hardware::obtain_battery () {
    has_battery = set_battery ();
}


bool OS_info::Hardware::see_if_has_battery () {
    return has_battery;
}


int OS_info::Hardware::get_battery_percent () {
    return battery_percent;
}

std::string OS_info::Hardware::get_battery_status () {
    return battery_status;
}






bool OS_info::Hardware::set_ram () {


    std::filesystem::path fpath = "/proc/meminfo";
    if (!std::filesystem::exists (fpath)) {
        return false;
    }

    std::fstream fmem;
    fmem.open (fpath, std::ios::in);
    if (!fmem.good ()) {
        fmem.close ();
        return false;
    }
    fmem.seekg (0, std::ios::beg);
    std::string cur_line;
    std::string fval [4];


    while (getline (fmem, cur_line)) {
        if (cur_line.substr (0, 9) == "MemTotal:") {
            break;
        }
    }
    fval [0] = cur_line;

    while (getline (fmem, cur_line)) {
        if (cur_line.substr (0, 7) == "Active:") {
            break;
        }
    }
    fval [1] = cur_line;

    while (getline (fmem, cur_line)) {
        if (cur_line.substr (0, 10) == "SwapTotal:") {
            break;
        }
    }
    fval [2] = cur_line;

    while (getline (fmem, cur_line)) {
        if (cur_line.substr (0, 9) == "SwapFree:") {
            break;
        }
    }
    fval [3] = cur_line;
    fmem.close ();

    
    size_t start, end;
    end = fval [0].find_last_of (' ');
    start = fval [0].find_last_of (' ', end - 1);
    ram_total = std::stoul (fval [0].substr (start + 1, end - start - 1));

    end = fval [1].find_last_of (' ');
    start = fval [1].find_last_of (' ', end - 1);
    ram_used = std::stoul (fval [1].substr (start + 1, end - start - 1));


    end = fval [2].find_last_of (' ');
    start = fval [2].find_last_of (' ', end - 1);
    swap_total = std::stoul (fval [2].substr (start + 1, end - start - 1));

    end = fval [3].find_last_of (' ');
    start = fval [3].find_last_of (' ', end - 1);
    swap_used = swap_total - std::stoul (fval [3].substr (start + 1, end - start - 1));




// active is used
// Active Swap = SwapTotal - SwapFree
// MemTotal
// Active
// SwapTotal
// SwapFree


    return true;
}


unsigned long OS_info::Hardware::get_ram_total () {
    return ram_total;
}


unsigned long OS_info::Hardware::get_ram_used () {
    return ram_used;
}


unsigned long OS_info::Hardware::get_swap_total () {
    return swap_total;
}


unsigned long OS_info::Hardware::get_swap_used () {
    return swap_used;
}
